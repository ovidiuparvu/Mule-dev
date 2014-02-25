#ifndef PRIMARYCONSTRAINTATTRIBUTE_HPP
#define PRIMARYCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declarations
        class ConstraintAttribute;
        class NotConstraintAttribute;
        class UnaryConstraintAttribute;


        //! Variant for a unary constraint attribute
        typedef boost::variant<
            boost::recursive_wrapper<ConstraintAttribute>,
            boost::recursive_wrapper<NotConstraintAttribute>,
            boost::recursive_wrapper<UnaryConstraintAttribute>
        > PrimaryConstraintAttributeType;


        //! Class for representing a primary constraint attribute
        class PrimaryConstraintAttribute : public ConstraintEvaluator {

            public:

                PrimaryConstraintAttributeType primaryConstraint;   /*!< The primary constraint */

            public:

                //! Filter the set of spatial entities for a timepoint considering the given constraint(s)
                /*!
                 * \param initialTimePoint      The initial timepoint
                 * \param constraintTimePoint   The result of applying constraints to the initial timepoint
                 */
                TimePoint evaluate(const TimePoint &initialTimePoint,
                                   const TimePoint &constraintTimePoint) const override {
                    return constraintTimePoint;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::PrimaryConstraintAttribute,
    (multiscale::verification::PrimaryConstraintAttributeType, primaryConstraint)
)

#endif
