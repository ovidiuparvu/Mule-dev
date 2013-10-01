#ifndef CIRCULARMATFACTORYEXCEPTION_HPP
#define CIRCULARMATFACTORYEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CircularMatFactory instances
    class CircularMatFactoryException : public MultiscaleException {

        public:

            CircularMatFactoryException(const string &file, int line, const string &msg)
                                        : MultiscaleException(file, line, msg) {}
            CircularMatFactoryException(const string &file, int line, const char *msg)
                                        : MultiscaleException(file, line, msg) {}

    };

};

#endif
