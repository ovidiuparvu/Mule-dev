#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

using namespace multiscale::verification;


ModelCheckingManager::ModelCheckingManager(const std::string &logicPropertiesFilepath,
                                           const std::string &tracesFolderPath,
                                           unsigned long extraEvaluationTime)
                                           : parser(PARSER_EMPTY_LOGIC_PROPERTY),
                                             traceReader(tracesFolderPath) {
    initialise(logicPropertiesFilepath, extraEvaluationTime);
}

ModelCheckingManager::~ModelCheckingManager() {
    logicProperties.clear();
    abstractSyntaxTrees.clear();
    tracesPaths.clear();
    modelCheckers.clear();
}

void ModelCheckingManager::runModelCheckingTasks(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory) {
    runModelCheckingAndOutputResults(modelCheckerFactory);
}

void ModelCheckingManager::initialise(const std::string &logicPropertyFilepath,
                                      unsigned long extraEvaluationTime) {
    this->extraEvaluationTime = extraEvaluationTime;
    this->evaluationStartTime = std::chrono::system_clock::now();

    initialiseLogicProperties(logicPropertyFilepath);
}

void ModelCheckingManager::initialiseLogicProperties(const std::string &logicPropertiesFilepath) {
    logicProperties = logicPropertyReader.readLogicPropertiesFromFile(logicPropertiesFilepath);
}

void ModelCheckingManager::runModelCheckingAndOutputResults(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory) {
    parseLogicPropertiesAndPrintMessage();
    createModelCheckers(modelCheckerFactory);
    runModelCheckersAndPrintMessage();
    outputModelCheckersResultsAndPrintMessage();
    outputDetailedEvaluationResults();
}

void ModelCheckingManager::parseLogicPropertiesAndPrintMessage() {
    ModelCheckingOutputWriter::printParsingLogicPropertiesBeginMessage();

    parseLogicProperties();

    ModelCheckingOutputWriter::printParsingLogicPropertiesEndMessage();
}

void ModelCheckingManager::parseLogicProperties() {
    auto it = logicProperties.begin();

    while (it != logicProperties.end()) {
        if (parseLogicPropertyAndPrintMessages(*it)) {
            it++;
        } else {
            it = logicProperties.erase(it);
        }
    }
}

bool ModelCheckingManager::parseLogicPropertyAndPrintMessages(const std::string &logicProperty) {
    ModelCheckingOutputWriter::printParsingLogicPropertyMessage(logicProperty);

    bool isParsedSuccessfully = parseLogicProperty(logicProperty);

    printParsingMessage(isParsedSuccessfully);

    return isParsedSuccessfully;
}

bool ModelCheckingManager::parseLogicProperty(const std::string &logicProperty) {
    try {
        return isValidLogicProperty(logicProperty);
    } catch (const InvalidInputException &ex) {
        ExceptionHandler::printErrorMessage(ex);

        return false;
    }
}

bool ModelCheckingManager::isValidLogicProperty(const std::string &logicProperty) {
    AbstractSyntaxTree syntaxTree;

    parser.setLogicalQuery(logicProperty);

    if (parser.parse(syntaxTree)) {
        abstractSyntaxTrees.push_back(syntaxTree);

        return true;
    }

    return false;
}

void ModelCheckingManager::printParsingMessage(bool isParsingSuccessful) {
    if (isParsingSuccessful) {
        ModelCheckingOutputWriter::printSuccessMessage();
    } else {
        ModelCheckingOutputWriter::printFailedMessage();
    }
}

void ModelCheckingManager::createModelCheckers(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory) {
    for (const auto &abstractSyntaxTree : abstractSyntaxTrees) {
        modelCheckers.push_back(
            modelCheckerFactory->createInstance(abstractSyntaxTree)
        );
    }
}

void ModelCheckingManager::runModelCheckersAndPrintMessage() {
    ModelCheckingOutputWriter::printStartModelCheckingExecutionMessage();

    runModelCheckers();
}

void ModelCheckingManager::runModelCheckers() {
    runModelCheckersForCurrentlyExistingTraces();
    runModelCheckersAndRequestAdditionalTraces();
}

void ModelCheckingManager::runModelCheckersForCurrentlyExistingTraces() {
    bool continueEvaluation = true;

    while ((continueEvaluation) && (traceReader.hasNext())) {
        SpatialTemporalTrace trace = getNextSpatialTemporalTrace();

        createNewEvaluationResults();
        runModelCheckersForTrace(trace, continueEvaluation);
    }
}

