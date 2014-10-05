#ifndef FILEOPENEXCEPTION_HPP
#define FILEOPENEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing exceptions when opening a file
    class FileOpenException : public IOException {

        public:

            FileOpenException() {}

            explicit FileOpenException(const std::string &file, int line, const std::string &msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit FileOpenException(const std::string &file, int line, const char *msg)
                : IOException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
