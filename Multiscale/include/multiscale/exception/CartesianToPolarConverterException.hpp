#ifndef CARTESIANTOPOLARCONVERTEREXCEPTION_HPP_
#define CARTESIANTOPOLARCONVERTEREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the CartesianToPolarConverter class
    class CartesianToPolarConverterException : public runtime_error {

        public:

            CartesianToPolarConverterException(const string &msg) : runtime_error(msg) {}
            CartesianToPolarConverterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
