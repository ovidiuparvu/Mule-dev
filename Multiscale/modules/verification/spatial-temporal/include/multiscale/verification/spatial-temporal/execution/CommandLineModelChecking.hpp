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

                std::string                             logicQueriesFilepath;               /*!< The path to the logic queries file */
                std::string                             tracesFolderPath;                   /*!< The path to the folder containing traces */

                unsigned int                            modelCheckerType;                   /*!< The type of the model checker */

                unsigned long                           extraEvaluationTime;                /*!< The number of minutes for which the application waits
                                                                                                 for new traces to be produced */
                std::string                             extraEvaluationProgramPath;         /*!< The path to the program which will be
                                                                                                 executed whenever more traces are required */

                bool                                    shouldVerboseDetailedResults;       /*!< The flag indicating if detailed results should
                                                                                                 be printed out */

                po::variables_map                       variablesMap;                       /*!< The map containing <a, v> pairs where a = command
                                                                                                 line argument and v = value */
                po::options_description                 allowedArguments;                   /*!< The configuration indicating which command line
                                                                                                 arguments are allowed */
                po::options_description                 requiredArguments;                  /*!< The configuration indicating which command line
                                                                                                 arguments are allowed */
                po::options_description                 optionalArguments;                  /*!< The configuration indicating which command line
                                                                                                 arguments are allowed */
                po::options_description                 modelCheckerTypeSpecificArguments;  /*!< The configuration indicating which command line
                                                                                                 arguments are allowed */

                std::string                             modelCheckerTypeName;               /*!< The name of the model checker type */
                std::string                             modelCheckerParameters;             /*!< The parameters specific to the model checker */

                std::shared_ptr<ModelCheckerFactory>    modelCheckerFactory;                /*!< The model checker */
                std::shared_ptr<ModelCheckingManager>   modelCheckingManager;               /*!< The model checking task manager */

            public:

                CommandLineModelChecking();
                ~CommandLineModelChecking();

                //! Initialise the class with the given command line arguments
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                void initialise(int argc, char **argv);

                //! Execute the model checking task
                void execute();

            private:

                //! Check if the provided command line arguments are valid
                /*!
                 * \param argc  The number of provided command line arguments
                 * \param argv  The collection of command line arguments
                 */
                bool areValidArguments(int argc, char **argv);

                //! Initialise the configuration of allowed command line arguments
                void initialiseAllowedArgumentsConfiguration();

                //! Initialise the configuration of required command line arguments
                void initialiseRequiredArgumentsConfiguration();

                //! Initialise the configuration of optional command line arguments
                void initialiseOptionalArgumentsConfiguration();

                //! Initialise the configuration of model checker type specific command line arguments
                void initialiseModelCheckerTypeSpecificArgumentsConfiguration();

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

                //! Check if any unrecognized command line arguments are present
                /*!
                 * \param parsedArguments   The parsed command line arguments
                 */
                bool areUnrecognizedArgumentsPresent(const po::parsed_options &parsedArguments);

                //! Check if any invalid model checker type dependent arguments are present
                bool areInvalidModelCheckingArguments();

                //! Check if any model checker type dependent arguments are invalid
                bool areInvalidModelCheckingArgumentsPresent();

                //! Check if the arguments specific to statistical model checking are present
                /*!
                 * \param allArguments  Flag indicating if all/at least one argument is present
                 */
                bool areStatisticalModelCheckingArgumentsPresent(bool allArguments);

                //! Check if the arguments specific to approximate probabilistic model checking are present
                /*!
                 * \param allArguments  Flag indicating if all/at least one argument is present
                 */
                bool areApproximateProbabilisticModelCheckingArgumentsPresent(bool allArguments);

                //! Check if the arguments specific to Bayesian model checking are present
                /*!
                 * \param allArguments  Flag indicating if all/at least one argument is present
                 */
                bool areBayesianModelCheckingArgumentsPresent(bool allArguments);

                //! Initialise the class members using the command line arguments
                void initialiseClassMembers();

                //! Initialise the class members dependent on required command line arguments
                void initialiseRequiredArgumentsDependentClassMembers();

                //! Initialise the class members dependent on optional command line arguments
                void initialiseOptionalArgumentsDependentClassMembers();

                //! Initialise the class members dependent on the model checker type
                void initialiseModelCheckerTypeDependentClassMembers();

                //! Initialise the model checker
                void initialiseModelChecker();

                //! Initialise the probabilistic black box model checker
                void initialiseProbabilisticBlackBoxModelChecker();

                //! Initialise the statistical model checker
                void initialiseStatisticalModelChecker();

                //! Initialise the approximate probabilistic model checker
                void initialiseApproximateProbabilisticModelChecker();

                //! Initialise the Bayesian model checker
                void initialiseBayesianModelChecker();

                //! Initialise the model checking manager
                void initialiseModelCheckingManager();

                //! Print the model checking initialisation message
                void printModelCheckingInitialisationMessage();


                // Constants
                static const std::string    ERR_INVALID_COMMAND_LINE_ARGUMENTS;
                static const std::string    ERR_INVALID_MODEL_CHECKING_ARGUMENTS;

                static const std::string    ERR_INVALID_MODEL_CHECKING_TYPE;

                static const std::string    HELP_NAME_LABEL;
                static const std::string    HELP_NAME_MSG;
                static const std::string    HELP_USAGE_LABEL;
                static const std::string    HELP_USAGE_MSG;

                static const std::string    MSG_MODEL_CHECKING_HELP_REQUESTED;

                static const unsigned int   MODEL_CHECKER_TYPE_PROBABILISTIC_BLACK_BOX;
                static const unsigned int   MODEL_CHECKER_TYPE_STATISTICAL;
                static const unsigned int   MODEL_CHECKER_TYPE_APPROXIMATE_PROBABILISTIC;
                static const unsigned int   MODEL_CHECKER_TYPE_BAYESIAN;

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

                static const std::string    CONFIG_CAPTION_ALLOWED_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_REQUIRED_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_OPTIONAL_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_MODEL_CHECKER_TYPE_SPECIFIC_ARGUMENTS;

                static const std::string    CONFIG_CAPTION_PROBABILISTIC_BLACK_BOX_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_STATISTICAL_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_APPROXIMATE_PROBABILISTIC_MODEL_CHECKER_ARGUMENTS;
                static const std::string    CONFIG_CAPTION_BAYESIAN_MODEL_CHECKER_ARGUMENTS;

        };

    };

};

#endif
