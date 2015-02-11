#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelCheckerFactory.hpp"
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
const unsigned int multiscale::verification::CommandLineModelChecking::MODEL_CHECKER_TYPE_APPROXIMATE_BAYESIAN      = 4;


CommandLineModelChecking::CommandLineModelChecking()
    : modelCheckerType(0),
      extraEvaluationTime(0),
      shouldVerboseDetailedResults(false),
      allowedArguments(CONFIG_CAPTION_ALLOWED_ARGUMENTS),
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
    requiredArguments.add_options()(ARG_LOGIC_QUERIES_NAME_BOTH.c_str()             , po::value<std::string>()->required()      , (ARG_LOGIC_QUERIES_DESCRIPTION + "\n").c_str())
                                   (ARG_SPATIAL_TEMPORAL_TRACES_NAME_BOTH.c_str()   , po::value<std::string>()->required()      , (ARG_SPATIAL_TEMPORAL_TRACES_DESCRIPTION + "\n").c_str())
                                   (ARG_EXTRA_EVALUATION_TIME_NAME_BOTH.c_str()     , po::value<unsigned long>()->required()    , (ARG_EXTRA_EVALUATION_TIME_DESCRIPTION + "\n").c_str())
                                   (ARG_MODEL_CHECKER_TYPE_NAME_BOTH.c_str()        , po::value<unsigned int>()->required()     , (ARG_MODEL_CHECKER_TYPE_DESCRIPTION + "\n").c_str());
}

void CommandLineModelChecking::initialiseOptionalArgumentsConfiguration() {
    optionalArguments.add_options()(ARG_HELP_NAME_BOTH.c_str()                                                  , (ARG_HELP_DESCRIPTION + "\n").c_str())
                                   (ARG_EXTRA_EVALUATION_PROGRAM_NAME_BOTH.c_str() , po::value<std::string>()   , (ARG_EXTRA_EVALUATION_PROGRAM_DESCRIPTION + "\n").c_str())
                                   (ARG_TYPE_SEMANTICS_TABLE_NAME_BOTH.c_str()     , po::value<std::string>()   , (ARG_TYPE_SEMANTICS_TABLE_DESCRIPTION + "\n").c_str())
                                   (ARG_VERBOSE_NAME_BOTH.c_str()                  , po::bool_switch()          , (ARG_VERBOSE_DESCRIPTION + "\n").c_str());
}

void CommandLineModelChecking::initialiseModelCheckerTypeSpecificArgumentsConfiguration() {
    auto statisticalArguments               = initialiseStatisticalModelCheckerArgumentsConfiguration();
    auto approximateProbabilisticArguments  = initialiseApproximateProbabilisticModelCheckerArgumentsConfiguration();
    auto bayesianArguments                  = initialiseBayesianModelCheckerArgumentsConfiguration();
    auto approximateBayesianArguments       = initialiseApproximateBayesianModelCheckerArgumentsConfiguration();

    modelCheckerTypeSpecificArguments.add(statisticalArguments)
                                     .add(approximateProbabilisticArguments)
                                     .add(bayesianArguments)
                                     .add(approximateBayesianArguments);
}

po::options_description CommandLineModelChecking::initialiseStatisticalModelCheckerArgumentsConfiguration() {
    po::options_description statisticalArguments(CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS);

    statisticalArguments.add_options()(ARG_TYPE_I_ERROR_NAME_LONG.c_str()     , po::value<double>(), (ARG_TYPE_I_ERROR_DESCRIPTION + "\n").c_str())
                                      (ARG_TYPE_II_ERROR_NAME_LONG.c_str()    , po::value<double>(), (ARG_TYPE_II_ERROR_DESCRIPTION + "\n").c_str());

    return statisticalArguments;
}

