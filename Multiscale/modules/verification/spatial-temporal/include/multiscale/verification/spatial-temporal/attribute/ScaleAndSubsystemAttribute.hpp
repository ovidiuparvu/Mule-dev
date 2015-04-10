#ifndef SCALEANDSUBSYSTEMATTRIBUTE_HPP
#define SCALEANDSUBSYSTEMATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a scale and subsystem attribute
        class ScaleAndSubsystemAttribute {

            public:

                std::string scaleAndSubsystem;    /*!< The considered scale and subsystem */

            public:

                ScaleAndSubsystemAttribute(const std::string &scaleAndSubsystem = ScaleAndSubsystem::DEFAULT_VALUE)
                                          : scaleAndSubsystem(scaleAndSubsystem) {}

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ScaleAndSubsystemAttribute,
    (std::string, scaleAndSubsystem)
)


#endif
