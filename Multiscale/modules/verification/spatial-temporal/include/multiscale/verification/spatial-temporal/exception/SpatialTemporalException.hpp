#ifndef SPATIALTEMPORALEXCEPTION_HPP
#define SPATIALTEMPORALEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal exception
        class SpatialTemporalException : public UnexpectedBehaviourException {

            public:

                explicit SpatialTemporalException(const std::string &file, int line, const std::string &msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const std::string &>(file, line, msg);
                }

                explicit SpatialTemporalException(const std::string &file, int line, const char *msg)
                    : UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const char *>(file, line, msg);
                }

        };

    };

};


#endif
