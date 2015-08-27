#ifndef TEMPORALNUMERICMEASURECOLLECTIONATTRIBUTE_HPP
#define TEMPORALNUMERICMEASURECOLLECTIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing temporal numeric measure collection attributes
        class TemporalNumericMeasureCollectionAttribute {

            public:

                double              startTimePoint; /*!< The considered start time point */
                double              endTimePoint;   /*!< The considered end time point */

                NumericMeasureType  numericMeasure; /*!< The numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericMeasureCollectionAttribute,
    (double, startTimePoint)
    (double, endTimePoint)
    (multiscale::verification::NumericMeasureType, numericMeasure)
)


#endif
