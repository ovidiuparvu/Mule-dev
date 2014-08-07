#ifndef MODELCHECKINGHELPREQUESTEXCEPTION_HPP
#define MODELCHECKINGHELPREQUESTEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a model checking help request exception
        class ModelCheckingHelpRequestException : public multiscale::UnexpectedBehaviourException {

            public:

                ModelCheckingHelpRequestException(const string &file, int line, const string &msg) {
                    explanatoryString = msg;
                }

                ModelCheckingHelpRequestException(const string &file, int line, const char *msg) {
                    explanatoryString = std::string(msg);
                }

        };

    };

};


#endif
