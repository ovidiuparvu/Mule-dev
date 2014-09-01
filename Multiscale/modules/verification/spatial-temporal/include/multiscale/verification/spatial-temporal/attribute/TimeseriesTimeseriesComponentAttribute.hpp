#ifndef TIMESERIESTIMESERIESCOMPONENTATTRIBUTE_HPP
#define TIMESERIESTIMESERIESCOMPONENTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TimeseriesMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a timeseries timeseries component attribute
        class TimeseriesTimeseriesComponentAttribute {

            public:

                TimeseriesMeasureAttribute
                    timeseriesMeasure;                  /*!< The timeseries measure */
                TimeseriesComponentAttribute
                    timeseriesComponent;                /*!< The timeseries component */
                TemporalNumericMeasureCollectionAttribute
                    temporalNumericMeasureCollection;   /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeseriesTimeseriesComponentAttribute,
    (multiscale::verification::TimeseriesMeasureAttribute, timeseriesMeasure)
    (multiscale::verification::TimeseriesComponentAttribute, timeseriesComponent)
    (multiscale::verification::TemporalNumericMeasureCollectionAttribute, temporalNumericMeasureCollection)
)


#endif
