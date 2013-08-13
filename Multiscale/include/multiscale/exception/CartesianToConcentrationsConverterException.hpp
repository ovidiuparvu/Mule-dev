#ifndef CARTESIANTOCONCENTRATIONSCONVERTEREXCEPTION_HPP_
#define CARTESIANTOCONCENTRATIONSCONVERTEREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CartesianToConcentrationsConverter class
    class CartesianToConcentrationsConverterException : public runtime_error {

        public:

            CartesianToConcentrationsConverterException(const string &msg) : runtime_error(msg) {}
            CartesianToConcentrationsConverterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
