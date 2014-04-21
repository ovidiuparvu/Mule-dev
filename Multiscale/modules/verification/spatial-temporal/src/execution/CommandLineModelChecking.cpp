#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateProbabilisticModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/BayesianModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/StatisticalModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/exception/ModelCheckingException.hpp"
#include "multiscale/verification/spatial-temporal/exception/ModelCheckingHelpRequestException.hpp"
#include "multiscale/verification/spatial-temporal/execution/CommandLineModelChecking.hpp"

#include <iostream>

using namespace multiscale::verification;


// Constants which need to be defined prior to some methods
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX   = 0;
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_STATISTICAL               = 1;
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC = 2;
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_BAYESIAN                  = 3;


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
    } else if (isHelpArgumentPresent()) {
        handleHelpRequest();
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
    requiredArguments.add_options()(ARG_LOGIC_QUERIES_NAME_BOTH.c_str()             , po::value<string>()->required()          , (ARG_LOGIC_QUERIES_DESCRIPTION + "\n").c_str())
                                   (ARG_SPATIAL_TEMPORAL_TRACES_NAME_BOTH.c_str()   , po::value<string>()->required()          , (ARG_SPATIAL_TEMPORAL_TRACES_DESCRIPTION + "\n").c_str())
                                   (ARG_EXTRA_EVALUATION_TIME_NAME_BOTH.c_str()     , po::value<unsigned long>()->required()   , (ARG_EXTRA_EVALUATION_TIME_DESCRIPTION + "\n").c_str())
                                   (ARG_MODEL_CHECKER_TYPE_NAME_BOTH.c_str()        , po::value<unsigned int>()->required()    , (ARG_MODEL_CHECKER_TYPE_DESCRIPTION + "\n").c_str());
}

void CommandLineModelChecking::initialiseOptionalArgumentsConfiguration() {
    optionalArguments.add_options()(ARG_HELP_NAME_BOTH.c_str()                                              , (ARG_HELP_DESCRIPTION + "\n").c_str())
                                   (ARG_EXTRA_EVALUATION_PROGRAM_NAME_BOTH.c_str() , po::value<string>()    , (ARG_EXTRA_EVALUATION_PROGRAM_DESCRIPTION + "\n").c_str())
                                   (ARG_VERBOSE_NAME_BOTH.c_str()                  , po::bool_switch()      , (ARG_VERBOSE_DESCRIPTION + "\n").c_str());
}

void CommandLineModelChecking::initialiseModelCheckerTypeSpecificArgumentsConfiguration() {
    po::options_description statisticalArguments                (CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS);
    po::options_description approximateProbabilisticArguments   (CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS);
    po::options_description bayesianArguments                   (CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS);

    statisticalArguments                .add_options()(ARG_TYPE_I_ERROR_NAME_LONG.c_str()           , po::value<double>(), (ARG_TYPE_I_ERROR_DESCRIPTION + "\n").c_str())
                                                      (ARG_TYPE_II_ERROR_NAME_LONG.c_str()          , po::value<double>(), (ARG_TYPE_II_ERROR_DESCRIPTION + "\n").c_str());

    approximateProbabilisticArguments   .add_options()(ARG_DELTA_NAME_LONG.c_str()                  , po::value<double>(), (ARG_DELTA_DESCRIPTION + "\n").c_str())
                                                      (ARG_EPSILON_NAME_LONG.c_str()                , po::value<double>(), (ARG_EPSILON_DESCRIPTION + "\n").c_str());

    bayesianArguments                   .add_options()(ARG_ALPHA_NAME_LONG.c_str()                  , po::value<double>(), (ARG_ALPHA_DESCRIPTION + "\n").c_str())
                                                      (ARG_BETA_NAME_LONG.c_str()                   , po::value<double>(), (ARG_BETA_DESCRIPTION + "\n").c_str())
                                                      (ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG.c_str() , po::value<double>(), (ARG_BAYES_FACTOR_THRESHOLD_DESCRIPTION + "\n").c_str());

    modelCheckerTypeSpecificArguments.add(statisticalArguments)
                                     .add(approximateProbabilisticArguments)
                                     .add(bayesianArguments);
}

