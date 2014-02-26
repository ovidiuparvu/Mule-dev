#ifndef NUMERICNUMERICCOMPARISONATTRIBUTE_HPP
#define NUMERICNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a numeric numeric comparison attribute
        class NumericNumericComparisonAttribute {

            public:

                NumericStateVariableAttribute   numericStateVariable;   /*!< The numeric state variable preceding the comparator */
                ComparatorAttribute             comparator;             /*!< The comparator */
                NumericMeasureAttributeType     numericMeasure;         /*!< The numeric measure following the comparator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericNumericComparisonAttribute,
    (multiscale::verification::NumericStateVariableAttribute, numericStateVariable)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
