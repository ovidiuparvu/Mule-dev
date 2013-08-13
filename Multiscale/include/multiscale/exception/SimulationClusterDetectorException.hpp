#ifndef SIMULATIONCLUSTERDETECTOREXCEPTION_HPP_
#define SIMULATIONCLUSTERDETECTOREXCEPTION_HPP_

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the SimulationClusterDetector instances
    class SimulationClusterDetectorException : public runtime_error {

        public:

            SimulationClusterDetectorException(const string &msg) : runtime_error(msg) {}
            SimulationClusterDetectorException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
