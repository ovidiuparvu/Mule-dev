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
                 * \param logicPropertyInputFilepath    The path to the input file containing logic properties
                 * \param tracesFolderPath              The path to the folder containing the traces
                 * \param extraEvaluationTime           The number of extra minutes which the application will wait for new traces to be provided and evaluated
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

                // Print an introduction message informing the user that the model checking results will be displayed
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

                //! Print a line containing a result tag and no content
                static void printResultTag();

                //! Print a line containing a separator tag
                static void printSeparatorTag();

            private:

                // Constants
                static const std::string TAG_INTRO;
                static const std::string TAG_INIT;
                static const std::string TAG_PARSING;
                static const std::string TAG_RESULT;
                static const std::string TAG_SUCCESS;
                static const std::string TAG_FAILED;
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

                static const std::string MSG_RESULTS_INTRODUCTION;

                static const std::string MSG_LOGIC_PROPERTY_HOLDS;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_TRUE;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_FALSE;
        };

    };

};

#endif
