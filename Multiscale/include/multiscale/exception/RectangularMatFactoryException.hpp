#ifndef RECTANGULARMATFACTORYEXCEPTION_HPP
#define RECTANGULARMATFACTORYEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularMatFactory instances
    class RectangularMatFactoryException : public MultiscaleException {

        public:

            RectangularMatFactoryException(const string &file, int line, const string &msg)
                                           : MultiscaleException(file, line, msg) {}
            RectangularMatFactoryException(const string &file, int line, const char *msg)
                                           : MultiscaleException(file, line, msg) {}

    };

};

#endif
