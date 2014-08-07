#ifndef MODELCHECKINGOUTPUTWRITER_HPP
#define MODELCHECKINGOUTPUTWRITER_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Class used to output the model checkers progress
        class ModelCheckingOutputWriter {

            public:

                //! Print the model checker introduction message considering the given model checker details
                /*!
                 * \param modelCheckerType          The type of the model checker
                 * \param modelCheckerParameters    The model checking parameters
                 */
                static void printIntroductionMessage(const std::string &modelCheckerType,
                                                     const std::string &modelCheckerParameters);

                //! Print the model checker initialisation message
                /*!
                 * \param logicProperty         The path to the input file containing logic properties
                 * \param tracesFolderPath      The path to the folder containing the traces
                 * \param extraEvaluationTime   The number of extra minutes which the application will wait for new traces to be provided and evaluated
                 */
                static void printInitialisationMessage(const std::string &logicProperty,
                                                       const std::string &tracesFolderPath,
                                                       unsigned long extraEvaluationTime);

                //! Print an introduction message informing the user that the logic properties will be parsed
                static void printParsingLogicPropertiesBeginMessage();

                //! Print a message informing the user which logic property will be parsed
                /*!
                 * \param logicProperty The given logic property
                 */
                static void printParsingLogicPropertyMessage(const std::string &logicProperty);

                //! Print a closing message after the logic properties were parsed
                static void printParsingLogicPropertiesEndMessage();

                //! Print a message informing the user that the model checking execution has started
                static void printStartModelCheckingExecutionMessage();

                //! Print a message informing the user which trace will be evaluated next by the model checkers
                /*!
                 * \param tracePath     The path to the spatial-temporal trace
                 */
                static void printStartTraceEvaluationMessage(const std::string &tracePath);

                //! Print a message informing the user that the extra evaluation program located at the given path will be executed
                /*!
                 * \param programPath    The path to the extra evaluation program
                 */
                static void printExecuteExtraEvaluationProgramMessage(const std::string &programPath);

                //! Print a message informing the user that the model checking execution is suspended for timeOut seconds
                /*! Additionally let the user know that the list of traces is updated after the timeout
                 *
                 * \param timeOut   The timeout value
                 */
                static void printTimeoutMessage(unsigned long timeOut);

                //! Print an introduction message informing the user that the model checking results will be displayed
                static void printModelCheckingResultsIntroductionMessage();

                //! Print a message with the results of checking if the given property holds
                /*!
                 * \param doesPropertyHold  The flag indicating if the logic property holds (with a given probability and/or confidence)
                 * \param detailedResult    The detailed result report indicating if the logic property holds (with a given probability and/or confidence)
                 * \param logicProperty     The logic property to be verified
                 */
                static void printModelCheckingResultMessage(bool doesPropertyHold,
                                                            const std::string &detailedResult,
                                                            const std::string &logicProperty);

                //! Print for each logic property the traces for which the evaluation result was true/false
                /*!
                 * \param logicProperties   The collection of logic properties
                 * \param tracesPaths       The collection of trace paths
                 * \param evaluationResults The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printDetailedEvaluationResults(const std::vector<std::string> &logicProperties,
                                                           const std::vector<std::string> &tracesPaths,
                                                           const std::vector<std::vector<bool>> &evaluationResults);

                //! Print a success message
                static void printSuccessMessage();

                //! Print a fail message
                static void printFailedMessage();

            private:

                //! Print the given logic property in the context of a result message
                /*!
                 * \param logicProperty The logic property
                 */
                static void printLogicPropertyForResult(const std::string &logicProperty);

                //! Print the given logic property in the context of the provided tag
                /*!
                 * \param logicProperty The given logic property
                 * \param tag           The given tag
                 */
                static void printLogicPropertyWithTag(const std::string &logicProperty,
                                                      const std::string &tag);

                //! Print if the logic property verified by the model checker holds in the context of a result message
                /*!
                 * \param doesPropertyHold  Flag indicating if the logic property holds
                 */
                static void printModelCheckingResult(bool doesPropertyHold);

                //! Print the detailed result of the model checking procedure
                /*
                 * \param doesPropertyHold  The flag indicating if the logic property holds (with a given probability and/or confidence)
                 * \param detailedResult    The detailed result report indicating if the logic property holds (with a given probability and/or confidence)
                 */
                static void printModelCheckingDetailedResult(bool doesPropertyHold,
                                                             const std::string &detailedResult);

                //! Print an introduction message informing the user that the detailed evaluation results will be printed
                static void printDetailedEvaluationResultsIntroductionMessage();

                //! Print the detailed evaluation results for the given logic properties and traces
                /*!
                 * \param logicProperties   The collection of logic properties
                 * \param tracesPaths       The collection of trace paths
                 * \param evaluationResults The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printDetailedEvaluationResultsForLogicProperties(const std::vector<std::string> &logicProperties,
                                                                             const std::vector<std::string> &tracesPaths,
                                                                             const std::vector<std::vector<bool>> &evaluationResults);

                //! Print the detailed evaluation results for the given logic property
                /*!
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracesPaths           The collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printLogicPropertyDetailedEvaluationResults(const std::size_t &logicPropertyIndex,
                                                                        const std::vector<std::string> &tracesPaths,
                                                                        const std::vector<std::vector<bool>> &evaluationResults);

                //! Print the detailed evaluation results for the given logic property
                /*!
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracesPaths           The collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printDetailedEvaluationResults(const std::size_t &logicPropertyIndex,
                                                           const std::vector<std::string> &tracesPaths,
                                                           const std::vector<std::vector<bool>> &evaluationResults);

                //! Check if the trace was evaluated for the given logic property
                /*!
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracePathIndex        The index of the trace path in the collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static bool isTraceEvaluatedForLogicProperty(const std::size_t &logicPropertyIndex,
                                                             const std::size_t &tracePathIndex,
                                                             const std::vector<std::vector<bool>> &evaluationResults);

                //! Print the detailed evaluation result for the given logic property and trace
                /*!
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracePath             The path to the spatial temporal trace
                 * \param tracePathIndex        The index of the trace path in the collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printDetailedTraceEvaluationResult(const std::size_t &logicPropertyIndex,
                                                               const std::string &tracePath,
                                                               const std::size_t &tracePathIndex,
                                                               const std::vector<std::vector<bool>> &evaluationResults);

                //! Print the trace path with the associated evaluation result
                /*!
                 * \param tracePath         The path to the spatial temporal trace
                 * \param evaluationResult  The evaluation result
                 */
                static void printTraceEvaluationResult(const std::string &tracePath, bool evaluationResult);

                //! Print the summary of the evaluation results for the given logic property
                /*!
                 * Print a message informing the user how many traces out of the total number
                 * of traces evaluated to true for the given logic property.
                 *
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracesPaths           The collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static void printEvaluationResultsSummary(const std::size_t &logicPropertyIndex,
                                                          const std::vector<std::string> &tracesPaths,
                                                          const std::vector<std::vector<bool>> &evaluationResults);

                //! Update the summary evaluation results considering the logic property, trace and evaluation results
                /*!
                 * \param logicPropertyIndex        The index of the logic property in the collection of logic properties
                 * \param tracePathIndex            The index of the trace path in the collection of trace paths
                 * \param evaluationResults         The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 * \param nrOfEvaluatedTraces       The number of evaluated traces
                 * \param nrOfTracesEvaluatedTrue   The number of traces evaluated true
                 */
                static void updateSummaryEvaluationResults(const std::size_t &logicPropertyIndex,
                                                           const std::size_t &tracePathIndex,
                                                           const std::vector<std::vector<bool>> &evaluationResults,
                                                           size_t &nrOfEvaluatedTraces,
                                                           size_t &nrOfTracesEvaluatedTrue);

                //! Check if the trace was evaluated to true for the given logic property
                /*!
                 * \param logicPropertyIndex    The index of the logic property in the collection of logic properties
                 * \param tracePathIndex        The index of the trace path in the collection of trace paths
                 * \param evaluationResults     The evaluation results (i.e. a two-dimensional array of size |logicProperties| x |2 * |traces|| where the first boolean value associated to a (logicProperty, trace) pair states if the logic property was evaluated for that trace and the second one stores the evaluation value
                 */
                static bool isTraceEvaluatedTrueForLogicProperty(const std::size_t &logicPropertyIndex,
                                                                 const std::size_t &tracePathIndex,
                                                                 const std::vector<std::vector<bool>> &evaluationResults);

                //! Print the summary of the evaluation results for the given logic property
                /*!
                 * Print a message informing the user how many traces out of the total number
                 * of traces evaluated to true for the given logic property.
                 *
                 * \param nrOfTraces        The total number of traces
                 * \param nrOfCorrectTraces The number of traces out of the total number of traces which were evaluated to true
                 */
                static void printEvaluationResultsSummary(std::size_t nrOfTraces, std::size_t nrOfCorrectTraces);

                //! Print a message with the given tag and colour depending on the truth value
                /*! If the truthValue is true then the tag colour is green, otherwise red
                 *
                 * \param message       The given message
                 * \param tag           The given tag
                 * \param truthValue    Boolean flag depending on which the tag colour is set
                 */
                static void printTruthValueDependentMessage(const std::string &message,
                                                            const std::string &tag,
                                                            bool truthValue);

                //! Print a line containing a result tag and no content
                static void printResultTag();

                //! Print a line containing a separator tag
                static void printSeparatorTag();

            private:

                // Constants
                static const std::string TAG_INTRO;
                static const std::string TAG_INIT;
                static const std::string TAG_PARSING;
                static const std::string TAG_EXECUTE;
                static const std::string TAG_TIMEOUT;
                static const std::string TAG_RESULT;
                static const std::string TAG_DETAILS;
                static const std::string TAG_SUCCESS;
                static const std::string TAG_FAILED;
                static const std::string TAG_TRUE;
                static const std::string TAG_FALSE;
                static const std::string TAG_SEPARATOR;

                static const std::string MSG_INTRO_NAME;
                static const std::string MSG_INTRO_COPYRIGHT;
                static const std::string MSG_INTRO_MODEL_CHECKING_TYPE;
                static const std::string MSG_INTRO_MODEL_CHECKING_PARAMETERS;
                static const std::string MSG_INTRO_CONTACT;

                static const std::string MSG_INIT_EXECUTION_PARAMETERS;
                static const std::string MSG_INIT_LOGIC_PROPERTIES_PATH;
                static const std::string MSG_INIT_TRACES_FOLDER_PATH;
                static const std::string MSG_INIT_EXTRA_EVALUATION_TIME;

                static const std::string MSG_PARSING_INTRODUCTION;

                static const std::string MSG_START_MODEL_CHECKING_EXECUTION;
                static const std::string MSG_START_TRACE_EVALUATION;
                static const std::string MSG_START_EXTRA_EVALUATION_PROGRAM_EXECUTION;
                static const std::string MSG_EXECUTION_TIMEOUT_BEGIN;
                static const std::string MSG_EXECUTION_TIMEOUT_END;

                static const std::string MSG_RESULTS_INTRODUCTION;

                static const std::string MSG_EVALUATION_RESULTS_INTRODUCTION;
                static const std::string MSG_EVALUATION_SUMMARY_BEGIN;
                static const std::string MSG_EVALUATION_SUMMARY_END;

                static const std::string MSG_LOGIC_PROPERTY_HOLDS;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_TRUE;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_FALSE;

        };

    };

};


#endif
