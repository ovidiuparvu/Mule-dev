#ifndef PARSERGRAMMARUNEXPECTEDTOKENEXCEPTION_HPP
#define PARSERGRAMMARUNEXPECTEDTOKENEXCEPTION_HPP

#include <string>

using namespace std;


namespace multiscale {

    namespace verification {

        //! Class for representing "unexpected token" exceptions in the parsing process
        class ParserGrammarUnexpectedTokenException {

            private:

                string expectedToken;   /*!< The token which was expected and was not found during parsing */
                string errorString;     /*!< The substring from the original string starting with
                                             the index of the error token*/

            public:

                ParserGrammarUnexpectedTokenException(const string &expectedToken,
                                                      const string &errorString) {
                    this->expectedToken = expectedToken;
                    this->errorString = errorString;
                }

                //! Get the error string
                string getErrorString() const {
                    return errorString;
                }

                //! Get the expected token
                string getExpectedToken() const {
                    return expectedToken;
                }

        };

    };

};



#endif
