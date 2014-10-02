#ifndef MODELCHECKINGEXCEPTION_HPP
#define MODELCHECKINGEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a model checking exception
        class ModelCheckingException : public UnexpectedBehaviourException {

            public:

                ModelCheckingException(const string &file, int line, const string &msg)
                    : UnexpectedBehaviourException(file, line, msg) {}

                ModelCheckingException(const string &file, int line, const char *msg)
                    : UnexpectedBehaviourException(file, line, msg) {}

        };

    };

};


#endif