po::options_description CommandLineModelChecking::initialiseApproximateProbabilisticModelCheckerArgumentsConfiguration() {
    po::options_description approximateProbabilisticArguments(CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS);

    approximateProbabilisticArguments.add_options()(ARG_DELTA_NAME_LONG.c_str()     , po::value<double>(), (ARG_DELTA_DESCRIPTION + "\n").c_str())
                                                   (ARG_EPSILON_NAME_LONG.c_str()   , po::value<double>(), (ARG_EPSILON_DESCRIPTION + "\n").c_str());

    return approximateProbabilisticArguments;
}

po::options_description CommandLineModelChecking::initialiseBayesianModelCheckerArgumentsConfiguration() {
    po::options_description bayesianArguments(CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS);

    bayesianArguments.add_options()(ARG_BAYESIAN_ALPHA_NAME_LONG.c_str()        , po::value<double>(), (ARG_BAYESIAN_ALPHA_DESCRIPTION + "\n").c_str())
                                   (ARG_BAYESIAN_BETA_NAME_LONG.c_str()         , po::value<double>(), (ARG_BAYESIAN_BETA_DESCRIPTION + "\n").c_str())
                                   (ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG.c_str(), po::value<double>(), (ARG_BAYES_FACTOR_THRESHOLD_DESCRIPTION + "\n").c_str());

    return bayesianArguments;
}

po::options_description CommandLineModelChecking::initialiseApproximateBayesianModelCheckerArgumentsConfiguration() {
    po::options_description approximateBayesianArguments(CONFIG_CAPTION_APPROXIMATE_BAYESIAN_MODEL_CHECKER_ARGUMENTS);

    approximateBayesianArguments.add_options()(ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG.c_str() , po::value<double>(), (ARG_BAYESIAN_ALPHA_DESCRIPTION + "\n").c_str())
                                              (ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG.c_str()  , po::value<double>(), (ARG_BAYESIAN_BETA_DESCRIPTION + "\n").c_str())
                                              (ARG_VARIANCE_THRESHOLD_NAME_LONG.c_str()         , po::value<double>(), (ARG_VARIANCE_THRESHOLD_DESCRIPTION + "\n").c_str());

    return approximateBayesianArguments;
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
    printHelpIntroMessage();
    printHelpContentsMessage();
    printHelpClosingMessage();
}

void CommandLineModelChecking::printHelpIntroMessage() {
    std::cout   << std::endl
                << HELP_NAME_LABEL          << std::endl
                << HELP_NAME_MSG            << std::endl
                << std::endl
                << HELP_USAGE_LABEL         << std::endl
                << HELP_USAGE_MSG           << std::endl
                << std::endl
                << HELP_DESCRIPTION_LABEL   << std::endl
                << HELP_DESCRIPTION_MSG     << std::endl;
}

void CommandLineModelChecking::printHelpContentsMessage() {
    std::cout << allowedArguments << std::endl;
}

void CommandLineModelChecking::printHelpClosingMessage() {
    std::cout   << std::endl
                << HELP_AUTHOR_LABEL            << std::endl
                << HELP_AUTHOR_MSG              << std::endl
                << std::endl
                << HELP_COPYRIGHT_LABEL         << std::endl
                << HELP_COPYRIGHT_MSG           << std::endl
                << std::endl
                << HELP_REPORTING_BUGS_LABEL    << std::endl
                << HELP_REPORTING_BUGS_MSG      << std::endl
                << std::endl;
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
    po::variables_map variablesMapCopy = variablesMap;
    unsigned int      modelCheckerType = variablesMap[ARG_MODEL_CHECKER_TYPE_NAME_LONG].as<unsigned int>();

    removeRequiredArguments(variablesMapCopy);
    removeOptionalArguments(variablesMapCopy);

    return areInvalidModelCheckingTypeSpecificArguments(modelCheckerType, variablesMapCopy);
}

void CommandLineModelChecking::removeRequiredArguments(po::variables_map &variablesMap) {
    variablesMap.erase(ARG_LOGIC_QUERIES_NAME_LONG);
    variablesMap.erase(ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG);
    variablesMap.erase(ARG_EXTRA_EVALUATION_TIME_NAME_LONG);
    variablesMap.erase(ARG_MODEL_CHECKER_TYPE_NAME_LONG);
}

