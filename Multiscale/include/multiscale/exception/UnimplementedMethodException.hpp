#ifndef UNIMPLEMENTEDMETHODEXCEPTION_HPP
#define UNIMPLEMENTEDMETHODEXCEPTION_HPP

#include "multiscale/exception/AlgorithmException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing unimplemented method exceptions
    class UnimplementedMethodException : public AlgorithmException {

        public:

            UnimplementedMethodException() {}

            explicit UnimplementedMethodException(const string &file, int line, const string &msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            explicit UnimplementedMethodException(const string &file, int line, const char *msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
