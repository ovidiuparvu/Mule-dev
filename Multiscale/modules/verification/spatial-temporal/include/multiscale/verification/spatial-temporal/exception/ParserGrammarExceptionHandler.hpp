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
                 * \param initialString     The initial std::string
                 * \param errorString       A substd::string of the initial std::string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static void handleUnexpectedTokenException(const std::string &initialString, const std::string &errorString,
                                                           const std::string &expectedToken);

                //! Handle the exception when an invalid probability was encountered
                /*!
                 * \param initialString     The initial std::string
                 * \param errorString       A substd::string of the initial std::string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static void handleProbabilityException(const std::string &initialString, const std::string &errorString,
                                                       const std::string &expectedToken);

                //! Handle the exception when wrong input is provided
                /*!
                 * \param initialString The initial std::string
                 * \param errorString   Error std::string
                 */
                static void handleUnparseableInputException(const std::string &initialString, const std::string &errorString);

                //! Handle the exception when extra input is provided
                /*!
                 * \param initialString The initial std::string
                 * \param extraInput    Extra input
                 */
                static void handleExtraInputException(const std::string &initialString, const std::string &extraInput);

            private:

                //! Handle the case where an unexpected token was found in the std::string
                /*!
                 * \param initialString     The initial std::string
                 * \param errorString       A substd::string of the initial std::string which starts from the error position
                 * \param expectedToken     The token which should replace the error token
                 */
                static std::string handleUnexpectedTokenInString(const std::string &initialString, const std::string &errorString,
                                                                 const std::string &expectedToken);

                //! Handle the case where an expected token was not encountered at the end of the std::string
                /*!
                 * \param initialString     The initial std::string
                 * \param expectedToken     The token which should replace the error token
                 */
                static std::string handleExpectedTokenAtEndOfString(const std::string &initialString,
                                                                    const std::string &expectedToken);

                //! Return the generic introductory error message
                static std::string getIntroductoryErrorMessage();

        };

    };

};



#endif
