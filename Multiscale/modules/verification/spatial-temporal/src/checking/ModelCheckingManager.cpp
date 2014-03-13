#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

using namespace multiscale::verification;


ModelCheckingManager::ModelCheckingManager(const std::string &logicPropertyFilepath,
                                           const std::string &tracesFolderPath,
                                           unsigned long extraEvaluationTime) {
    initialise(logicPropertyFilepath, tracesFolderPath, extraEvaluationTime);
}

ModelCheckingManager::~ModelCheckingManager() {
    abstractSyntaxTrees.clear();
    logicProperties.clear();
    modelCheckers.clear();
}

void ModelCheckingManager::runFrequencyModelChecking() {
    parseLogicProperties();
    createModelCheckers();
    runModelCheckers();
    outputModelCheckersResults();
}

void ModelCheckingManager::initialise(const std::string &logicPropertyFilepath,
                                      const std::string &tracesFolderPath,
                                      unsigned long extraEvaluationTime) {
    this->extraEvaluationTime = extraEvaluationTime;

    initialiseLogicProperties(logicPropertyFilepath);
    initialiseTraceReader(tracesFolderPath);
}

void ModelCheckingManager::initialiseLogicProperties(const std::string &logicPropertiesFilepath) {
    logicProperties = logicPropertyReader.readLogicPropertiesFromFile(logicPropertiesFilepath);
}

void ModelCheckingManager::initialiseTraceReader(const std::string &tracesFolderPath) {
    traceReader = SpatialTemporalDataReader(tracesFolderPath);
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

void ModelCheckingManager::createModelCheckers() {
    for (const auto &abstractSyntaxTree : abstractSyntaxTrees) {
        modelCheckers.push_back(
            std::shared_ptr<ModelChecker>(new FrequencyModelChecker(abstractSyntaxTree))
        );
    }
}

void ModelCheckingManager::runModelCheckers() {
    bool continueEvaluation = true;

    while ((continueEvaluation) && (traceReader.hasNext())) {
        SpatialTemporalTrace trace = traceReader.getNextSpatialTemporalTrace();

        runModelCheckersForTrace(trace, continueEvaluation);
    }
}

void ModelCheckingManager::runModelCheckersForTrace(const SpatialTemporalTrace &trace,
                                                    bool &continueEvaluation) {
    continueEvaluation = false;

    for (auto &modelChecker : modelCheckers) {
        if (modelChecker->acceptsMoreTraces()) {
            modelChecker->evaluate(trace);

            continueEvaluation = true;
        }
    }
}
