#ifndef PARSERGRAMMARUNEXPECTEDTOKENEXCEPTION_HPP
#define PARSERGRAMMARUNEXPECTEDTOKENEXCEPTION_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing "unexpected token" exceptions in the parsing process
        class ParserGrammarUnexpectedTokenException {

            private:

                std::string expectedToken;   /*!< The token which was expected and was not found during parsing */
                std::string errorString;     /*!< The substring from the original string starting with
                                                  the index of the error token */

            public:

                ParserGrammarUnexpectedTokenException(const std::string &expectedToken,
                                                      const std::string &errorString) {
                    this->expectedToken = expectedToken;
                    this->errorString = errorString;
                }

                //! Get the error string
                std::string getErrorString() const {
                    return errorString;
                }

                //! Get the expected token
                std::string getExpectedToken() const {
                    return expectedToken;
                }

        };

    };

};



#endif