bool CommandLineModelChecking::areValidArgumentsConsideringConfiguration(int argc, char **argv) {
    po::parsed_options parsedArguments = parseAndStoreArgumentsValues(argc, argv);

    if (areInvalidExecutionArguments(parsedArguments)) {
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

bool CommandLineModelChecking::areInvalidExecutionArguments(const po::parsed_options &parsedArguments) {
    return (
        isHelpArgumentPresent()                             ||
        areUnrecognizedArgumentsPresent(parsedArguments)
    );
}

bool CommandLineModelChecking::isHelpArgumentPresent() {
    return (variablesMap.count(ARG_HELP_NAME_LONG));
}

void CommandLineModelChecking::handleHelpRequest() {
    printHelpMessage();

    MS_throw(ModelCheckingHelpRequestException, MSG_MODEL_CHECKING_HELP_REQUESTED);
}

void CommandLineModelChecking::printHelpMessage() {
    std::cout   << std::endl
                << HELP_NAME_LABEL << std::endl
                << HELP_NAME_MSG   << std::endl
                << std::endl
                << HELP_USAGE_LABEL << std::endl
                << HELP_USAGE_MSG   << std::endl;

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
    // TODO: Implement a more abstract method which is not so error-prone

    switch (variablesMap[ARG_MODEL_CHECKER_TYPE_NAME_LONG].as<unsigned int>()) {
        case MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX:
            return ((areStatisticalModelCheckingArgumentsPresent(false))                ||
                    (areApproximateProbabilisticModelCheckingArgumentsPresent(false))   ||
                    (areBayesianModelCheckingArgumentsPresent(false)));

        case MODEL_CHECKER_TYPE_STATISTICAL:
            return ((!areStatisticalModelCheckingArgumentsPresent(true))                ||
                    (areApproximateProbabilisticModelCheckingArgumentsPresent(false))   ||
                    (areBayesianModelCheckingArgumentsPresent(false)));

        case MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC:
            return ((!areApproximateProbabilisticModelCheckingArgumentsPresent(true))   ||
                    (areStatisticalModelCheckingArgumentsPresent(false))                ||
                    (areBayesianModelCheckingArgumentsPresent(false)));

        case MODEL_CHECKER_TYPE_BAYESIAN:
            return ((!areBayesianModelCheckingArgumentsPresent(true))                   ||
                    (areStatisticalModelCheckingArgumentsPresent(false))                ||
                    (areApproximateProbabilisticModelCheckingArgumentsPresent(false)));

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
            (variablesMap.count(ARG_TYPE_I_ERROR_NAME_LONG)) &&
            (variablesMap.count(ARG_TYPE_II_ERROR_NAME_LONG))
        );
    } else {
        // Is at least one argument present?
        return (
            (variablesMap.count(ARG_TYPE_I_ERROR_NAME_LONG)) ||
            (variablesMap.count(ARG_TYPE_II_ERROR_NAME_LONG))
        );
    }
}

bool CommandLineModelChecking::areApproximateProbabilisticModelCheckingArgumentsPresent(bool allArguments) {
    if (allArguments) {
        // Are all arguments present?
        return (
            (variablesMap.count(ARG_DELTA_NAME_LONG)) &&
            (variablesMap.count(ARG_EPSILON_NAME_LONG))
        );
    } else {
        // Is at least one argument present?
        return (
            (variablesMap.count(ARG_DELTA_NAME_LONG)) ||
            (variablesMap.count(ARG_EPSILON_NAME_LONG))
        );
    }
}

bool CommandLineModelChecking::areBayesianModelCheckingArgumentsPresent(bool allArguments) {
    if (allArguments) {
        // Are all arguments present?
        return (
            (variablesMap.count(ARG_ALPHA_NAME_LONG))                   &&
            (variablesMap.count(ARG_BETA_NAME_LONG))                    &&
            (variablesMap.count(ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG))
        );
    } else {
        // Is at least one argument present?
        return (
            (variablesMap.count(ARG_ALPHA_NAME_LONG))                   ||
            (variablesMap.count(ARG_BETA_NAME_LONG))                    ||
            (variablesMap.count(ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG))
        );
    }
}

void CommandLineModelChecking::initialiseClassMembers() {
    initialiseRequiredArgumentsDependentClassMembers();
    initialiseOptionalArgumentsDependentClassMembers();
    initialiseModelCheckerTypeDependentClassMembers();
}

void CommandLineModelChecking::initialiseRequiredArgumentsDependentClassMembers() {
    logicQueriesFilepath  = variablesMap[ARG_LOGIC_QUERIES_NAME_LONG].as<string>();
    tracesFolderPath      = variablesMap[ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG].as<string>();
    extraEvaluationTime   = variablesMap[ARG_EXTRA_EVALUATION_TIME_NAME_LONG].as<unsigned long>();
    modelCheckerType      = variablesMap[ARG_MODEL_CHECKER_TYPE_NAME_LONG].as<unsigned int>();
}

void CommandLineModelChecking::initialiseOptionalArgumentsDependentClassMembers() {
    if (variablesMap.count(ARG_VERBOSE_NAME_LONG)) {
        shouldVerboseDetailedResults = variablesMap[ARG_VERBOSE_NAME_LONG].as<bool>();
    }

    if (variablesMap.count(ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG)) {
        extraEvaluationProgramPath = variablesMap[ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG].as<string>();
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

        case MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC:
            initialiseApproximateProbabilisticModelChecker();
            break;

        case MODEL_CHECKER_TYPE_BAYESIAN:
            initialiseBayesianModelChecker();
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
    double typeIError   = variablesMap[ARG_TYPE_I_ERROR_NAME_LONG].as<double>();
    double typeIIError  = variablesMap[ARG_TYPE_II_ERROR_NAME_LONG].as<double>();

    modelCheckerFactory = make_shared<StatisticalModelCheckerFactory>(typeIError, typeIIError);

    modelCheckerTypeName    = MODEL_CHECKER_STATISTICAL_NAME;
    modelCheckerParameters  = (
        MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN +
        StringManipulator::toString(typeIError) +
        MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE +
        StringManipulator::toString(typeIIError) +
        MODEL_CHECKER_STATISTICAL_PARAMETERS_END
    );
}

void CommandLineModelChecking::initialiseApproximateProbabilisticModelChecker() {
    double delta    = variablesMap[ARG_DELTA_NAME_LONG].as<double>();
    double epsilon  = variablesMap[ARG_EPSILON_NAME_LONG].as<double>();

    modelCheckerFactory = make_shared<ApproximateProbabilisticModelCheckerFactory>(delta, epsilon);

    modelCheckerTypeName    = MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_NAME;
    modelCheckerParameters  = (
        MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_BEGIN +
        StringManipulator::toString(delta) +
        MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_MIDDLE +
        StringManipulator::toString(epsilon) +
        MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_END
    );
}

void CommandLineModelChecking::initialiseBayesianModelChecker() {
    double alpha                = variablesMap[ARG_ALPHA_NAME_LONG].as<double>();
    double beta                 = variablesMap[ARG_BETA_NAME_LONG].as<double>();
    double bayesFactorThreshold = variablesMap[ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG].as<double>();

    modelCheckerFactory = make_shared<BayesianModelCheckerFactory>(alpha, beta, bayesFactorThreshold);

    modelCheckerTypeName    = MODEL_CHECKER_BAYESIAN_NAME;
    modelCheckerParameters  = (
        MODEL_CHECKER_BAYESIAN_PARAMETERS_BEGIN +
        StringManipulator::toString(alpha) +
        MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE1 +
        StringManipulator::toString(beta) +
        MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE2 +
        StringManipulator::toString(bayesFactorThreshold) +
        MODEL_CHECKER_BAYESIAN_PARAMETERS_END
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
const std::string   CommandLineModelChecking::ERR_INVALID_COMMAND_LINE_ARGUMENTS                                = "Invalid command line arguments were provided and the model checker execution was stopped.";
const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_ARGUMENTS                              = "The command line arguments provided for the chosen model checking type are invalid. Please run Mudi with the --help flag to determine which arguments you should use.";

const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_TYPE                                   = "The provided model checking type is invalid. Please run Mudi with the --help flag to determine which values you can use.";

const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_NAME_LONG                                       = "logic-queries";
const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_NAME_BOTH                                       = ARG_LOGIC_QUERIES_NAME_LONG + ",q";
const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_DESCRIPTION                                     = "the path to the spatial-temporal queries input file";

const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG                             = "spatial-temporal-traces";
const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_NAME_BOTH                             = ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG + ",t";
const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_DESCRIPTION                           = "the path to the folder containing spatial-temporal traces";

const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_NAME_LONG                               = "extra-evaluation-time";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_NAME_BOTH                               = ARG_EXTRA_EVALUATION_TIME_NAME_LONG + ",e";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_DESCRIPTION                             = "the maximum number of minutes the application can wait before finishing evaluation";

const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_NAME_LONG                                  = "model-checker-type";
const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_NAME_BOTH                                  = ARG_MODEL_CHECKER_TYPE_NAME_LONG + ",m";
const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_DESCRIPTION                                = "the type of the model checker (0 = Probabilistic black-box, 1 = Statistical, 2 = Approximate probabilistic, 3 = Bayesian)";

const std::string   CommandLineModelChecking::ARG_HELP_NAME_LONG                                                = "help";
const std::string   CommandLineModelChecking::ARG_HELP_NAME_BOTH                                                = ARG_HELP_NAME_LONG + ",h";
const std::string   CommandLineModelChecking::ARG_HELP_DESCRIPTION                                              = "display help message (describing the meaning and usage of each command line argument)";

const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG                            = "extra-evaluation-program";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_NAME_BOTH                            = ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG + ",p";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_DESCRIPTION                          = "the program which will be executed whenever extra evaluation (and input traces) is required";

const std::string   CommandLineModelChecking::ARG_VERBOSE_NAME_LONG                                             = "verbose";
const std::string   CommandLineModelChecking::ARG_VERBOSE_NAME_BOTH                                             = ARG_VERBOSE_NAME_LONG + ",v";
const std::string   CommandLineModelChecking::ARG_VERBOSE_DESCRIPTION                                           = "if this flag is set detailed evaluation results will be displayed";

const std::string   CommandLineModelChecking::ARG_TYPE_I_ERROR_NAME_LONG                                        = "type-I-error";
const std::string   CommandLineModelChecking::ARG_TYPE_I_ERROR_DESCRIPTION                                      = "the probability of type I errors";

const std::string   CommandLineModelChecking::ARG_TYPE_II_ERROR_NAME_LONG                                       = "type-II-error";
const std::string   CommandLineModelChecking::ARG_TYPE_II_ERROR_DESCRIPTION                                     = "the probability of type II errors";

const std::string   CommandLineModelChecking::ARG_DELTA_NAME_LONG                                               = "delta";
const std::string   CommandLineModelChecking::ARG_DELTA_DESCRIPTION                                             = "the upper bound on the probability to deviate from the true probability";

const std::string   CommandLineModelChecking::ARG_EPSILON_NAME_LONG                                             = "epsilon";
const std::string   CommandLineModelChecking::ARG_EPSILON_DESCRIPTION                                           = "the considered deviation from the true probability";

const std::string   CommandLineModelChecking::ARG_ALPHA_NAME_LONG                                               = "alpha";
const std::string   CommandLineModelChecking::ARG_ALPHA_DESCRIPTION                                             = "the alpha shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_BETA_NAME_LONG                                                = "beta";
const std::string   CommandLineModelChecking::ARG_BETA_DESCRIPTION                                              = "the beta shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG                              = "bayes-factor-threshold";
const std::string   CommandLineModelChecking::ARG_BAYES_FACTOR_THRESHOLD_DESCRIPTION                            = "the Bayes factor threshold used to fix the confidence level of the answer";

const std::string   CommandLineModelChecking::HELP_NAME_LABEL                                                   = "NAME:";
const std::string   CommandLineModelChecking::HELP_NAME_MSG                                                     = "    Mudi - Multidimensional model checker";
const std::string   CommandLineModelChecking::HELP_USAGE_LABEL                                                  = "USAGE:";
const std::string   CommandLineModelChecking::HELP_USAGE_MSG                                                    = "    bin/Mudi <required-arguments> [<optional-arguments>] <model-checking-type-specific-arguments>";

const std::string   CommandLineModelChecking::MSG_MODEL_CHECKING_HELP_REQUESTED                                 = "A request for displaying help information was issued.";

const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME                        = "Probabilistic black-box";
const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS                  = "None";

const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_NAME                                    = "Statistical";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN                        = "Probability of type I errors (false negatives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE                       = " and of type II errors (false positives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_END                          = ".";

const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_NAME                      = "Approximate probabilistic";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_BEGIN          = "Upper bound on probability to deviate more than epsilon = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_MIDDLE         = " from the true probability is delta = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_END            = ".";

const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_NAME                                       = "Bayesian";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_BEGIN                           = "Beta distribution prior shape parameters alpha = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE1                         = " and beta = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE2                         = ". Bayes factor threshold = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_END                             = ".";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_ALLOWED_ARGUMENTS                                  = "";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_REQUIRED_ARGUMENTS                                 = "REQUIRED ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_OPTIONAL_ARGUMENTS                                 = "OPTIONAL ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS              = "MODEL CHECKING TYPE SPECIFIC ARGUMENTS";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_PROBABILISTIC_BLACK_BOX_MODEL_CHECKER_ARGUMENTS    = "Probabilistic black-box";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS                = "Statistical";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS  = "Approximate probabilistic";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS                   = "Bayesian";
