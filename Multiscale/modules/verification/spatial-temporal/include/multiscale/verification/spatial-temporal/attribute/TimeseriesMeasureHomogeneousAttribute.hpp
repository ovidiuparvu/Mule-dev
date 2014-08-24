#ifndef TIMESERIESMEASUREHOMOGENEOUSATTRIBUTE_HPP
#define TIMESERIESMEASUREHOMOGENEOUSATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TimeseriesMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a timeseries measure homogeneous attribute
        class TimeseriesMeasureHomogeneousAttribute {

            public:

                TimeseriesMeasureAttribute
                    timeseriesMeasure;              /*!< The considered timeseries measure */
                HomogeneousTimeseriesComponentAttribute
                    homogeneousTimeseriesComponent; /*!< The homogeneous timeseries component */
                TemporalNumericCollectionAttribute
                    temporalNumericCollection;      /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeseriesMeasureHomogeneousAttribute,
    (multiscale::verification::TimeseriesMeasureAttribute, timeseriesMeasure)
    (multiscale::verification::HomogeneousTimeseriesComponentAttribute, homogeneousTimeseriesComponent)
    (multiscale::verification::TemporalNumericCollectionAttribute, temporalNumericCollection)
)


#endif
