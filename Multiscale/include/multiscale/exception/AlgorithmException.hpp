#ifndef ALGORITHMEXCEPTION_HPP
#define ALGORITHMEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing algorithm exceptions
    class AlgorithmException : public MultiscaleException {

        public:

            AlgorithmException(const string &file, int line, const string &msg)
                               : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            AlgorithmException(const string &file, int line, const char *msg)
                               : MultiscaleException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};

#endif
