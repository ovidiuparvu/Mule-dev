#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/StatisticalModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/exception/ModelCheckingException.hpp"
#include "multiscale/verification/spatial-temporal/execution/CommandLineModelChecking.hpp"

#include <iostream>

using namespace multiscale::verification;


// Constants which need to be defined prior to some methods
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_STATISTICAL                = 1;
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX    = 0;


CommandLineModelChecking::CommandLineModelChecking()
    : allowedArguments(CONFIG_CAPTION_ALLOWED_ARGUMENTS),
      requiredArguments(CONFIG_CAPTION_REQUIRED_ARGUMENTS),
      optionalArguments(CONFIG_CAPTION_OPTIONAL_ARGUMENTS),
      modelCheckerTypeSpecificArguments(CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS) {}

CommandLineModelChecking::~CommandLineModelChecking() {}

void CommandLineModelChecking::initialise(int argc, char **argv) {
    if (areValidArguments(argc, argv)) {
        initialiseClassMembers();
        printModelCheckingInitialisationMessage();
    } else {
        MS_throw(ModelCheckingException, ERR_INVALID_COMMAND_LINE_ARGUMENTS);
    }
}

void CommandLineModelChecking::execute() {
    modelCheckingManager->runModelCheckingTasks(modelCheckerFactory);
}

bool CommandLineModelChecking::areValidArguments(int argc, char **argv) {
    initialiseAllowedArgumentsConfiguration();

    return areValidArgumentsConsideringConfiguration(argc, argv);
}

void CommandLineModelChecking::initialiseAllowedArgumentsConfiguration() {
    initialiseRequiredArgumentsConfiguration();
    initialiseOptionalArgumentsConfiguration();
    initialiseModelCheckerTypeSpecificArgumentsConfiguration();

    allowedArguments.add(requiredArguments)
                    .add(optionalArguments)
                    .add(modelCheckerTypeSpecificArguments);
}

void CommandLineModelChecking::initialiseRequiredArgumentsConfiguration() {
    requiredArguments.add_options()("logic-queries,q"            , po::value<string>()->required()          , "the path to the spatial-temporal queries input file\n")
                                   ("spatial-temporal-traces,t"  , po::value<string>()->required()          , "the path to the folder containing spatial-temporal traces\n")
                                   ("extra-evaluation-time,e"    , po::value<unsigned long>()->required()   , "the maximum number of minutes the application can wait before finishing evaluation\n")
                                   ("model-checker-type,m"       , po::value<unsigned int>()->required()    , "the type of the model checker (0 = Probabilistic black-box, 1 = Statistical) \n");
}

void CommandLineModelChecking::initialiseOptionalArgumentsConfiguration() {
    optionalArguments.add_options()("help,h"                     , "display help message (describing the meaning and usage of each command line argument)\n")
                                   ("extra-evaluation-program,p" , po::value<string>()                       , "the program which will be executed whenever extra evaluation (and input traces) is required\n")
                                   ("verbose,v"                  , po::bool_switch()                         , "if this flag is set detailed evaluation results will be displayed\n");
}

void CommandLineModelChecking::initialiseModelCheckerTypeSpecificArgumentsConfiguration() {
    po::options_description statisticalArguments(CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS);

    statisticalArguments.add_options()("alpha,a",   po::value<double>(), "the probability of type I errors (false positives)\n")
                                      ("beta,b",    po::value<double>(), "the probability of type II errors (false negatives)\n");

    modelCheckerTypeSpecificArguments.add(statisticalArguments);
}

bool CommandLineModelChecking::areValidArgumentsConsideringConfiguration(int argc, char **argv) {
    po::parsed_options parsedArguments = parseAndStoreArgumentsValues(argc, argv);

    if (areInvalidArguments(parsedArguments)) {
        return false;
    } else {
        // Check if all arguments are present and valid
        po::notify(variablesMap);

        return (!areInvalidModelCheckingArguments());
    }
}

po::parsed_options CommandLineModelChecking::parseAndStoreArgumentsValues(int argc, char **argv) {
    po::parsed_options parsedOptions = po::command_line_parser(argc, argv).
                                       options(allowedArguments).allow_unregistered().run();

    po::store(parsedOptions, variablesMap);

    return parsedOptions;
}

bool CommandLineModelChecking::areInvalidArguments(const po::parsed_options &parsedArguments) {
    return (
        isHelpArgumentPresent()                             ||
        areUnrecognizedArgumentsPresent(parsedArguments)
    );
}

bool CommandLineModelChecking::isHelpArgumentPresent() {
    if (variablesMap.count("help")) {
        printHelpMessage();

        return true;
    }

    return false;
}

void CommandLineModelChecking::printHelpMessage() {
    std::cout << std::endl
              << "USAGE: " << std::endl
              << "    Mudi <required-arguments> [<optional-arguments>] <model-checking-type-specific-arguments>" << std::endl;

    std::cout << allowedArguments << std::endl;
}

bool CommandLineModelChecking::areUnrecognizedArgumentsPresent(const po::parsed_options &parsedArguments) {
    std::vector<std::string> unrecognizedOptions = po::collect_unrecognized(parsedArguments.options,
                                                                            po::include_positional);

    return (unrecognizedOptions.size() > 0);
}

bool CommandLineModelChecking::areInvalidModelCheckingArguments() {
    if (areInvalidModelCheckingArgumentsPresent()) {
        MS_throw(ModelCheckingException, ERR_INVALID_MODEL_CHECKING_ARGUMENTS);
    }

    return false;
}

