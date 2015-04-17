#ifndef COMMANDLINEMODELCHECKING_HPP
#define COMMANDLINEMODELCHECKING_HPP

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

#include <boost/program_options.hpp>

using namespace multiscale;
using namespace multiscale::verification;

namespace po = boost::program_options;


namespace multiscale {

    namespace verification {

        //! Class for running model checkers from the command line
        class CommandLineModelChecking {

            private:

                std::string
                    logicQueriesFilepath;               /*!< The path to the logic queries file */
                std::string
                    tracesFolderPath;                   /*!< The path to the folder containing traces */

                unsigned int
                    modelCheckerType;                       /*!< The type of the model checker */

                unsigned long
                    extraEvaluationTime;                    /*!< The number of minutes for which the application waits
                                                                 for new traces to be produced */
                std::string
                    extraEvaluationProgramPath;             /*!< The path to the program which will be
                                                                 executed whenever more traces are required */

                std::string
                    multiscaleArchitectureGraphFilepath;    /*!< The path to the multiscale architecture graph */

                bool
                    shouldVerboseDetailedResults;           /*!< The flag indicating if detailed results should
                                                                 be printed out */

                po::variables_map
                    variablesMap;                           /*!< The map containing <a, v> pairs where a = command
                                                                 line argument and v = value */
                po::options_description
                    allowedArguments;                       /*!< The configuration indicating which command line
                                                                 arguments are allowed */
                po::options_description
                    requiredArguments;                      /*!< The configuration indicating which command line
                                                                 arguments are allowed */
                po::options_description
                    optionalArguments;                      /*!< The configuration indicating which command line
                                                                 arguments are allowed */
                po::options_description
                    modelCheckerTypeSpecificArguments;      /*!< The configuration indicating which command line
                                                                 arguments are allowed */

                std::string
                    modelCheckerTypeName;                   /*!< The name of the model checker type */
                std::string
                    modelCheckerParameters;                 /*!< The parameters specific to the model checker */

                std::shared_ptr<ModelCheckerFactory>
                    modelCheckerFactory;                    /*!< The model checker */
                std::shared_ptr<ModelCheckingManager>
                    modelCheckingManager;                   /*!< The model checking task manager */

            public:

                CommandLineModelChecking();
                ~CommandLineModelChecking();

                //! Initialize the class with the given command line arguments
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                void initialize(int argc, char **argv);

                //! Execute the model checking task
                void execute();

            private:

                //! Check if the provided command line arguments are valid
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                bool areValidArguments(int argc, char **argv);

                //! Initialize the configuration of allowed command line arguments
                void initializeAllowedArgumentsConfiguration();

                //! Initialize the configuration of required command line arguments
                void initializeRequiredArgumentsConfiguration();

                //! Initialize the configuration of optional command line arguments
                void initializeOptionalArgumentsConfiguration();

                //! Initialize the configuration of model checker type specific command line arguments
                void initializeModelCheckerTypeSpecificArgumentsConfiguration();

                //! Initialize the configuration of the statistical model checker command line arguments
                po::options_description initializeStatisticalModelCheckerArgumentsConfiguration();

                //! Initialize the configuration of the approximate probabilistic model checker command line arguments
                po::options_description initializeApproximateProbabilisticModelCheckerArgumentsConfiguration();

                //! Initialize the configuration of the Bayesian model checker command line arguments
                po::options_description initializeBayesianModelCheckerArgumentsConfiguration();

                //! Initialize the configuration of the approximate Bayesian model checker command line arguments
                po::options_description initializeApproximateBayesianModelCheckerArgumentsConfiguration();

                //! Check if the provided command line arguments are valid
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                bool areValidArgumentsConsideringConfiguration(int argc, char **argv);

                //! Parse and store the command line arguments' values in a variables map
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                po::parsed_options parseAndStoreArgumentsValues(int argc, char **argv);

