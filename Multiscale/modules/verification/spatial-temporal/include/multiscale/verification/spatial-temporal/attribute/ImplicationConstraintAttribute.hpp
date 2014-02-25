#ifndef IMPLICATIONCONSTRAINTATTRIBUTE_HPP
#define IMPLICATIONCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "implication" constraint attribute
        class ImplicationConstraintAttribute : public ConstraintEvaluator {

            public:

                ConstraintAttributeType constraint; /*!< The constraint following the "implication" operator */

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
    multiscale::verification::ImplicationConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
