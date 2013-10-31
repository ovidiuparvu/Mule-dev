#ifndef UNEXPECTEDBEHAVIOUREXCEPTION_HPP
#define UNEXPECTEDBEHAVIOUREXCEPTION_HPP

#include "multiscale/exception/AlgorithmException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    //! Class for representing unexpected behaviour exceptions
    class UnexpectedBehaviourException : public AlgorithmException {

        public:

            UnexpectedBehaviourException(const string &file, int line, const string &msg)
                                         : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            UnexpectedBehaviourException(const string &file, int line, const char *msg)
                                         : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};

#endif
