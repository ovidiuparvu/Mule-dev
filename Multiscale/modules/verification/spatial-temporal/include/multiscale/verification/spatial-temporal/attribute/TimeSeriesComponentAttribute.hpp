#ifndef TIMESERIESCOMPONENTATTRIBUTE_HPP
#define TIMESERIESCOMPONENTATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <multiscale/verification/spatial-temporal/attribute/HeterogeneousTimeSeriesComponentAttribute.hpp>
#include <multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesComponentAttribute.hpp>


namespace multiscale {

    namespace verification {

        //! Variant for the time series component attribute
        typedef boost::variant<
            HeterogeneousTimeSeriesComponentAttribute,
            HomogeneousTimeSeriesComponentAttribute
        > TimeSeriesComponentType;

        //! Class for representing a time series component attribute
        class TimeSeriesComponentAttribute {

            public:

                TimeSeriesComponentType  timeSeriesComponent;   /*!< The time series component */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeSeriesComponentAttribute,
    (multiscale::verification::TimeSeriesComponentType, timeSeriesComponent)
)


#endif
