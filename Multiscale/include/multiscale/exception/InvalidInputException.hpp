#ifndef INVALIDINPUTEXCEPTION_HPP
#define INVALIDINPUTEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing invalid input exceptions
    class InvalidInputException : public multiscale::IOException {

        public:

            InvalidInputException() {}

            explicit InvalidInputException(const std::string &file, int line, const std::string &msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit InvalidInputException(const std::string &file, int line, const char *msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
