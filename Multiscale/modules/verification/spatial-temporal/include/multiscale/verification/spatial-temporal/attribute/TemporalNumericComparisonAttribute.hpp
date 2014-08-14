#ifndef TEMPORALNUMERICCOMPARISONATTRIBUTE_HPP
#define TEMPORALNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a temporal numeric comparison attribute
        class TemporalNumericComparisonAttribute {

            public:

                TemporalNumericMeasureType
                    lhsTemporalNumericMeasure;  /*!< The temporal numeric measure preceding the comparator */
                ComparatorAttribute
                    comparator;                 /*!< The comparator */
                TemporalNumericMeasureType
                    rhsTemporalNumericMeasure;  /*!< The temporal numeric measure succeeding the comparator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericComparisonAttribute,
    (multiscale::verification::TemporalNumericMeasureType, lhsTemporalNumericMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::TemporalNumericMeasureType, rhsTemporalNumericMeasure)
)


#endif
