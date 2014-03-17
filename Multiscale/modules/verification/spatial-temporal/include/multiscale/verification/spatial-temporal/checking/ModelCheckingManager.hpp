#ifndef MODELCHECKINGMANAGER_HPP
#define MODELCHECKINGMANAGER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <chrono>
#include <ctime>
#include <string>
#include <thread>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for managing the model checking processes
        class ModelCheckingManager {

            private:

                std::chrono::time_point<std::chrono::system_clock>  evaluationStartTime;            /*!< The start time for the evaluation process */
                unsigned long                                       extraEvaluationTime;            /*!< The number of minutes for which the program waits for
                                                                                                         new traces to be added to the trace folder */

                Parser                                              parser;                         /*!< The parser used to verify if logical properties
                                                                                                         are syntactically correct */

                std::vector<std::string>                            logicProperties;                /*!< The collection of logic properties */
                std::vector<AbstractSyntaxTree>                     abstractSyntaxTrees;            /*!< The collection of abstract syntax tree obtained after
                                                                                                         parsing the logic properties */

                LogicPropertyDataReader                             logicPropertyReader;            /*!< The logic property reader */
                SpatialTemporalDataReader                           traceReader;                    /*!< The behaviour/trace reader */

                std::vector<std::shared_ptr<ModelChecker>>          modelCheckers;                  /*!< The collection of model checkers */

            public:

                ModelCheckingManager(const std::string &logicPropertiesFilepath,
                                     const std::string &tracesFolderPath,
                                     unsigned long extraEvaluationTime);
                ~ModelCheckingManager();

                //! Run the model checking tasks
                /*!
                 * \param modelCheckerFactory   The factory used to create model checkers
                 */
                void runModelCheckingTasks(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory);

            private:

                //! Initialise the model checking manager considering the given logic properties input file and extra evaluation time, and print the introduction message
                /*!
                 * \param logicPropertiesFilepath   The path to the logic properties input file
                 * \param extraEvaluationTime       The number of extra minutes allocated for evaluating logic properties
                 */
                void initialise(const std::string &logicPropertiesFilepath,
                                unsigned long extraEvaluationTime);

                //! Initialise the logic properties using the provided input file
                /*!
                 * \param logicPropertiesFilepath The path to the logic properties input file
                 */
                void initialiseLogicProperties(const std::string &logicPropertiesFilepath);

                //! Run the model checking tasks and output the results
                /*!
                 * \param modelCheckerFactory   The factory used to create model checkers
                 */
                void runModelCheckingAndOutputResults(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory);

                //! Parse the logic properties and print message informing the user about this
                void parseLogicPropertiesAndPrintMessage();

                //! Parse the logic properties and create abstract syntax trees whenever a logic property was successfully parsed
                void parseLogicProperties();

                //! Parse the logic property and inform the user if the logic property was syntactically correct
                /*!
                 * \param logicProperty The given logic property
                 */
                bool parseLogicPropertyAndPrintMessages(const std::string &logicProperty);

                //! Parse the given logic property and return true if parsing was successful and false otherwise
                /*! Exceptions are catched in this method
                 *
                 * \param logicProperty The given logic property
                 */
                bool parseLogicProperty(const std::string &logicProperty);

                //! Parse the given logic property and return true if parsing was successful and false otherwise
                /*! Exceptions are not catched in this method
                 *
                 * \param logicProperty The given logic property
                 */
                bool isValidLogicProperty(const std::string &logicProperty);

                //! Print a message stating if the logic property was parsed successfully
                /*!
                 * \param isParsingSuccessful   Flag indicating if the parsing was successful
                 */
                void printParsingMessage(bool isParsingSuccessful);

                //! Create the model checker instances using the provided model checker factory
                /*! Each model checker instance verifies one logic property
                 *
                 * \param modelCheckerFactory   The factory used to create model checkers
                 */
                void createModelCheckers(const std::shared_ptr<ModelCheckerFactory> &modelCheckerFactory);

                //! Run the model checkers and print a message informing the user about it
                void runModelCheckersAndPrintMessage();

                //! Run the model checkers and verify the logic properties
                void runModelCheckers();

                //! Run the model checkers and verify the logic properties for the currently existing traces
                void runModelCheckersForCurrentlyExistingTraces();

                //! Run the model checkers and verify the logic properties considering the given trace
                /*! If none of the model checkers need additional traces then the continueEvaluation flag
                 *  will be set to false.
                 *
                 * \param trace                 The spatial temporal trace used for the logic properties evaluation
                 * \param continueEvaluation    The flag indicating if there is at least one logic property whose truth value was not determined yet and needs to be evaluated considering more spatial temporal traces
                 */
                void runModelCheckersForTrace(const SpatialTemporalTrace &trace,
                                              bool &continueEvaluation);

                //! Run the model checkers and request additional traces
                void runModelCheckersAndRequestAdditionalTraces();

                //! Check if there is evaluation time remaining
                bool isEvaluationTimeRemaining();

                //! Check if there exist model checkers which require extra traces
                bool areUnfinishedModelCheckingTasks();

                //! Wait TRACE_INPUT_REFRESH_TIMEOUT minutes before updating the trace reader
                void waitBeforeRetry();

                //! Update trace reader
                void updateTraceReader();

                //! Output the model checking results and print the message informing the user about this
                void outputModelCheckersResultsAndPrintMessage();

                //! Output the model checking results
                void outputModelCheckersResults();

                //! Output the model checking results for the given model checker
                /*!
                 * \param modelChecker  The given model checker
                 * \param logicProperty The logic property verified by the given model checker
                 */
                void outputModelCheckerResults(const std::shared_ptr<ModelChecker> &modelChecker,
                                               const std::string &logicProperty);


                // Constants
                static const unsigned long TRACE_INPUT_REFRESH_TIMEOUT; /*!< The number of seconds for which the manager waits before updating the trace reader */
                static const unsigned long NR_SECONDS_IN_ONE_MINUTE;

                static const std::string   PARSER_EMPTY_LOGIC_PROPERTY;

        };

    };

};

#endif
