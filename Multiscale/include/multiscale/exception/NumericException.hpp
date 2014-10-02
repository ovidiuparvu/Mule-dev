#ifndef NUMERICEXCEPTION_HPP
#define NUMERICEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing algorithm exceptions
    class NumericException : public MultiscaleException {

        public:

            NumericException() {}

            explicit NumericException(const string &file, int line, const string &msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit NumericException(const string &file, int line, const char *msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
