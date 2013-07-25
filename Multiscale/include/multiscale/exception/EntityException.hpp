#ifndef ENTITYEXCEPTION_HPP
#define ENTITYEXCEPTION_HPP

#include <stdexcept>
#include <string>

using namespace std;

namespace multiscale {

    class EntityException : public runtime_error {

        public:

            EntityException(const string &msg) : runtime_error(msg) {}
            EntityException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
