#ifndef INDEXOUTOFBOUNDSEXCEPTION_HPP
#define INDEXOUTOFBOUNDSEXCEPTION_HPP

#include "multiscale/exception/RuntimeException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing an index out of bounds exception
    class IndexOutOfBoundsException : public RuntimeException {

        public:

        IndexOutOfBoundsException(const string &file, int line, const string &msg)
                        : RuntimeException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

        IndexOutOfBoundsException(const string &file, int line, const char *msg)
                        : RuntimeException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};

#endif