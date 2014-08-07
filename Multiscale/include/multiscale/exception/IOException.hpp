#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing input and output exceptions
    class IOException : public MultiscaleException {

        public:

            IOException() {}

            explicit IOException(const string &file, int line, const string &msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit IOException(const string &file, int line, const char *msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
