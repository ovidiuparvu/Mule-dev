#ifndef ENTITYEXCEPTION_HPP
#define ENTITYEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Entity instances
    class EntityException : public MultiscaleException {

        public:

            EntityException(const string &file, int line, const string &msg)
                            : MultiscaleException(file, line, msg) {}
            EntityException(const string &file, int line, const char *msg)
                            : MultiscaleException(file, line, msg) {}

    };

};

#endif
