#ifndef CLUSTEREXCEPTION_HPP
#define CLUSTEREXCEPTION_HPP

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Cluster instances
    class ClusterException : public runtime_error {

        public:

            ClusterException(const string &msg) : runtime_error(msg) {}
            ClusterException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
