#ifndef MODELCHECKINGEXCEPTION_HPP
#define MODELCHECKINGEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a model checking exception
        class ModelCheckingException : public multiscale::UnexpectedBehaviourException {

            public:

                ModelCheckingException(const string &file, int line, const string &msg) {
                    explanatoryString = msg;
                }

                ModelCheckingException(const string &file, int line, const char *msg) {
                    explanatoryString = std::string(msg);
                }

        };

    };

};

#endif
