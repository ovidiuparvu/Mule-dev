#ifndef RECTANGULARMATFACTORYEXCEPTION_HPP_
#define RECTANGULARMATFACTORYEXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularMatFactory instances
    class RectangularMatFactoryException : public runtime_error {

        public:

            RectangularMatFactoryException(const string &msg) : runtime_error(msg) {}
            RectangularMatFactoryException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
