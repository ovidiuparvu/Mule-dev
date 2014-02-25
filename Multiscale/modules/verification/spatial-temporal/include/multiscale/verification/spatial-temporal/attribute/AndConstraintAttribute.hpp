#ifndef ANDCONSTRAINTATTRIBUTE_HPP
#define ANDCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "and" constraint attribute
        class AndConstraintAttribute : public ConstraintEvaluator {

        public:

            ConstraintAttributeType constraint; /*!< The constraint following the "and" operator */

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
    multiscale::verification::AndConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
