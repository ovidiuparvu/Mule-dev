#ifndef DETECTOREXCEPTION_HPP_
#define DETECTOREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Detector class
    class DetectorException : public runtime_error {

        public:

            DetectorException(const string &msg) : runtime_error(msg) {}
            DetectorException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
