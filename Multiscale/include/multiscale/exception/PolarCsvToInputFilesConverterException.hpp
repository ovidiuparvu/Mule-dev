#ifndef POLARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_
#define POLARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the PolarCsvToInputFilesConverter class
    class PolarCsvToInputFilesConverterException : public runtime_error {

        public:

            PolarCsvToInputFilesConverterException(const string &msg) : runtime_error(msg) {}
            PolarCsvToInputFilesConverterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
