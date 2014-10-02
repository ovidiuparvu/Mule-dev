#ifndef SPATIALTEMPORALEXCEPTION_HPP
#define SPATIALTEMPORALEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal exception
        class SpatialTemporalException : public UnexpectedBehaviourException {

            public:

                SpatialTemporalException(const string &file, int line, const string &msg) {
                    constructExplanatoryString(file, line, msg);
                }

                SpatialTemporalException(const string &file, int line, const char *msg) {
                    constructExplanatoryString(file, line, msg);
                }

        };

    };

};


#endif
