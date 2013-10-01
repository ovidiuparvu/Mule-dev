#ifndef MATFACTORYEXCEPTION_HPP
#define MATFACTORYEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the MatFactory class
    class MatFactoryException : public MultiscaleException {

        public:

            MatFactoryException(const string &file, int line, const string &msg)
                                : MultiscaleException(file, line, msg) {}
            MatFactoryException(const string &file, int line, const char *msg)
                                : MultiscaleException(file, line, msg) {}

    };

};

#endif
