#ifndef RECTANGULARENTITYCSVTOINPUTFILESCONVERTEREXCEPTION_HPP
#define RECTANGULARENTITYCSVTOINPUTFILESCONVERTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularEntityCsvToInputFilesConverter class
    class RectangularEntityCsvToInputFilesConverterException : public MultiscaleException {

        public:

            RectangularEntityCsvToInputFilesConverterException(const string &file, int line, const string &msg)
                                                               : MultiscaleException(file, line, msg) {}
            RectangularEntityCsvToInputFilesConverterException(const string &file, int line, const char *msg)
                                                               : MultiscaleException(file, line, msg) {}

    };

};

#endif