                //! Check if any invalid execution arguments were provided
                /*!
                 * \param parsedArguments   The parsed command line arguments
                 */
                bool areInvalidExecutionArguments(const po::parsed_options &parsedArguments);

                //! Check if the help command line argument is present
                bool isHelpArgumentPresent();

                //! Handle the help request i.e. if the --help flag was provided
                void handleHelpRequest();

                //! Print help message to the console
                void printHelpMessage();

                //! Print the help intro message to the console
                void printHelpIntroMessage();

                //! Print the help contents message to the console
                void printHelpContentsMessage();

                //! Print the help closing message to the console
                void printHelpClosingMessage();

                //! Check if any unrecognized command line arguments are present
                /*!
                 * \param parsedArguments   The parsed command line arguments
                 */
                bool areUnrecognizedArgumentsPresent(const po::parsed_options &parsedArguments);

                //! Check if any invalid model checker type dependent arguments are present
                bool areInvalidModelCheckingArguments();

                //! Check if any model checker type dependent arguments are invalid
                bool areInvalidModelCheckingArgumentsPresent();

                //! Remove the required arguments from the given variables_map
                /*!
                 * \param variablesMap  The map containing all parsed command line arguments
                 */
                void removeRequiredArguments(po::variables_map &variablesMap);

                //! Remove the optional arguments from the given variables_map
                /*!
                 * \param variablesMap  The map containing all parsed command line arguments
                 */
                void removeOptionalArguments(po::variables_map &variablesMap);

                //! Check if the model checking type specific arguments from the given variables_map are invalid
                /*!
                 * \param modelCheckerType  The type of the model checker
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areInvalidModelCheckingTypeSpecificArguments(unsigned int modelCheckerType,
                                                                  po::variables_map &variablesMap);

                //! Check if all model checking type specific arguments are present
                /*!
                 * \param modelCheckerType  The type of the model checker
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areModelCheckingTypeSpecificArgumentsPresent(unsigned int modelCheckerType,
                                                                  const po::variables_map &variablesMap);

                //! Check if the arguments specific to statistical model checking are present
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areStatisticalModelCheckingArgumentsPresent(const po::variables_map &variablesMap);

                //! Check if the arguments specific to approximate probabilistic model checking are present
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areApproximateProbabilisticModelCheckingArgumentsPresent(const po::variables_map &variablesMap);

                //! Check if the arguments specific to Bayesian model checking are present
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areBayesianModelCheckingArgumentsPresent(const po::variables_map &variablesMap);

                //! Check if the arguments specific to approximate Bayesian model checking are present
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                bool areApproximateBayesianModelCheckingArgumentsPresent(const po::variables_map &variablesMap);

                //! Remove the model checking type specific arguments from the given variables_map
                /*!
                 * \param modelCheckerType  The type of the model checker
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                void removeModelCheckingTypeSpecificArguments(unsigned int modelCheckerType,
                                                              po::variables_map &variablesMap);

                //! Remove the statistical model checking arguments from the given variables_map
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                void removeStatisticalModelCheckingArguments(po::variables_map &variablesMap);

                //! Remove the approximate probabilistic model checking arguments from the given variables_map
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                void removeApproximateProbabilisticModelCheckingArguments(po::variables_map &variablesMap);

                //! Remove the Bayesian model checking arguments from the given variables_map
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                void removeBayesianModelCheckingArguments(po::variables_map &variablesMap);

                //! Remove the approximate Bayesian model checking arguments from the given variables_map
                /*!
                 * \param variablesMap      The map containing all parsed command line arguments
                 */
                void removeApproximateBayesianModelCheckingArguments(po::variables_map &variablesMap);

                //! Initialize the class members using the command line arguments
                void initializeClassMembers();

                //! Initialize the class members dependent on required command line arguments
                void initializeRequiredArgumentsDependentClassMembers();

                //! Initialize the class members dependent on optional command line arguments
                void initializeOptionalArgumentsDependentClassMembers();

                //! Initialize the class members dependent on the model checker type
                void initializeModelCheckerTypeDependentClassMembers();

