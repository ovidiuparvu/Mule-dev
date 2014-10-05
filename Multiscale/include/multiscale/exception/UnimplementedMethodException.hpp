#ifndef UNIMPLEMENTEDMETHODEXCEPTION_HPP
#define UNIMPLEMENTEDMETHODEXCEPTION_HPP

#include "multiscale/exception/AlgorithmException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing unimplemented method exceptions
    class UnimplementedMethodException : public AlgorithmException {

        public:

            UnimplementedMethodException() {}

            explicit UnimplementedMethodException(const std::string &file, int line, const std::string &msg)
                : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const std::string &>(file, line, msg);
            }

            explicit UnimplementedMethodException(const std::string &file, int line, const char *msg)
                : AlgorithmException(file, line, msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

    };

    // Constants
    const std::string ERR_UNIMPLEMENTED_METHOD = "The method you tried to call is not implemented. Please change.";

};


#endif
