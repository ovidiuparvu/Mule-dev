#ifndef MODELCHECKINGHELPREQUESTEXCEPTION_HPP
#define MODELCHECKINGHELPREQUESTEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a model checking help request exception
        class ModelCheckingHelpRequestException : public UnexpectedBehaviourException {

            public:

                explicit ModelCheckingHelpRequestException(const std::string &file, int line, const std::string &msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const std::string &>(file, line, msg);
                }

                explicit ModelCheckingHelpRequestException(const std::string &file, int line, const char *msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const char *>(file, line, msg);
                }

        };

    };

};


#endif