                //! Initialize the model checker
                void initializeModelChecker();

                //! Initialize the probabilistic black box model checker
                void initializeProbabilisticBlackBoxModelChecker();

                //! Initialize the statistical model checker
                void initializeStatisticalModelChecker();

                //! Initialize the approximate probabilistic model checker
                void initializeApproximateProbabilisticModelChecker();

                //! Initialize the Bayesian model checker
                void initializeBayesianModelChecker();

                //! Initialize the approximate Bayesian model checker
                void initializeApproximateBayesianModelChecker();

                //! Initialize the model checking manager
                void initializeModelCheckingManager();

                //! Print the model checking initialisation message
                void printModelCheckingInitialisationMessage();


                // Constants
                static const std::string    ERR_INVALID_COMMAND_LINE_ARGUMENTS;
                static const std::string    ERR_INVALID_MODEL_CHECKING_ARGUMENTS;

                static const std::string    ERR_INVALID_MODEL_CHECKING_TYPE;

                static const std::string    ARG_LOGIC_QUERIES_NAME_LONG;
                static const std::string    ARG_LOGIC_QUERIES_NAME_BOTH;
                static const std::string    ARG_LOGIC_QUERIES_DESCRIPTION;

                static const std::string    ARG_SPATIAL_TEMPORAL_TRACES_NAME_LONG;
                static const std::string    ARG_SPATIAL_TEMPORAL_TRACES_NAME_BOTH;
                static const std::string    ARG_SPATIAL_TEMPORAL_TRACES_DESCRIPTION;
                
                static const std::string    ARG_EXTRA_EVALUATION_TIME_NAME_LONG;
                static const std::string    ARG_EXTRA_EVALUATION_TIME_NAME_BOTH;
                static const std::string    ARG_EXTRA_EVALUATION_TIME_DESCRIPTION;

                static const std::string    ARG_MODEL_CHECKER_TYPE_NAME_LONG;
                static const std::string    ARG_MODEL_CHECKER_TYPE_NAME_BOTH;
                static const std::string    ARG_MODEL_CHECKER_TYPE_DESCRIPTION;

                static const std::string    ARG_HELP_NAME_LONG;
                static const std::string    ARG_HELP_NAME_BOTH;
                static const std::string    ARG_HELP_DESCRIPTION;

                static const std::string    ARG_EXTRA_EVALUATION_PROGRAM_NAME_LONG;
                static const std::string    ARG_EXTRA_EVALUATION_PROGRAM_NAME_BOTH;
                static const std::string    ARG_EXTRA_EVALUATION_PROGRAM_DESCRIPTION;

                static const std::string    ARG_MULTISCALE_ARCHITECTURE_GRAPH_NAME_LONG;
                static const std::string    ARG_MULTISCALE_ARCHITECTURE_GRAPH_NAME_BOTH;
                static const std::string    ARG_MULTISCALE_ARCHITECTURE_GRAPH_DESCRIPTION;

                static const std::string    ARG_VERBOSE_NAME_LONG;
                static const std::string    ARG_VERBOSE_NAME_BOTH;
                static const std::string    ARG_VERBOSE_DESCRIPTION;

                static const std::string    ARG_TYPE_I_ERROR_NAME_LONG;
                static const std::string    ARG_TYPE_I_ERROR_DESCRIPTION;

                static const std::string    ARG_TYPE_II_ERROR_NAME_LONG;
                static const std::string    ARG_TYPE_II_ERROR_DESCRIPTION;

                static const std::string    ARG_DELTA_NAME_LONG;
                static const std::string    ARG_DELTA_DESCRIPTION;

                static const std::string    ARG_EPSILON_NAME_LONG;
                static const std::string    ARG_EPSILON_DESCRIPTION;

                static const std::string    ARG_BAYESIAN_ALPHA_NAME_LONG;
                static const std::string    ARG_BAYESIAN_ALPHA_DESCRIPTION;

