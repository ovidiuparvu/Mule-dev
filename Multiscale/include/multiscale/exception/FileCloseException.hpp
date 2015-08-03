#ifndef FILECLOSEEXCEPTION_HPP
#define FILECLOSEEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing exceptions when closing a file
    class FileCloseException : public IOException {

        public:

        FileCloseException() {}

            explicit FileCloseException(const std::string &file, int line, const std::string &msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit FileCloseException(const std::string &file, int line, const char *msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
