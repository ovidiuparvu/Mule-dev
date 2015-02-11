#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>


namespace multiscale {

    //! Class for representing input and output exceptions
    class IOException : public MultiscaleException {

        public:

            IOException() {}

            explicit IOException(const std::string &file, int line, const std::string &msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit IOException(const std::string &file, int line, const char *msg)
                : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