                static const std::string    ARG_BAYESIAN_BETA_NAME_LONG;
                static const std::string    ARG_BAYESIAN_BETA_DESCRIPTION;

                static const std::string    ARG_BAYES_FACTOR_THRESHOLD_NAME_LONG;
                static const std::string    ARG_BAYES_FACTOR_THRESHOLD_DESCRIPTION;

                static const std::string    ARG_APPROXIMATE_BAYESIAN_ALPHA_NAME_LONG;
                static const std::string    ARG_APPROXIMATE_BAYESIAN_ALPHA_DESCRIPTION;

                static const std::string    ARG_APPROXIMATE_BAYESIAN_BETA_NAME_LONG;
                static const std::string    ARG_APPROXIMATE_BAYESIAN_BETA_DESCRIPTION;

                static const std::string    ARG_VARIANCE_THRESHOLD_NAME_LONG;
                static const std::string    ARG_VARIANCE_THRESHOLD_DESCRIPTION;

                static const std::string    HELP_NAME_LABEL;
                static const std::string    HELP_NAME_MSG;
                static const std::string    HELP_USAGE_LABEL;
                static const std::string    HELP_USAGE_MSG;
                static const std::string    HELP_DESCRIPTION_LABEL;
                static const std::string    HELP_DESCRIPTION_MSG;
                static const std::string    HELP_AUTHOR_LABEL;
                static const std::string    HELP_AUTHOR_MSG;
                static const std::string    HELP_COPYRIGHT_LABEL;
                static const std::string    HELP_COPYRIGHT_MSG;
                static const std::string    HELP_REPORTING_BUGS_LABEL;
                static const std::string    HELP_REPORTING_BUGS_MSG;

                static const std::string    MSG_MODEL_CHECKING_HELP_REQUESTED;

                static const unsigned int   MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX;
                static const unsigned int   MODEL_CHECKER_TYPE_STATISTICAL;
                static const unsigned int   MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC;
                static const unsigned int   MODEL_CHECKER_TYPE_BAYESIAN;
                static const unsigned int   MODEL_CHECKER_TYPE_APPROXIMATE_BAYESIAN;

                static const std::string    MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_NAME;
                static const std::string    MODEL_CHECKER_PROBABILISTIC_BLACK_BOX_PARAMETERS;

                static const std::string    MODEL_CHECKER_STATISTICAL_NAME;
                static const std::string    MODEL_CHECKER_STATISTICAL_PARAMETERS_BEGIN;
                static const std::string    MODEL_CHECKER_STATISTICAL_PARAMETERS_MIDDLE;
                static const std::string    MODEL_CHECKER_STATISTICAL_PARAMETERS_END;

                static const std::string    MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_NAME;
                static const std::string    MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_BEGIN;
                static const std::string    MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_MIDDLE;
                static const std::string    MODEL_CHECKER_APPROXIMATE_PROBABILISTIC_PARAMETERS_END;

                static const std::string    MODEL_CHECKER_BAYESIAN_NAME;
                static const std::string    MODEL_CHECKER_BAYESIAN_PARAMETERS_BEGIN;
                static const std::string    MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE1;
                static const std::string    MODEL_CHECKER_BAYESIAN_PARAMETERS_MIDDLE2;
                static const std::string    MODEL_CHECKER_BAYESIAN_PARAMETERS_END;

                static const std::string    MODEL_CHECKER_APPROXIMATE_BAYESIAN_NAME;
                static const std::string    MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_BEGIN;
                static const std::string    MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE1;
                static const std::string    MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_MIDDLE2;
                static const std::string    MODEL_CHECKER_APPROXIMATE_BAYESIAN_PARAMETERS_END;

                static const std::string    CONFIG_CAPTION_ALLOWED_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_REQUIRED_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_OPTIONAL_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS;

                static const std::string    CONFIG_CAPTION_PROBABILISTIC_BLACK_BOX_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_APPROXIMATE_BAYESIAN_MODEL_CHECKER_ARGUMENTS;

        };

    };

};


#endif
