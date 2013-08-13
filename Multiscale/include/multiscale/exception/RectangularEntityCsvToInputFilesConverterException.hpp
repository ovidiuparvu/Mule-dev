#ifndef RECTANGULARENTITYCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_
#define RECTANGULARENTITYCSVTOINPUTFILESCONVERTEREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the RectangularEntityCsvToInputFilesConverter class
    class RectangularEntityCsvToInputFilesConverterException : public runtime_error {

        public:

            RectangularEntityCsvToInputFilesConverterException(const string &msg) : runtime_error(msg) {}
            RectangularEntityCsvToInputFilesConverterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
