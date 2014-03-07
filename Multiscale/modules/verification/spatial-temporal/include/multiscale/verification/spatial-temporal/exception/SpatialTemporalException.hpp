#ifndef SPATIALTEMPORALEXCEPTION_HPP
#define SPATIALTEMPORALEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal exception
        class SpatialTemporalException : public multiscale::UnexpectedBehaviourException {

            public:

                SpatialTemporalException(const string &file, int line, const string &msg) {
                    explanatoryString = msg;
                }

                SpatialTemporalException(const string &file, int line, const char *msg) {
                    explanatoryString = std::string(msg);
                }

        };

    };

};

#endif
