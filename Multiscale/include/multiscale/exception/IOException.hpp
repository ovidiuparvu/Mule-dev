#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing input and output exceptions
    class IOException : public MultiscaleException {

        public:

            IOException(const string &file, int line, const string &msg)
                        : MultiscaleException(file, line, msg) {}
            IOException(const string &file, int line, const char *msg)
                        : MultiscaleException(file, line, msg) {}

    };

};

#endif