void CommandLineModelChecking::removeOptionalArguments(po::variables_map &variablesMap) {
    if (variablesMap.count(ARG_HELP_NAME_LONG)) {
        variablesMap.erase(ARG_HELP_NAME_LONG);
    }

    if (variablesMap.count(ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG)) {
        variablesMap.erase(ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG);
    }

    if (variablesMap.count(ARG_TYPE_SEMANTICS_TABLE_NAME_LONG)) {
        variablesMap.erase(ARG_TYPE_SEMANTICS_TABLE_NAME_LONG);
    }

    if (variablesMap.count(ARG_VERBOSE_NAME_LONG)) {
        variablesMap.erase(ARG_VERBOSE_NAME_LONG);
    }
}

bool CommandLineModelChecking::areInvalidModelCheckingTypeSpecificArguments(unsigned int modelCheckerType,
                                                                            po::variables_map &variablesMap) {
    if (areModelCheckingTypeSpecificArgumentsPresent(modelCheckerType, variablesMap)) {
        removeModelCheckingTypeSpecificArguments(modelCheckerType, variablesMap);

        return (variablesMap.size() > 0);
    } else {
        return true;
    }
}

bool CommandLineModelChecking::areModelCheckingTypeSpecificArgumentsPresent(unsigned int modelCheckerType,
                                                                            const po::variables_map &variablesMap) {
    switch (modelCheckerType) {
        case MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX:
            return true;

        case MODEL_CHECKER_TYPE_STATISTICAL:
            return areStatisticalModelCheckingArgumentsPresent(variablesMap);

        case MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC:
            return areApproximateProbabilisticModelCheckingArgumentsPresent(variablesMap);

        case MODEL_CHECKER_TYPE_BAYESIAN:
            return areBayesianModelCheckingArgumentsPresent(variablesMap);

        case MODEL_CHECKER_TYPE_APPROXIMATE_BAYESIAN:
            return areApproximateBayesianModelCheckingArgumentsPresent(variablesMap);

        default:
            MS_throw(InvalidInputException, ERR_INVALID_MODEL_CHECKING_TYPE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return false;
}

bool CommandLineModelChecking::areStatisticalModelCheckingArgumentsPresent(const po::variables_map &variablesMap) {
    return (
        (variablesMap.count(ARG_TYPE_I_ERROR_NAME_LONG))    &&
        (variablesMap.count(ARG_TYPE_II_ERROR_NAME_LONG))
    );
}

bool CommandLineModelChecking::areApproximateProbabilisticModelCheckingArgumentsPresent(const po::variables_map &variablesMap) {
    return (
        (variablesMap.count(ARG_DELTA_NAME_LONG))   &&
        (variablesMap.count(ARG_EPSILON_NAME_LONG))
    );
}

bool CommandLineModelChecking::areBayesianModelCheckingArgumentsPresent(const po::variables_map &variablesMap) {
    return (
        (variablesMap.count(ARG_BAYESIAN_ALPHA_NAME_LONG))                   &&
        (variablesMap.count(ARG_BAYESIAN_BETA_NAME_LONG))                    &&
        (variablesMap.count(ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG))
    );
}

bool CommandLineModelChecking::areApproximateBayesianModelCheckingArgumentsPresent(const po::variables_map &variablesMap) {
    return (
        (variablesMap.count(ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG))  &&
        (variablesMap.count(ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG))   &&
        (variablesMap.count(ARG_VARIANCE_THRESHOLD_NAME_LONG))
    );
}

void CommandLineModelChecking::removeModelCheckingTypeSpecificArguments(unsigned int modelCheckerType,
                                                                        po::variables_map &variablesMap) {
    switch (modelCheckerType) {
        case MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX:
            break;

        case MODEL_CHECKER_TYPE_STATISTICAL:
            removeStatisticalModelCheckingArguments(variablesMap);
            break;

        case MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC:
            removeApproximateProbabilisticModelCheckingArguments(variablesMap);
            break;

        case MODEL_CHECKER_TYPE_BAYESIAN:
            removeBayesianModelCheckingArguments(variablesMap);
            break;

        case MODEL_CHECKER_TYPE_APPROXIMATE_BAYESIAN:
            removeApproximateBayesianModelCheckingArguments(variablesMap);
            break;

        default:
            MS_throw(InvalidInputException, ERR_INVALID_MODEL_CHECKING_TYPE);
    }
}

void CommandLineModelChecking::removeStatisticalModelCheckingArguments(po::variables_map &variablesMap) {
    variablesMap.erase(ARG_TYPE_I_ERROR_NAME_LONG);
    variablesMap.erase(ARG_TYPE_II_ERROR_NAME_LONG);
}

void CommandLineModelChecking::removeApproximateProbabilisticModelCheckingArguments(po::variables_map &variablesMap) {
    variablesMap.erase(ARG_DELTA_NAME_LONG);
    variablesMap.erase(ARG_EPSILON_NAME_LONG);
}

void CommandLineModelChecking::removeBayesianModelCheckingArguments(po::variables_map &variablesMap) {
    variablesMap.erase(ARG_BAYESIAN_ALPHA_NAME_LONG);
    variablesMap.erase(ARG_BAYESIAN_BETA_NAME_LONG);
    variablesMap.erase(ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG);
}

void CommandLineModelChecking::removeApproximateBayesianModelCheckingArguments(po::variables_map &variablesMap) {
    variablesMap.erase(ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG);
    variablesMap.erase(ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG);
    variablesMap.erase(ARG_VARIANCE_THRESHOLD_NAME_LONG);
}

void CommandLineModelChecking::initialiseClassMembers() {
    initialiseRequiredArgumentsDependentClassMembers();
    initialiseOptionalArgumentsDependentClassMembers();
    initialiseModelCheckerTypeDependentClassMembers();
}

void CommandLineModelChecking::initialiseRequiredArgumentsDependentClassMembers() {
    logicQueriesFilepath  = variablesMap[ARG_LOGIC_QUERIES_NAME_LONG].as<std::string>();
    tracesFolderPath      = variablesMap[ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG].as<std::string>();
    extraEvaluationTime   = variablesMap[ARG_EXTRA_EVALUATION_TIME_NAME_LONG].as<unsigned long>();
    modelCheckerType      = variablesMap[ARG_MODEL_CHECKER_TYPE_NAME_LONG].as<unsigned int>();
}

void CommandLineModelChecking::initialiseOptionalArgumentsDependentClassMembers() {
    if (variablesMap.count(ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG)) {
        extraEvaluationProgramPath = variablesMap[ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG].as<std::string>();
    }

    if (variablesMap.count(ARG_TYPE_SEMANTICS_TABLE_NAME_LONG)) {
        typeSemanticsTableFilepath = variablesMap[ARG_TYPE_SEMANTICS_TABLE_NAME_LONG].as<std::string>();
    }

    if (variablesMap.count(ARG_VERBOSE_NAME_LONG)) {
        shouldVerboseDetailedResults = variablesMap[ARG_VERBOSE_NAME_LONG].as<bool>();
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

        case MODEL_CHECKER_TYPE_APPROXIMATE_BAYESIAN:
            initialiseApproximateBayesianModelChecker();
            break;

        default:
            MS_throw(InvalidInputException, ERR_INVALID_MODEL_CHECKING_TYPE);
    }
}

void CommandLineModelChecking::initialiseProbabilisticBlackBoxModelChecker() {
    modelCheckerFactory = std::make_shared<ProbabilisticBlackBoxModelCheckerFactory>();

    modelCheckerTypeName    = MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME;
    modelCheckerParameters  = MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS;
}

void CommandLineModelChecking::initialiseStatisticalModelChecker() {
    double typeIError   = variablesMap[ARG_TYPE_I_ERROR_NAME_LONG].as<double>();
    double typeIIError  = variablesMap[ARG_TYPE_II_ERROR_NAME_LONG].as<double>();

    modelCheckerFactory = std::make_shared<StatisticalModelCheckerFactory>(typeIError, typeIIError);

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

    modelCheckerFactory = std::make_shared<ApproximateProbabilisticModelCheckerFactory>(delta, epsilon);

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
    double alpha                = variablesMap[ARG_BAYESIAN_ALPHA_NAME_LONG].as<double>();
    double beta                 = variablesMap[ARG_BAYESIAN_BETA_NAME_LONG].as<double>();
    double bayesFactorThreshold = variablesMap[ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG].as<double>();

    modelCheckerFactory = std::make_shared<BayesianModelCheckerFactory>(alpha, beta, bayesFactorThreshold);

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

void CommandLineModelChecking::initialiseApproximateBayesianModelChecker() {
    double alpha                = variablesMap[ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG].as<double>();
    double beta                 = variablesMap[ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG].as<double>();
    double varianceThreshold    = variablesMap[ARG_VARIANCE_THRESHOLD_NAME_LONG].as<double>();

    modelCheckerFactory = std::make_shared<ApproximateBayesianModelCheckerFactory>(
                              alpha, beta, varianceThreshold
                          );

    modelCheckerTypeName    = MODEL_CHECKER_APPROXIMATE_BAYESIAN_NAME;
    modelCheckerParameters  = (
        MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_BEGIN     +
        StringManipulator::toString(alpha)                      +
        MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE1   +
        StringManipulator::toString(beta)                       +
        MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE2   +
        StringManipulator::toString(varianceThreshold)          +
        MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_END
    );
}

void CommandLineModelChecking::initialiseModelCheckingManager() {
    modelCheckingManager = std::make_shared<ModelCheckingManager>(
                               logicQueriesFilepath, tracesFolderPath,
                               extraEvaluationTime, typeSemanticsTableFilepath
                           );

    modelCheckingManager->setExtraEvaluationProgramPath(extraEvaluationProgramPath);
    modelCheckingManager->setShouldPrintDetailedEvaluation(shouldVerboseDetailedResults);
}

void CommandLineModelChecking::printModelCheckingInitialisationMessage() {
    ModelCheckingOutputWriter::printIntroductionMessage  (modelCheckerTypeName, modelCheckerParameters);
    ModelCheckingOutputWriter::printInitialisationMessage(logicQueriesFilepath, tracesFolderPath, extraEvaluationTime);
}


// Constants
const std::string   CommandLineModelChecking::ERR_INVALID_COMMAND_LINE_ARGUMENTS                                = "Invalid command line arguments were provided and the model checker execution was stopped.";
const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_ARGUMENTS                              = "The command line arguments provided for the chosen model checking type are invalid. Please run Mule with the --help flag to determine which arguments you should use.";

const std::string   CommandLineModelChecking::ERR_INVALID_MODEL_CHECKING_TYPE                                   = "The provided model checking type is invalid. Please run Mule with the --help flag to determine which values you can use.";

const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_NAME_LONG                                       = "logic-queries";
const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_NAME_BOTH                                       = ARG_LOGIC_QUERIES_NAME_LONG + ",q";
const std::string   CommandLineModelChecking::ARG_LOGIC_QUERIES_DESCRIPTION                                     = "the path to the spatio-temporal queries input file";

const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG                             = "spatial-temporal-traces";
const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_NAME_BOTH                             = ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG + ",t";
const std::string   CommandLineModelChecking::ARG_SPATIAL_TEMPORAL_TRACES_DESCRIPTION                           = "the path to the folder containing spatio-temporal traces";

const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_NAME_LONG                               = "extra-evaluation-time";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_NAME_BOTH                               = ARG_EXTRA_EVALUATION_TIME_NAME_LONG + ",e";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_TIME_DESCRIPTION                             = "the maximum number of minutes the application can wait before finishing evaluation";

const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_NAME_LONG                                  = "model-checker-type";
const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_NAME_BOTH                                  = ARG_MODEL_CHECKER_TYPE_NAME_LONG + ",m";
const std::string   CommandLineModelChecking::ARG_MODEL_CHECKER_TYPE_DESCRIPTION                                = "the type of the model checker (0 = Probabilistic black-box, 1 = Frequentist statistical, 2 = Frequentist approximate probabilistic (Chernoff-Hoeffding), 3 = Bayesian (statistical hypothesis testing), 4 = Approximate Bayesian (mean and variance estimation))";

const std::string   CommandLineModelChecking::ARG_HELP_NAME_LONG                                                = "help";
const std::string   CommandLineModelChecking::ARG_HELP_NAME_BOTH                                                = ARG_HELP_NAME_LONG + ",h";
const std::string   CommandLineModelChecking::ARG_HELP_DESCRIPTION                                              = "display help message (describing the meaning and usage of each command line argument)";

const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG                            = "extra-evaluation-program";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_NAME_BOTH                            = ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG + ",p";
const std::string   CommandLineModelChecking::ARG_EXTRA_EVALUATION_PROGRAM_DESCRIPTION                          = "the program which will be executed whenever extra evaluation (and input traces) is required";

const std::string   CommandLineModelChecking::ARG_TYPE_SEMANTICS_TABLE_NAME_LONG                                = "type-semantics-table";
const std::string   CommandLineModelChecking::ARG_TYPE_SEMANTICS_TABLE_NAME_BOTH                                = ARG_TYPE_SEMANTICS_TABLE_NAME_LONG + ",s";
const std::string   CommandLineModelChecking::ARG_TYPE_SEMANTICS_TABLE_DESCRIPTION                              = "the type semantics table mapping semantic criteria values (e.g. Organ.Heart) to abstract positive natural numbers";

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

const std::string   CommandLineModelChecking::ARG_BAYESIAN_ALPHA_NAME_LONG                                      = "bayesian-alpha";
const std::string   CommandLineModelChecking::ARG_BAYESIAN_ALPHA_DESCRIPTION                                    = "the alpha shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_BAYESIAN_BETA_NAME_LONG                                       = "bayesian-beta";
const std::string   CommandLineModelChecking::ARG_BAYESIAN_BETA_DESCRIPTION                                     = "the beta shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG                              = "bayes-factor-threshold";
const std::string   CommandLineModelChecking::ARG_BAYES_FACTOR_THRESHOLD_DESCRIPTION                            = "the Bayes factor threshold used to fix the confidence level of the answer";

const std::string   CommandLineModelChecking::ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG                          = "approximate-bayesian-alpha";
const std::string   CommandLineModelChecking::ARG_APPROXIMATE_BAYESIAN_ALPHA_DESCRIPTION                        = "the alpha shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG                           = "approximate-bayesian-beta";
const std::string   CommandLineModelChecking::ARG_APPROXIMATE_BAYESIAN_BETA_DESCRIPTION                         = "the beta shape parameter of the Beta distribution prior";

const std::string   CommandLineModelChecking::ARG_VARIANCE_THRESHOLD_NAME_LONG                                  = "variance-threshold";
const std::string   CommandLineModelChecking::ARG_VARIANCE_THRESHOLD_DESCRIPTION                                = "the variance threshold used to fix the confidence level of the answer";

const std::string   CommandLineModelChecking::HELP_NAME_LABEL                                                   = "NAME:";
const std::string   CommandLineModelChecking::HELP_NAME_MSG                                                     = "    Mule - Multidimensional multiscale model checker";
const std::string   CommandLineModelChecking::HELP_USAGE_LABEL                                                  = "USAGE:";
const std::string   CommandLineModelChecking::HELP_USAGE_MSG                                                    = "    Mule <required-arguments> [<optional-arguments>] <model-checking-type-specific-arguments>";
const std::string   CommandLineModelChecking::HELP_DESCRIPTION_LABEL                                            = "DESCRIPTION:";
const std::string   CommandLineModelChecking::HELP_DESCRIPTION_MSG                                              = "    Mule is a multidimensional (spatial-temporal) multiscale approximate probabilistic model checker. It can be used for two different types of applications. First of all Mule can be employed to validate logic properties against multidimensional multiscale models. Secondly it can be used in reverse mode as a method to query time series data generated by in vivo/vitro experiments. Properties of interest are formalised using a multiscale spatio-temporal logic and their validity is checked using Mule.";
const std::string   CommandLineModelChecking::HELP_AUTHOR_LABEL                                                 = "AUTHOR:";
const std::string   CommandLineModelChecking::HELP_AUTHOR_MSG                                                   = "    The author of this software is Ovidiu Parvu.";
const std::string   CommandLineModelChecking::HELP_COPYRIGHT_LABEL                                              = "COPYRIGHT:";
const std::string   CommandLineModelChecking::HELP_COPYRIGHT_MSG                                                = "    Copyright Ovidiu Parvu 2014.";
const std::string   CommandLineModelChecking::HELP_REPORTING_BUGS_LABEL                                         = "REPORTING BUGS:";
const std::string   CommandLineModelChecking::HELP_REPORTING_BUGS_MSG                                           = "    Please send requests for fixing bugs or recommendations to <ovidiu.parvu[AT]gmail.com>.";

const std::string   CommandLineModelChecking::MSG_MODEL_CHECKING_HELP_REQUESTED                                 = "A request for displaying help information was issued.";

const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME                        = "Probabilistic black-box";
const std::string   CommandLineModelChecking::MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS                  = "None";

const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_NAME                                    = "Frequentist statistical";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN                        = "Probability of type I errors (false negatives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE                       = " and of type II errors (false positives) = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_STATISTICAL_PARAMETERS_END                          = ".";

const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_NAME                      = "Frequentist approximate probabilistic (Chernoff-Hoeffding)";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_BEGIN          = "Upper bound on probability to deviate more than epsilon = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_MIDDLE         = " from the true probability is delta = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_END            = ".";

const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_NAME                                       = "Bayesian (statistical hypothesis testing)";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_BEGIN                           = "Beta distribution prior shape parameters alpha = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE1                         = " and beta = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE2                         = ". Bayes factor threshold = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_BAYESIAN_PARAMETERS_END                             = ".";

const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_BAYESIAN_NAME                           = "Approximate Bayesian (mean and variance estimate)";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_BEGIN               = "Beta distribution prior shape parameters alpha = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE1             = " and beta = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE2             = ". Variance threshold = ";
const std::string   CommandLineModelChecking::MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_END                 = ".";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_ALLOWED_ARGUMENTS                                  = "";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_REQUIRED_ARGUMENTS                                 = "REQUIRED ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_OPTIONAL_ARGUMENTS                                 = "OPTIONAL ARGUMENTS";
const std::string   CommandLineModelChecking::CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS              = "MODEL CHECKING TYPE SPECIFIC ARGUMENTS";

const std::string   CommandLineModelChecking::CONFIG_CAPTION_PROBABILISTIC_BLACK_BOX_MODEL_CHECKER_ARGUMENTS    = MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME;
const std::string   CommandLineModelChecking::CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS                = MODEL_CHECKER_STATISTICAL_NAME;
const std::string   CommandLineModelChecking::CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS  = MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_NAME;
const std::string   CommandLineModelChecking::CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS                   = MODEL_CHECKER_BAYESIAN_NAME;
const std::string   CommandLineModelChecking::CONFIG_CAPTION_APPROXIMATE_BAYESIAN_MODEL_CHECKER_ARGUMENTS       = MODEL_CHECKER_APPROXIMATE_BAYESIAN_NAME;