bool CommandLineModelChecking::areInvalidModelCheckingArgumentsPresent() {
    switch (variablesMap["model-checker-type"].as<unsigned int>()) {
        case MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX:
            return (areStatisticalModelCheckingArgumentsPresent(false));

        case MODEL_CHECKER_TYPE_STATISTICAL:
            return (!areStatisticalModelCheckingArgumentsPresent(true));

        default:
            MS_throw(InvalidInputException, ERR_INVALID_MODEL_CHECKING_TYPE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return false;
}

bool CommandLineModelChecking::areStatisticalModelCheckingArgumentsPresent(bool allArguments) {
    if (allArguments) {
        // Are all arguments present?
        return (
            (variablesMap.count("alpha")) &&
            (variablesMap.count("beta"))
        );
    } else {
        // Is at least one argument present?
        return (
            (variablesMap.count("alpha")) ||
            (variablesMap.count("beta"))
        );
    }
}

void CommandLineModelChecking::initialiseClassMembers() {
    initialiseRequiredArgumentsDependentClassMembers();
    initialiseOptionalArgumentsDependentClassMembers();
    initialiseModelCheckerTypeDependentClassMembers();
}

void CommandLineModelChecking::initialiseRequiredArgumentsDependentClassMembers() {
    logicQueriesFilepath  = variablesMap["logic-queries"].as<string>();
    tracesFolderPath      = variablesMap["spatial-temporal-traces"].as<string>();
    extraEvaluationTime   = variablesMap["extra-evaluation-time"].as<unsigned long>();
    modelCheckerType      = variablesMap["model-checker-type"].as<unsigned int>();
}

void CommandLineModelChecking::initialiseOptionalArgumentsDependentClassMembers() {
    if (variablesMap.count("verbose")) {
        shouldVerboseDetailedResults = variablesMap["verbose"].as<bool>();
    }

    if (variablesMap.count("extra-evaluation-program")) {
        extraEvaluationProgramPath = variablesMap["extra-evaluation-program"].as<string>();
    }
}

void CommandLineModelChecking::initialiseModelCheckerTypeDependentClassMembers() {
    initialiseModelChecker();
    initialiseModelCheckingManager();
}

void CommandLineModelChecking::initialiseModelChecker() {
    switch (modelCheckerType) {
        case MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX:
            initialiseProbabilisticBlackBoxModelChecker();
            break;

        case MODEL_CHECKER_TYPE_STATISTICAL:
            initialiseStatisticalModelChecker();
            break;

        default:
            MS_throw(InvalidInputException, ERR_INVALID_MODEL_CHECKING_TYPE);
    }
}

void CommandLineModelChecking::initialiseProbabilisticBlackBoxModelChecker() {
    modelCheckerFactory = make_shared<ProbabilisticBlackBoxModelCheckerFactory>();

    modelCheckerTypeName    = MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME;
    modelCheckerParameters  = MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS;
}

void CommandLineModelChecking::initialiseStatisticalModelChecker() {
    double alpha = variablesMap["alpha"].as<double>();
    double beta  = variablesMap["beta"].as<double>();

    modelCheckerFactory = make_shared<StatisticalModelCheckerFactory>(alpha, beta);

    modelCheckerTypeName    = MODEL_CHECKER_STATISTICAL_NAME;
    modelCheckerParameters  = (
        MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN +
        StringManipulator::toString(alpha) +
        MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE +
        StringManipulator::toString(beta) +
        MODEL_CHECKER_STATISTICAL_PARAMETERS_END
    );
}

void CommandLineModelChecking::initialiseModelCheckingManager() {
    modelCheckingManager = make_shared<ModelCheckingManager>(logicQueriesFilepath,
                                                             tracesFolderPath,
                                                             extraEvaluationTime);

    modelCheckingManager->setExtraEvaluationProgramPath(extraEvaluationProgramPath);
    modelCheckingManager->setShouldPrintDetailedEvaluation(shouldVerboseDetailedResults);
}

void CommandLineModelChecking::printModelCheckingInitialisationMessage() {
    ModelCheckingOutputWriter::printIntroductionMessage  (modelCheckerTypeName, modelCheckerParameters);
    ModelCheckingOutputWriter::printInitialisationMessage(logicQueriesFilepath, tracesFolderPath, extraEvaluationTime);
}


// Constants
const std::string   CommandLineModelChecking::ERR_INVALID_COMMAND_LINE_ARGUMENTS      = "Invalid command line arguments were provided and the model checker execution was stopped.";
const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_ARGUMENTS    = "The command line arguments provided for the chosen model checking type are invalid. Please run Mudi with the --help flag to determine which arguments you should use.";

const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_TYPE         = "The provided model checking type is invalid. Please run Mudi with the --help flag to determine which values you can use.";

const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME        = "Probabilistic black-box";
const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS  = "None";

const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_NAME                = "Statistical";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN    = "Probability of type I errors (false positives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE   = " and of type II errors (false negatives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_END      = ".";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_ALLOWED_ARGUMENTS                        = "";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_REQUIRED_ARGUMENTS                       = "REQUIRED ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_OPTIONAL_ARGUMENTS                       = "OPTIONAL ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS    = "REQUIRED ARGUMENTS SPECIFIC TO MODEL CHECKER TYPE";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_PROBABILISTIC_BLACK_BOX_MODEL_CHECKER_ARGUMENTS  = "Probabilistic black-box";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS              = "Statistical";
