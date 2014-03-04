#ifndef TESTEXCEPTION_HPP
#define TESTEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing testing exceptions
    class TestException : public MultiscaleException {

        public:

        TestException(const string &file, int line, const string &msg)
                      : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

        TestException(const string &file, int line, const char *msg)
                      : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};

#endif
