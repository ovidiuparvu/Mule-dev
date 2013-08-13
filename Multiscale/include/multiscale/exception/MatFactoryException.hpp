#ifndef MATFACTORYEXCEPTION_HPP_
#define MATFACTORYEXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the MatFactory class
    class MatFactoryException : public runtime_error {

        public:

            MatFactoryException(const string &msg) : runtime_error(msg) {}
            MatFactoryException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
