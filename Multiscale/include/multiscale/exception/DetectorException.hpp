#ifndef DETECTOREXCEPTION_HPP
#define DETECTOREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Detector class
    class DetectorException : public MultiscaleException {

        public:

            DetectorException(const string &file, int line, const string &msg)
                              : MultiscaleException(file, line, msg) {}
            DetectorException(const string &file, int line, const char *msg)
                              : MultiscaleException(file, line, msg) {}

    };

};

#endif
