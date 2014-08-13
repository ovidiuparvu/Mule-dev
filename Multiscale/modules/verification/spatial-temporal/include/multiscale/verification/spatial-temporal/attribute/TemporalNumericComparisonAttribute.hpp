#ifndef TEMPORALNUMERICCOMPARISONATTRIBUTE_HPP
#define TEMPORALNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a temporal numeric comparison attribute
        class TemporalNumericComparisonAttribute {

            public:

                NumericMeasureAttributeType lhsNumericMeasure;  /*!< The numeric measure preceding the comparator */
                ComparatorAttribute         comparator;         /*!< The comparator */
                NumericMeasureAttributeType rhsNumericMeasure;  /*!< The numeric measure succeeding the comparator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericComparisonAttribute,
    (multiscale::verification::NumericMeasureAttributeType, lhsNumericMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, rhsNumericMeasure)
)


#endif
