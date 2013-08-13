#ifndef RECTANGULARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_
#define RECTANGULARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularCsvToInputFilesConverter class
    class RectangularCsvToInputFilesConverterException : public runtime_error {

        public:

            RectangularCsvToInputFilesConverterException(const string &msg) : runtime_error(msg) {}
            RectangularCsvToInputFilesConverterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