SpatialTemporalTrace ModelCheckingManager::getNextSpatialTemporalTrace() {
    std::string tracePath;

    // Get the trace and its path
    SpatialTemporalTrace trace = traceReader.getNextSpatialTemporalTrace(tracePath);

    // Record the path of the trace
    tracesPaths.push_back(tracePath);

    return trace;
}

void ModelCheckingManager::createNewEvaluationResults() {
    evaluationResults.push_back(std::vector<bool>(2 * modelCheckers.size(), false));
}

void ModelCheckingManager::runModelCheckersForTrace(const SpatialTemporalTrace &trace,
                                                    bool &continueEvaluation) {
    continueEvaluation = false;
    auto nrOfModelCheckers = modelCheckers.size();

    for (decltype(nrOfModelCheckers) i = 0; i != nrOfModelCheckers; i++) {
        if (modelCheckers[i]->acceptsMoreTraces()) {
            runModelCheckerForTrace(i, trace);

            continueEvaluation = true;
        }
    }
}

void ModelCheckingManager::runModelCheckerForTrace(const std::size_t &modelCheckerIndex,
                                                   const SpatialTemporalTrace &trace) {
    bool evaluationResult = modelCheckers[modelCheckerIndex]->evaluate(trace);

    updateEvaluationResults(modelCheckerIndex, evaluationResult);
}

void ModelCheckingManager::updateEvaluationResults(const std::size_t &modelCheckerIndex, bool evaluationResult) {
    // Set the isEvaluated flag to true
    (evaluationResults.back())[(2 * modelCheckerIndex)] = true;

    // Set the evaluation result value
    (evaluationResults.back())[(2 * modelCheckerIndex) + 1] = evaluationResult;
}

void ModelCheckingManager::runModelCheckersAndRequestAdditionalTraces() {
    while ((isEvaluationTimeRemaining()) && (areUnfinishedModelCheckingTasks())) {
        waitBeforeRetry();
        updateTraceReader();
        runModelCheckersForCurrentlyExistingTraces();
    }
}

bool ModelCheckingManager::isEvaluationTimeRemaining() {
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = (currentTime - evaluationStartTime);

    double nrOfMinutes = ((elapsedSeconds.count()) / NR_SECONDS_IN_ONE_MINUTE);

    return (nrOfMinutes < extraEvaluationTime);
}

bool ModelCheckingManager::areUnfinishedModelCheckingTasks() {
    for (const auto &modelChecker : modelCheckers) {
        if (modelChecker->requiresMoreTraces()) {
            return true;
        }
    }

    return false;
}

void ModelCheckingManager::waitBeforeRetry() {
    ModelCheckingOutputWriter::printTimeoutMessage(TRACE_INPUT_REFRESH_TIMEOUT);

    std::this_thread::sleep_for(std::chrono::seconds(TRACE_INPUT_REFRESH_TIMEOUT));
}

void ModelCheckingManager::updateTraceReader() {
    traceReader.refresh();
}

void ModelCheckingManager::outputModelCheckersResultsAndPrintMessage() {
    ModelCheckingOutputWriter::printModelCheckingResultsIntroductionMessage();

    outputModelCheckersResults();
}

void ModelCheckingManager::outputModelCheckersResults() {
    unsigned int nrOfModelCheckers = modelCheckers.size();

    for (unsigned int i = 0; i < nrOfModelCheckers; i++) {
        outputModelCheckerResults(modelCheckers[i], logicProperties[i]);
    }
}

void ModelCheckingManager::outputModelCheckerResults(const std::shared_ptr<ModelChecker> &modelChecker,
                                                     const std::string &logicProperty) {
    ModelCheckingOutputWriter::printModelCheckingResultMessage(
        modelChecker->doesPropertyHold(),
        modelChecker->getDetailedResults(),
        logicProperty
    );
}

void ModelCheckingManager::outputDetailedEvaluationResults() {
    ModelCheckingOutputWriter::printDetailedEvaluationResults(
        logicProperties,
        tracesPaths,
        evaluationResults
    );
}


// Constants

const unsigned long ModelCheckingManager::TRACE_INPUT_REFRESH_TIMEOUT   = 30;
const unsigned long ModelCheckingManager::NR_SECONDS_IN_ONE_MINUTE      = 60;

const std::string   ModelCheckingManager::PARSER_EMPTY_LOGIC_PROPERTY   = "";
