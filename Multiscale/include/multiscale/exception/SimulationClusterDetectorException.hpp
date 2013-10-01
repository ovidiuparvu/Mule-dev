#ifndef SIMULATIONCLUSTERDETECTOREXCEPTION_HPP
#define SIMULATIONCLUSTERDETECTOREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the SimulationClusterDetector instances
    class SimulationClusterDetectorException : public MultiscaleException {

        public:

            SimulationClusterDetectorException(const string &file, int line, const string &msg)
                                               : MultiscaleException(file, line, msg) {}
            SimulationClusterDetectorException(const string &file, int line, const char *msg)
                                               : MultiscaleException(file, line, msg) {}

    };

};

#endif
