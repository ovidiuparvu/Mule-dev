#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing runtime exceptions
    class RuntimeException : public MultiscaleException {

        public:

            RuntimeException() {}

            explicit RuntimeException(const string &file, int line, const string &msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit RuntimeException(const string &file, int line, const char *msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
