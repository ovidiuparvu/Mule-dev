#ifndef PARSERGRAMMAREXCEPTIONHANDLER_HPP
#define PARSERGRAMMAREXCEPTIONHANDLER_HPP

#include "multiscale/exception/InvalidInputException.hpp"

#include <string>

using namespace multiscale;


namespace multiscale {

    namespace verification {

        //! Class for handling parser grammar exceptions
        class ParserGrammarExceptionHandler {

            public:

                //! Handle the exception when an unexpected token was encountered
                /*!
                 * \param initialString     The initial string
                 * \param errorString       A substring of the initial string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static void handleUnexpectedTokenException(const std::string &initialString, const std::string &errorString,
                                                           const std::string &expectedToken);

                //! Handle the exception when an invalid probability was encountered
                /*!
                 * \param initialString     The initial string
                 * \param errorString       A substring of the initial string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static void handleProbabilityException(const std::string &initialString, const std::string &errorString,
                                                       const std::string &expectedToken);

                //! Handle the exception when wrong input is provided
                /*!
                 * \param initialString The initial string
                 * \param errorString   Error string
                 */
                static void handleUnparseableInputException(const std::string &initialString, const std::string &errorString);

                //! Handle the exception when extra input is provided
                /*!
                 * \param initialString The initial string
                 * \param extraInput    Extra input
                 */
                static void handleExtraInputException(const std::string &initialString, const std::string &extraInput);

            private:

                //! Handle the case where an unexpected token was found in the string
                /*!
                 * \param initialString     The initial string
                 * \param errorString       A substring of the initial string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static std::string handleUnexpectedTokenInString(const std::string &initialString, const std::string &errorString,
                                                                 const std::string &expectedToken);

                //! Handle the case where an expected token was not encountered at the end of the string
                /*!
                 * \param initialString     The initial string
                 * \param expectedToken     The token which should replace the error token
                 */
                static std::string handleExpectedTokenAtEndOfString(const std::string &initialString,
                                                                    const std::string &expectedToken);

                //! Remove the trailing "new line" characters from the end of the string
                /*!
                 * \param inputString   The given input string
                 */
                static std::string trimRight(const std::string &inputString);

                //! Return the generic introductory error message
                static std::string getIntroductoryErrorMessage();

        };

    };

};



#endif
