#ifndef PRIMARYCONSTRAINTATTRIBUTE_HPP
#define PRIMARYCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declarations
        class ConstraintAttribute;
        class NotConstraintAttribute;
        class UnarySpatialConstraintAttribute;
        class UnaryTypeConstraintAttribute;


        //! Variant for a primary constraint attribute
        typedef boost::variant<
            Nil,
            boost::recursive_wrapper<ConstraintAttribute>,
            boost::recursive_wrapper<NotConstraintAttribute>,
            boost::recursive_wrapper<UnarySpatialConstraintAttribute>,
            boost::recursive_wrapper<UnaryTypeConstraintAttribute>
        > PrimaryConstraintAttributeType;


        //! Class for representing a primary constraint attribute
        class PrimaryConstraintAttribute {

            public:

                PrimaryConstraintAttributeType primaryConstraint;   /*!< The primary constraint */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::PrimaryConstraintAttribute,
    (multiscale::verification::PrimaryConstraintAttributeType, primaryConstraint)
)


#endif
