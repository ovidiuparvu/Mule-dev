#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <vector>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class ConstraintAttribute;
        class OrConstraintAttribute;
        class AndConstraintAttribute;
        class ImplicationConstraintAttribute;
        class EquivalenceConstraintAttribute;
        class PrimaryConstraintAttribute;


        //! Variant for a constraint attribute type
        typedef boost::variant<
            Nil,
            boost::recursive_wrapper<ConstraintAttribute>,
            boost::recursive_wrapper<OrConstraintAttribute>,
            boost::recursive_wrapper<AndConstraintAttribute>,
            boost::recursive_wrapper<ImplicationConstraintAttribute>,
            boost::recursive_wrapper<EquivalenceConstraintAttribute>,
            boost::recursive_wrapper<PrimaryConstraintAttribute>
        > ConstraintAttributeType;


        //! Class for representing a constraint attribute
        class ConstraintAttribute : public ConstraintEvaluator {

            public:

                ConstraintAttributeType                 firstConstraint;    /*!< The first constraint */
                std::vector<ConstraintAttributeType>    nextConstraints;    /*!< The next constraints */

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
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::vector<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
