#ifndef INVALIDINPUTEXCEPTION_HPP
#define INVALIDINPUTEXCEPTION_HPP

#include "multiscale/exception/IOException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing invalid input exceptions
    class InvalidInputException : public IOException {

        public:

            InvalidInputException(const string &file, int line, const string &msg)
                                  : IOException(file, line, msg) {}
            InvalidInputException(const string &file, int line, const char *msg)
                                  : IOException(file, line, msg) {}

    };

};

#endif
