#ifndef SPATIALTEMPORALEXCEPTION_HPP
#define SPATIALTEMPORALEXCEPTION_HPP

#include "multiscale/exception/UnexpectedBehaviourException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal exception
        class SpatialTemporalException : public multiscale::UnexpectedBehaviourException {

            public:

                SpatialTemporalException(const string &file, int line, const string &msg)
                                         : multiscale::UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const string &>(file, line, msg);
                }

                SpatialTemporalException(const string &file, int line, const string &startMsg,
                                         const string &msg, const string &endMsg)
                                         : multiscale::UnexpectedBehaviourException(file, line, msg) {
                    string message = startMsg + msg + endMsg;

                    constructExplanatoryString<const string &>(file, line, message);
                }

                SpatialTemporalException(const string &file, int line, const char *msg)
                                         : multiscale::UnexpectedBehaviourException(file, line, msg) {
                    constructExplanatoryString<const char *>(file, line, msg);
                }

                SpatialTemporalException(const string &file, int line, const char *startMsg,
                                         const char *msg, const char *endMsg)
                                         : multiscale::UnexpectedBehaviourException(file, line, msg) {
                    string message = string(startMsg) + string(msg) + string(endMsg);

                    constructExplanatoryString<const char *>(file, line, message.c_str());
                }

        };

    };

};

#endif
