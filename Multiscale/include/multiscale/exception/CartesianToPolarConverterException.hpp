#ifndef CARTESIANTOPOLARCONVERTEREXCEPTION_HPP
#define CARTESIANTOPOLARCONVERTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CartesianToPolarConverter class
    class CartesianToPolarConverterException : public MultiscaleException {

        public:

            CartesianToPolarConverterException(const string &file, int line, const string &msg)
                                               : MultiscaleException(file, line, msg) {}
            CartesianToPolarConverterException(const string &file, int line, const char *msg)
                                               : MultiscaleException(file, line, msg) {}

    };

};

#endif
