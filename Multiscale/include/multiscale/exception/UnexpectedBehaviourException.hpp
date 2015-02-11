#ifndef UNEXPECTEDBEHAVIOUREXCEPTION_HPP
#define UNEXPECTEDBEHAVIOUREXCEPTION_HPP

#include "multiscale/exception/AlgorithmException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing unexpected behaviour exceptions
    class UnexpectedBehaviourException : public AlgorithmException {

        public:

            UnexpectedBehaviourException() {}

            explicit UnexpectedBehaviourException(const std::string &file, int line, const std::string &msg)
                : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit UnexpectedBehaviourException(const std::string &file, int line, const char *msg)
                : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

};


#endif
