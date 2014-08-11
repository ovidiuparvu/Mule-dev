#ifndef UNARYTYPECONSTRAINTATTRIBUTE_HPP
#define UNARYTYPECONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FilterNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "unary" type constraint attribute
        class UnaryTypeConstraintAttribute {

            public:

                ComparatorAttribute                 comparator;             /*!< The comparator */
                FilterNumericMeasureAttributeType   filterNumericMeasure;   /*!< The filter numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryTypeConstraintAttribute,
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::FilterNumericMeasureAttributeType, filterNumericMeasure)
)


#endif
