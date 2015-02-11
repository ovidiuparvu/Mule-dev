#ifndef NUMERICEXCEPTION_HPP
#define NUMERICEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>


namespace multiscale {

    //! Class for representing algorithm exceptions
    class NumericException : public MultiscaleException {

        public:

            NumericException() {}

            explicit NumericException(const std::string &file, int line, const std::string &msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit NumericException(const std::string &file, int line, const char *msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
