#ifndef COMMANDLINEMODELCHECKING_HPP
#define COMMANDLINEMODELCHECKING_HPP

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;

namespace po = boost::program_options;


namespace multiscale {

    namespace verification {

        //! Enumeration used to specify the type of model checker
        enum class ModelCheckerType : int {
            STATISTICAL             = 1,   /*!< Statistical model checker */
            PROBABILISTIC_BLACK_BOX = 2    /*!< Probabilistic black box model checker */
        };


        //! Class for running model checkers from the command line
        class CommandLineModelChecking {

            private:

                std::string                     logicQueriesFilePath;           /*!< The path to the logic queries file */
                std::string                     tracesFolderPath;               /*!< The path to the folder containing traces */

                unsigned long                   extraEvaluationTime;            /*!< The number of minutes for which the application waits
                                                                                     for new traces to be produced */
                std::string                     extraEvaluationProgramPath;     /*!< The path to the program which will be
                                                                                     executed whenever more traces are required */

                bool                            shouldVerboseDetailedResults;   /*!< The flag indicating if detailed results should
                                                                                     be printed out */

                po::variables_map               variablesMap;                   /*!< The map containing <a, v> pairs where a = command
                                                                                     line argument and v = value */
                po::options_description         allowedArguments;               /*!< The configuration indicating which command line
                                                                                     arguments are allowed */

                std::shared_ptr<ModelChecker>   modelChecker;                   /*!< The model checker */
                ModelCheckingManager            modelCheckingManager;           /*!< The model checking task manager */

            public:

                CommandLineModelChecking();
                ~CommandLineModelChecking();

                //! Initialise the class with the given command line arguments
                /*!
                 * \param argc  The number of command line arguments provided
                 * \param argv  The collection of command line arguments
                 */
                void initialise(int argc, char **argv);

                //! Execute the model checking task
                void execute();

            private:

                //! Check if the provided command line arguments are valid
                /*!
                 * \param argc  The number of command line arguments provided
                 * \param argv  The collection of command line arguments
                 */
                bool areValidArgumentsAndSuccessfulInitialisation(int argc, char **argv);

                //! Check if the provided command line arguments are valid and initialise class members
                /*!
                 * \param argc  The number of command line arguments provided
                 * \param argv  The collection of command line arguments
                 */
                bool areValidArguments(int argc, char **argv);

                //! Initialise the configuration of allowed command line arguments
                void initialiseAllowedArgumentsConfiguration();

                //! Parse the command line arguments and store the provided values if all command line arguments were valid
                /*!
                 * \param argc  The number of command line arguments provided
                 * \param argv  The collection of command line arguments
                 */
                bool areArgumentsSuccessfullyParsed(int argc, char **argv);

                //! Check if the help command line argument is present
                bool isHelpArgumentPresent();

                //! Check if any unrecognized command line arguments are present
                bool areUnrecognizedArgumentsPresent();

                //! Check if all model checker type dependent arguments are present
                bool areModelCheckerTypeArgumentsPresent();

                //! Initialise the class members using the command line arguments
                void initialiseClassMembers();

                //! Initialise the class members dependent on required command line arguments
                void initialiseRequiredArgumentsDependentClassMembers();

                //! Initialise the class members dependent on optional command line arguments
                void initialiseOptionalArgumentsDependentClassMembers();

                //! Initialise the class members dependent on the model checker type
                void initialiseModelCheckerTypeDependentClassMembers();

                //! Print the model checking initialisation message
                void printModelCheckingInitialisationMessage();

        };

    };

};

#endif
