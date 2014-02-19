#ifndef PARSERGRAMMAREXCEPTIONHANDLER_HPP
#define PARSERGRAMMAREXCEPTIONHANDLER_HPP

#include "multiscale/exception/InvalidInputException.hpp"

#include <string>

using namespace multiscale;
using namespace std;


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
                static void handleUnexpectedTokenException(const string &initialString, const string &errorString,
                                                           const string &expectedToken);

                //! Handle the exception when an invalid probability was encountered
                /*!
                 * \param initialString     The initial string
                 * \param errorString       A substring of the initial string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static void handleProbabilityException(const string &initialString, const string &errorString,
                                                       const string &expectedToken);

                //! Handle the exception when wrong input is provided
                /*!
                 * \param initialString The initial string
                 * \param errorString   Error string
                 */
                static void handleUnparseableInputException(const string &initialString, const string &errorString);

                //! Handle the exception when extra input is provided
                /*!
                 * \param initialString The initial string
                 * \param extraInput    Extra input
                 */
                static void handleExtraInputException(const string &initialString, const string &extraInput);

            private:

                //! Handle the case where an unexpected token was found in the string
                /*!
                 * \param initialString     The initial string
                 * \param errorString       A substring of the initial string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static string handleUnexpectedTokenInString(const string &initialString, const string &errorString,
                                                            const string &expectedToken);

                //! Handle the case where an expected token was not encountered at the end of the string
                /*!
                 * \param initialString     The initial string
                 * \param expectedToken     The token which should replace the error token
                 */
                static string handleExpectedTokenAtEndOfString(const string &initialString,
                                                               const string &expectedToken);

                //! Return the generic introductory error message
                static string getIntroductoryErrorMessage();

        };

    };

};



#endif
