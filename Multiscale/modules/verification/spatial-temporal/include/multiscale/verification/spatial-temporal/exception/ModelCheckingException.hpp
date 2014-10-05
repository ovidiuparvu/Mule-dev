#ifndef MODELCHECKINGEXCEPTION_HPP
#define MODELCHECKINGEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a model checking exception
        class ModelCheckingException : public UnexpectedBehaviourException {

            public:

                explicit ModelCheckingException(const std::string &file, int line, const std::string &msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const std::string &>(file, line, msg);
                }

                explicit ModelCheckingException(const std::string &file, int line, const char *msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const char *>(file, line, msg);
                }

        };

    };

};


#endif
