#ifndef CARTESIANTOCONCENTRATIONSCONVERTEREXCEPTION_HPP
#define CARTESIANTOCONCENTRATIONSCONVERTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CartesianToConcentrationsConverter class
    class CartesianToConcentrationsConverterException : public MultiscaleException {

        public:

            CartesianToConcentrationsConverterException(const string &file, int line, const string &msg)
                                                        : MultiscaleException(file, line, msg) {}
            CartesianToConcentrationsConverterException(const string &file, int line, const char *msg)
                                                        : MultiscaleException(file, line, msg) {}

    };

};

#endif
