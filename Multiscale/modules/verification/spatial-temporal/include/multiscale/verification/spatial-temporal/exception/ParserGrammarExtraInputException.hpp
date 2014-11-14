#ifndef PARSERGRAMMAREXTRAINPUTEXCEPTION_HPP
#define PARSERGRAMMAREXTRAINPUTEXCEPTION_HPP

#include <string>

using namespace multiscale;


namespace multiscale {

    namespace verification {

        //! Class for representing "extra input" exceptions in the parsing process
        class ParserGrammarExtraInputException {

            private:

                std::string errorString;    /*!< The substring from the original string starting with
                                                 the index of the error token */

            public:

                ParserGrammarExtraInputException(const std::string &errorString) {
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
