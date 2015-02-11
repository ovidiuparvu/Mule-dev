#ifndef TIMESERIESCOMPONENTATTRIBUTE_HPP
#define TIMESERIESCOMPONENTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/HeterogeneousTimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesComponentAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Variant for the timeseries component attribute
        typedef boost::variant<
            HeterogeneousTimeseriesComponentAttribute,
            HomogeneousTimeseriesComponentAttribute
        > TimeseriesComponentType;

        //! Class for representing a timeseries component attribute
        class TimeseriesComponentAttribute {

            public:

                TimeseriesComponentType  timeseriesComponent;   /*!< The timeseries component */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeseriesComponentAttribute,
    (multiscale::verification::TimeseriesComponentType, timeseriesComponent)
)


#endif
