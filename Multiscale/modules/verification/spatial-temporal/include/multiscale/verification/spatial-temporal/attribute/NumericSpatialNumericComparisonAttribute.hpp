#ifndef NUMERICSPATIALNUMERICCOMPARISONATTRIBUTE_HPP
#define NUMERICSPATIALNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a numeric spatial numeric comparison attribute
        class NumericSpatialNumericComparisonAttribute {

            public:

                NumericSpatialAttributeType    numericSpatialMeasure;   /*!< The numeric spatial measure preceding the comparator */
                ComparatorAttribute            comparator;              /*!< The comparator */
                NumericMeasureAttributeType    numericMeasure;          /*!< The numeric measure following the comparator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialNumericComparisonAttribute,
    (multiscale::verification::NumericSpatialAttributeType, numericSpatialMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
