#ifndef POLARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP
#define POLARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the PolarCsvToInputFilesConverter class
    class PolarCsvToInputFilesConverterException : public MultiscaleException {

        public:

            PolarCsvToInputFilesConverterException(const string &file, int line, const string &msg)
                                                   : MultiscaleException(file, line, msg) {}
            PolarCsvToInputFilesConverterException(const string &file, int line, const char *msg)
                                                   : MultiscaleException(file, line, msg) {}

    };

};

#endif
