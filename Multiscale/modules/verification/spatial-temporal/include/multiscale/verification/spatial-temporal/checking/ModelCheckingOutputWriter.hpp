#ifndef MODELCHECKINGOUTPUTWRITER_HPP
#define MODELCHECKINGOUTPUTWRITER_HPP

namespace multiscale {

    namespace verification {

        //! Class used to output the model checkers progress
        class ModelCheckingOutputWriter {

            public:

                //! Print the model checker introduction message
                static void printIntroductionMessage();

                //! Print a message informing the user which logic property will be parsed
                /*!
                 * \param logicProperty The given logic property
                 */
                static void printParsingLogicPropertyMessage(const std::string &logicProperty);

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

                //! Print a separator line for the model checking result
                static void printSeparatorForResult();


            private:

                // Constants
                static const std::string TAG_INTRO;
                static const std::string TAG_INIT;
                static const std::string TAG_PARSING;
                static const std::string TAG_RESULT;
                static const std::string TAG_SUCCESS;
                static const std::string TAG_FAILED;
                static const std::string TAG_SEPARATOR;

                static const std::string MSG_EMPTY;

                static const std::string MSG_INTRO_NAME;
                static const std::string MSG_INTRO_COPYRIGHT;

                static const std::string MSG_INTRO_MODEL_CHECKING_DESC;
                static const std::string MSG_INTRO_MODEL_CHECKING_TYPE;
                static const std::string MSG_INTRO_MODEL_CHECKING_PARAMETERS;

                static const std::string MSG_INTRO_CONTACT;

                static const std::string MSG_LOGIC_PROPERTY_HOLDS;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_TRUE;
                static const std::string MSG_LOGIC_PROPERTY_HOLDS_FALSE;
        };

    };

};

#endif
