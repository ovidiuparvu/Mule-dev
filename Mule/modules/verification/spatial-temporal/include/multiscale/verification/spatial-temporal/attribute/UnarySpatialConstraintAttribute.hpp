#ifndef UNARYSPATIALCONSTRAINTATTRIBUTE_HPP
#define UNARYSPATIALCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FilterNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "unary" spatial constraint attribute
        class UnarySpatialConstraintAttribute {

            public:

                SpatialMeasureAttribute             spatialMeasure;         /*!< The spatial measure */
                ComparatorAttribute                 comparator;             /*!< The comparator */
                FilterNumericMeasureAttributeType   filterNumericMeasure;   /*!< The filter numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySpatialConstraintAttribute,
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::FilterNumericMeasureAttributeType, filterNumericMeasure)
)


#endif
