#ifndef UNARYCONSTRAINTATTRIBUTE_HPP
#define UNARYCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FilterNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "unary" constraint attribute
        class UnaryConstraintAttribute {

            public:

                SpatialMeasureAttribute             spatialMeasure;         /*!< The spatial measure */
                ComparatorAttribute                 comparator;             /*!< The comparator */
                FilterNumericMeasureAttributeType   filterNumericMeasure;   /*!< The filter numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryConstraintAttribute,
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::FilterNumericMeasureAttributeType, filterNumericMeasure)
)

#endif
