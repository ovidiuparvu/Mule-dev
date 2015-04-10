#ifndef UNARYSCALEANDSUBSYSTEMCONSTRAINTATTRIBUTE_HPP
#define UNARYSCALEANDSUBSYSTEMCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ScaleAndSubsystemAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "unary" scale and subsystem constraint attribute
        class UnaryScaleAndSubsystemConstraintAttribute {

            public:

                ComparatorAttribute         comparator;           /*!< The comparator */
                ScaleAndSubsystemAttribute  scaleAndSubsystem;    /*!< The considered scale and subsystem */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryScaleAndSubsystemConstraintAttribute,
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::ScaleAndSubsystemAttribute, scaleAndSubsystem)
)


#endif
