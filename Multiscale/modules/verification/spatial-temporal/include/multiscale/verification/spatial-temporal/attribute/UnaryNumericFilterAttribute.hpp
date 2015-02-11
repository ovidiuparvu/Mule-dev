#ifndef UNARYNUMERICFILTERATTRIBUTE_HPP
#define UNARYNUMERICFILTERATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/FilterNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary numeric filter attribute
        class UnaryNumericFilterAttribute {

            public:

                UnaryNumericMeasureAttribute        unaryNumericMeasure;    /*!< The unary numeric measure */
                FilterNumericMeasureAttributeType   filterNumericMeasure;   /*!< The considered filter numeric
                                                                                 measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericFilterAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::FilterNumericMeasureAttributeType, filterNumericMeasure)
)


#endif
