#ifndef PARSERGRAMMARUNPARSEABLEINPUTEXCEPTION_HPP
#define PARSERGRAMMARUNPARSEABLEINPUTEXCEPTION_HPP

#include <string>

using namespace multiscale;


namespace multiscale {

    namespace verification {

        //! Class for representing "unparseable input" exceptions in the parsing process
        class ParserGrammarUnparseableInputException {

            private:

                std::string errorString;    /*!< The substring from the original string starting with
                                                 the index of the error token */

            public:

                ParserGrammarUnparseableInputException(const std::string &errorString) {
                    this->errorString = errorString;
                }

                //! Get the error string
                std::string getErrorString() const {
                    return errorString;
                }

        };

    };

};



#endif
