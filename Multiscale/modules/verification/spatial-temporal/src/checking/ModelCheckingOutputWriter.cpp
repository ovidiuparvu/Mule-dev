#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

using namespace multiscale::verification;


void ModelCheckingOutputWriter::printIntroductionMessage(const std::string &modelCheckerType,
                                                         const std::string &modelCheckerParameters) {
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_NAME, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_COPYRIGHT, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_MODEL_CHECKING_TYPE + modelCheckerType,
                                                 TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_MODEL_CHECKING_PARAMETERS + modelCheckerParameters,
                                                 TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_CONTACT, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printInitialisationMessage(const std::string &logicProperty,
                                                           const std::string &tracesFolderPath,
                                                           unsigned long extraEvaluationTime) {
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_EXECUTION_PARAMETERS, TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INIT, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_LOGIC_PROPERTIES_PATH + logicProperty,
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_TRACES_FOLDER_PATH + tracesFolderPath,
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_EXTRA_EVALUATION_TIME +
                                                 StringManipulator::toString(extraEvaluationTime),
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printParsingLogicPropertiesBeginMessage() {
    ConsolePrinter::printMessageWithColouredTag (MSG_PARSING_INTRODUCTION, TAG_PARSING, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage        (TAG_PARSING, ColourCode::GREEN);

    printSeparatorTag();
}

void ModelCheckingOutputWriter::printParsingLogicPropertyMessage(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(StringManipulator::trimRight(logicProperty), TAG_PARSING, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printParsingLogicPropertiesEndMessage() {
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printStartModelCheckingExecutionMessage() {
    ConsolePrinter::printMessageWithColouredTag(MSG_START_MODEL_CHECKING_EXECUTION, TAG_EXECUTE, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage(TAG_EXECUTE, ColourCode::GREEN);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printStartTraceEvaluationMessage(const std::string &tracePath) {
    ConsolePrinter::printMessageWithColouredTag(MSG_START_TRACE_EVALUATION + tracePath, TAG_EXECUTE, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printExecuteExtraEvaluationProgramMessage(const std::string &programPath) {
    ConsolePrinter::printMessageWithColouredTag(MSG_START_EXTRA_EVALUATION_PROGRAM_EXECUTION +
                                                programPath, TAG_EXECUTE, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printTimeoutMessage(unsigned long timeOut) {
    ConsolePrinter::printMessageWithColouredTag(MSG_EXECUTION_TIMEOUT_BEGIN +
                                                StringManipulator::toString(timeOut) +
                                                MSG_EXECUTION_TIMEOUT_END,
                                                TAG_TIMEOUT, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResultsIntroductionMessage() {
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();

    ConsolePrinter::printMessageWithColouredTag(MSG_RESULTS_INTRODUCTION, TAG_RESULT, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage(TAG_RESULT, ColourCode::GREEN);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printModelCheckingResultMessage(bool doesPropertyHold,
                                                                const std::string &detailedResult,
                                                                const std::string &logicProperty) {
    printLogicPropertyForResult(logicProperty);
    printResultTag();

    printModelCheckingResult(doesPropertyHold);
    printModelCheckingDetailedResult(doesPropertyHold, detailedResult);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printDetailedEvaluationResults(const std::vector<std::string> &logicProperties,
                                                               const std::vector<std::string> &tracesPaths,
                                                               const std::vector<std::vector<bool>> &evaluationResults) {
    printDetailedEvaluationResultsIntroductionMessage();
    printDetailedEvaluationResultsForLogicProperties(logicProperties, tracesPaths, evaluationResults);
}

void ModelCheckingOutputWriter::printSuccessMessage() {
    ConsolePrinter::printColouredMessage(TAG_SUCCESS, ColourCode::GREEN);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printFailedMessage() {
    ConsolePrinter::printColouredMessage(TAG_FAILED, ColourCode::RED);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printLogicPropertyForResult(const std::string &logicProperty) {
    printLogicPropertyWithTag(logicProperty, TAG_RESULT);
}

void ModelCheckingOutputWriter::printLogicPropertyWithTag(const std::string &logicProperty,
                                                          const std::string &tag) {
    ConsolePrinter::printMessageWithColouredTag(StringManipulator::trimRight(logicProperty),
                                                tag, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResult(bool doesPropertyHold) {

    if (doesPropertyHold) {
        printTruthValueDependentMessage(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_TRUE, TAG_RESULT, doesPropertyHold);
    } else {
        printTruthValueDependentMessage(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_FALSE, TAG_RESULT, doesPropertyHold);
    }
}

void ModelCheckingOutputWriter::printModelCheckingDetailedResult(bool doesPropertyHold,
                                                                 const std::string &detailedResult) {
    printTruthValueDependentMessage(detailedResult, TAG_RESULT, doesPropertyHold);
}

void ModelCheckingOutputWriter::printDetailedEvaluationResultsIntroductionMessage() {
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printMessageWithColouredTag(MSG_EVALUATION_RESULTS_INTRODUCTION,
                                                TAG_DETAILS, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage(TAG_DETAILS, ColourCode::GREEN);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printDetailedEvaluationResultsForLogicProperties(const std::vector<std::string> &logicProperties,
                                                                                 const std::vector<std::string> &tracesPaths,
                                                                                 const std::vector<std::vector<bool>> &evaluationResults) {
    auto nrOfLogicProperties = logicProperties.size();

    for (decltype(nrOfLogicProperties) i = 0; i != nrOfLogicProperties; i++) {
        printLogicPropertyWithTag(logicProperties[i], TAG_DETAILS);
        ConsolePrinter::printColouredMessage(TAG_DETAILS, ColourCode::GREEN);

        printLogicPropertyDetailedEvaluationResults(i, tracesPaths, evaluationResults);
        printSeparatorTag();
    }
}

void ModelCheckingOutputWriter::printLogicPropertyDetailedEvaluationResults(const std::size_t &logicPropertyIndex,
                                                                            const std::vector<std::string> &tracesPaths,
                                                                            const std::vector<std::vector<bool>> &evaluationResults) {
    printDetailedEvaluationResults(logicPropertyIndex, tracesPaths, evaluationResults);
    printEvaluationResultsSummary(logicPropertyIndex, tracesPaths, evaluationResults);
}

void ModelCheckingOutputWriter::printDetailedEvaluationResults(const std::size_t &logicPropertyIndex,
                                                               const std::vector<std::string> &tracesPaths,
                                                               const std::vector<std::vector<bool>> &evaluationResults) {
    auto nrOfTraces = tracesPaths.size();

    for (decltype(nrOfTraces) i = 0; i != nrOfTraces; i++) {
        if (isTraceEvaluatedForLogicProperty(logicPropertyIndex, i, evaluationResults)) {
            printDetailedTraceEvaluationResult(logicPropertyIndex, tracesPaths[i], i, evaluationResults);
        }
    }
}

void ModelCheckingOutputWriter::printEvaluationResultsSummary(const std::size_t &logicPropertyIndex,
                                                              const std::vector<std::string> &tracesPaths,
                                                              const std::vector<std::vector<bool>> &evaluationResults) {
    std::size_t nrOfTraces              = tracesPaths.size();
    std::size_t nrOfEvaluatedTraces     = 0;
    std::size_t nrOfTracesEvaluatedTrue = 0;

    for (std::size_t i = 0; i != nrOfTraces; i++) {
        updateSummaryEvaluationResults(logicPropertyIndex, i, evaluationResults,
                                       nrOfEvaluatedTraces, nrOfTracesEvaluatedTrue);
    }

    printEvaluationResultsSummary(nrOfEvaluatedTraces, nrOfTracesEvaluatedTrue);
}

void ModelCheckingOutputWriter::updateSummaryEvaluationResults(const std::size_t &logicPropertyIndex,
                                                               const std::size_t &tracePathIndex,
                                                               const std::vector<std::vector<bool>> &evaluationResults,
                                                               size_t &nrOfEvaluatedTraces,
                                                               size_t &nrOfTracesEvaluatedTrue) {
    if (isTraceEvaluatedForLogicProperty(logicPropertyIndex, tracePathIndex, evaluationResults)) {
        nrOfEvaluatedTraces++;

        if (isTraceEvaluatedTrueForLogicProperty(logicPropertyIndex, tracePathIndex, evaluationResults)) {
            nrOfTracesEvaluatedTrue++;
        }
    }
}

bool ModelCheckingOutputWriter::isTraceEvaluatedForLogicProperty(const std::size_t &logicPropertyIndex,
                                                                 const std::size_t &tracePathIndex,
                                                                 const std::vector<std::vector<bool>> &evaluationResults) {
    return ((evaluationResults[tracePathIndex])[2 * logicPropertyIndex]);
}

void ModelCheckingOutputWriter::printEvaluationResultsSummary(std::size_t nrOfTraces,
                                                              std::size_t nrOfCorrectTraces) {
    ConsolePrinter::printColouredMessage(TAG_DETAILS, ColourCode::GREEN);

    ConsolePrinter::printMessageWithColouredTag(
        StringManipulator::toString(nrOfCorrectTraces) +
        MSG_EVALUATION_SUMMARY_BEGIN +
        StringManipulator::toString(nrOfTraces) +
        MSG_EVALUATION_SUMMARY_END,
        TAG_DETAILS,
        ColourCode::GREEN
    );
}

void ModelCheckingOutputWriter::printDetailedTraceEvaluationResult(const std::size_t &logicPropertyIndex,
                                                                   const std::string &tracePath,
                                                                   const std::size_t &tracePathIndex,
                                                                   const std::vector<std::vector<bool>> &evaluationResults) {
    // If the logic property was evaluated for this trace
    printTraceEvaluationResult(
        tracePath,
        (evaluationResults[tracePathIndex])[(2 * logicPropertyIndex) + 1]
    );
}

void ModelCheckingOutputWriter::printTraceEvaluationResult(const std::string &tracePath, bool evaluationResult) {
    if (evaluationResult) {
        printTruthValueDependentMessage(tracePath, TAG_TRUE, true);
    } else {
        printTruthValueDependentMessage(tracePath, TAG_FALSE, false);
    }
}

bool ModelCheckingOutputWriter::isTraceEvaluatedTrueForLogicProperty(const std::size_t &logicPropertyIndex,
                                                                     const std::size_t &tracePathIndex,
                                                                     const std::vector<std::vector<bool>> &evaluationResults) {
    if (isTraceEvaluatedForLogicProperty(logicPropertyIndex, tracePathIndex, evaluationResults)) {
        return (evaluationResults[tracePathIndex])[(2 * logicPropertyIndex) + 1];
    }

    return false;
}

void ModelCheckingOutputWriter::printTruthValueDependentMessage(const std::string &message,
                                                                const std::string &tag,
                                                                bool truthValue) {
    if (truthValue) {
        ConsolePrinter::printMessageWithColouredTag(message, tag, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(message, tag, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printResultTag() {
    ConsolePrinter::printColouredMessage(TAG_RESULT, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printSeparatorTag() {
    ConsolePrinter::printColouredMessage(TAG_SEPARATOR, ColourCode::GREEN);
}


// Constants
const std::string ModelCheckingOutputWriter::TAG_INTRO      = "[ INTRO    ]";
const std::string ModelCheckingOutputWriter::TAG_INIT       = "[ INIT     ]";
const std::string ModelCheckingOutputWriter::TAG_PARSING    = "[ PARSING  ]";
const std::string ModelCheckingOutputWriter::TAG_EXECUTE    = "[ EXECUTE  ]";
const std::string ModelCheckingOutputWriter::TAG_TIMEOUT    = "[ TIMEOUT  ]";
const std::string ModelCheckingOutputWriter::TAG_RESULT     = "[ RESULT   ]";
const std::string ModelCheckingOutputWriter::TAG_DETAILS    = "[ DETAILS  ]";
const std::string ModelCheckingOutputWriter::TAG_SUCCESS    = "[ SUCCESS  ]";
const std::string ModelCheckingOutputWriter::TAG_FAILED     = "[ FAILED   ]";
const std::string ModelCheckingOutputWriter::TAG_TRUE       = "[ TRUE     ]";
const std::string ModelCheckingOutputWriter::TAG_FALSE      = "[ FALSE    ]";
const std::string ModelCheckingOutputWriter::TAG_SEPARATOR  = "[==========]";

const std::string ModelCheckingOutputWriter::MSG_INTRO_NAME                         = "Mule 1.0.469 (Multidimensional multiscale model checker)";
const std::string ModelCheckingOutputWriter::MSG_INTRO_COPYRIGHT                    = "Copyright Ovidiu Pârvu 2014";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_TYPE          = "Model checker type: ";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_PARAMETERS    = "Parameters:         ";
const std::string ModelCheckingOutputWriter::MSG_INTRO_CONTACT                      = "For more details, recommendations or suggestions feel free to contact me at <ovidiu.parvu[AT]gmail.com>.";

const std::string ModelCheckingOutputWriter::MSG_INIT_EXECUTION_PARAMETERS  = "Multidimensional multiscale model checking input parameters";
const std::string ModelCheckingOutputWriter::MSG_INIT_LOGIC_PROPERTIES_PATH = "Logic properties input file:          ";
const std::string ModelCheckingOutputWriter::MSG_INIT_TRACES_FOLDER_PATH    = "Spatio-temporal traces input folder:  ";
const std::string ModelCheckingOutputWriter::MSG_INIT_EXTRA_EVALUATION_TIME = "Extra evaluation time (minutes):      ";

const std::string ModelCheckingOutputWriter::MSG_PARSING_INTRODUCTION       = "I am starting to parse logic properties...";

const std::string ModelCheckingOutputWriter::MSG_START_MODEL_CHECKING_EXECUTION             = "I am starting the execution of the model checkers...";
const std::string ModelCheckingOutputWriter::MSG_START_TRACE_EVALUATION                     = "Evaluating the spatio-temporal trace: ";
const std::string ModelCheckingOutputWriter::MSG_START_EXTRA_EVALUATION_PROGRAM_EXECUTION   = "I am starting the execution of the extra evaluation program located at the following path: ";
const std::string ModelCheckingOutputWriter::MSG_EXECUTION_TIMEOUT_BEGIN                    = "The model checker execution was suspended for ";
const std::string ModelCheckingOutputWriter::MSG_EXECUTION_TIMEOUT_END                      = " seconds during which new traces can be provided in the traces input folder.";

const std::string ModelCheckingOutputWriter::MSG_RESULTS_INTRODUCTION   = "I have finished evaluating the logic properties and will display the results...";

const std::string ModelCheckingOutputWriter::MSG_EVALUATION_RESULTS_INTRODUCTION    = "I will display for each logic property which traces evaluated to TRUE and which evaluated to FALSE...";
const std::string ModelCheckingOutputWriter::MSG_EVALUATION_SUMMARY_BEGIN           = "/";
const std::string ModelCheckingOutputWriter::MSG_EVALUATION_SUMMARY_END             = " spatio-temporal traces evaluated to TRUE";

const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS          = "The logic property holds: ";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_TRUE     = "TRUE";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_FALSE    = "FALSE";
