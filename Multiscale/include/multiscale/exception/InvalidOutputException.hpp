#ifndef INVALIDOUTPUTEXCEPTION_HPP
#define INVALIDOUTPUTEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing invalid output exceptions
    class InvalidOutputException : public IOException {

        public:

        InvalidOutputException() {}

            explicit InvalidOutputException(const std::string &file, int line, const std::string &msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit InvalidOutputException(const std::string &file, int line, const char *msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
