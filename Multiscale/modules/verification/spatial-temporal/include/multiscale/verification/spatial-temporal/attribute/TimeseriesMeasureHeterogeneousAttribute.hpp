#ifndef TIMESERIESMEASUREHETEROGENEOUSATTRIBUTE_HPP
#define TIMESERIESMEASUREHETEROGENEOUSATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TimeseriesMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/HeterogeneousTimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a timeseries measure heterogeneous attribute
        class TimeseriesMeasureHeterogeneousAttribute {

            public:

                TimeseriesMeasureAttribute
                    timeseriesMeasure;                  /*!< The considered timeseries measure */
                HeterogeneousTimeseriesComponentAttribute
                    heterogeneousTimeseriesComponent;   /*!< The heterogeneous timeseries component */
                TemporalNumericCollectionAttribute
                    temporalNumericCollection;          /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeseriesMeasureHeterogeneousAttribute,
    (multiscale::verification::TimeseriesMeasureAttribute, timeseriesMeasure)
    (multiscale::verification::HeterogeneousTimeseriesComponentAttribute, heterogeneousTimeseriesComponent)
    (multiscale::verification::TemporalNumericCollectionAttribute, temporalNumericCollection)
)


#endif
