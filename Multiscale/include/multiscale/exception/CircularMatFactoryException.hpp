#ifndef CIRCULARMATFACTORYEXCEPTION_HPP_
#define CIRCULARMATFACTORYEXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CircularMatFactory instances
    class CircularMatFactoryException : public runtime_error {

        public:

            CircularMatFactoryException(const string &msg) : runtime_error(msg) {}
            CircularMatFactoryException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
