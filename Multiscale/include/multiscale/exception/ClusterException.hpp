#ifndef CLUSTEREXCEPTION_HPP
#define CLUSTEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Cluster instances
    class ClusterException : public MultiscaleException {

        public:

            ClusterException(const string &file, int line, const string &msg)
                             : MultiscaleException(file, line, msg) {}
            ClusterException(const string &file, int line, const char *msg)
                             : MultiscaleException(file, line, msg) {}

    };

};

#endif
