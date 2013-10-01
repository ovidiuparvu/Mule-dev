#ifndef RECTANGULARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP
#define RECTANGULARCSVTOINPUTFILESCONVERTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularCsvToInputFilesConverter class
    class RectangularCsvToInputFilesConverterException : public MultiscaleException {

        public:

            RectangularCsvToInputFilesConverterException(const string &file, int line, const string &msg)
                                                         : MultiscaleException(file, line, msg) {}
            RectangularCsvToInputFilesConverterException(const string &file, int line, const char *msg)
                                                         : MultiscaleException(file, line, msg) {}

    };

};

#endif
