#ifndef MODELCHECKINGOUTPUTWRITER_HPP
#define MODELCHECKINGOUTPUTWRITER_HPP

namespace multiscale {

    namespace verification {

        //! Class used to output the model checkers progress
        class ModelCheckingOutputWriter {

            public:

                //! Print a message informing the user which logic property will be parsed
                /*!
                 * \param logicProperty The given logic property
                 */
                static void printParsingLogicPropertyMessage(const std::string &logicProperty);

                //! Print a message with the results of checking if the given property holds
                /*!
                 * \param result        The result indicating if the logic property holds (with a given probability and/or confidence)
                 * \param logicProperty The logic property to be verified
                 */
                static void printModelCheckingResultMessage(const std::string &result,
                                                            const std::string &logicProperty);

                //! Print a success message
                static void printSuccessMessage();

                //! Print a fail message
                static void printFailMessage();

            private:

                // Constants
                static const std::string MSG_PARSING;
                static const std::string MSG_RESULT;
                static const std::string MSG_SUCCESS;
                static const std::string MSG_FAIL;

        };

    };

};

#endif
