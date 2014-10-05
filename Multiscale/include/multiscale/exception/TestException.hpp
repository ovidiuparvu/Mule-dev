#ifndef TESTEXCEPTION_HPP
#define TESTEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>


namespace multiscale {

    //! Class for representing testing exceptions
    class TestException : public MultiscaleException {

        public:

            TestException() {}

            explicit TestException(const std::string &file, int line, const std::string &msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit TestException(const std::string &file, int line, const char *msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
