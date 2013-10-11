#ifndef UNIMPLEMENTEDMETHODEXCEPTION_HPP
#define UNIMPLEMENTEDMETHODEXCEPTION_HPP

#include "multiscale/exception/AlgorithmException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing unimplemented method exceptions
    class UnimplementedMethodException : public AlgorithmException {

        public:

            UnimplementedMethodException(const string &file, int line, const string &msg)
                                         : AlgorithmException(file, line, msg) {}
            UnimplementedMethodException(const string &file, int line, const char *msg)
                                         : AlgorithmException(file, line, msg) {}

    };

};

#endif
