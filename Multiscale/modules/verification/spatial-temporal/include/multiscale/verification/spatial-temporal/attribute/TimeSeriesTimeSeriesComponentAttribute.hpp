#ifndef TIMESERIESTIMESERIESCOMPONENTATTRIBUTE_HPP
#define TIMESERIESTIMESERIESCOMPONENTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <multiscale/verification/spatial-temporal/attribute/TimeSeriesComponentAttribute.hpp>
#include <multiscale/verification/spatial-temporal/attribute/TimeSeriesMeasureAttribute.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a time series time series component attribute
        class TimeSeriesTimeSeriesComponentAttribute {

            public:

                TimeSeriesMeasureAttribute
                    timeSeriesMeasure;                  /*!< The time series measure */
                TimeSeriesComponentAttribute
                    timeSeriesComponent;                /*!< The time series component */
                TemporalNumericMeasureCollectionAttribute
                    temporalNumericMeasureCollection;   /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeSeriesTimeSeriesComponentAttribute,
    (multiscale::verification::TimeSeriesMeasureAttribute, timeSeriesMeasure)
    (multiscale::verification::TimeSeriesComponentAttribute, timeSeriesComponent)
    (multiscale::verification::TemporalNumericMeasureCollectionAttribute, temporalNumericMeasureCollection)
)


#endif
