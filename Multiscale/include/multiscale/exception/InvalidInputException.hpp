#ifndef INVALIDINPUTEXCEPTION_HPP
#define INVALIDINPUTEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing invalid input exceptions
    class InvalidInputException : public IOException {

        public:

            InvalidInputException() {}

            explicit InvalidInputException(const string &file, int line, const string &msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit InvalidInputException(const string &file, int line, const char *msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};

#endif
