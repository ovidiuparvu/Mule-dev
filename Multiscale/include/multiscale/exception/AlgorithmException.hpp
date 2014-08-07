#ifndef ALGORITHMEXCEPTION_HPP
#define ALGORITHMEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing algorithm exceptions
    class AlgorithmException : public MultiscaleException {

        public:

            AlgorithmException() {}

            explicit AlgorithmException(const string &file, int line, const string &msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit AlgorithmException(const string &file, int line, const char *msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
