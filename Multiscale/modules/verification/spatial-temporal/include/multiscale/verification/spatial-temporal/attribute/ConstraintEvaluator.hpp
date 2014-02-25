#ifndef CONSTRAINTEVALUATOR_HPP
#define CONSTRAINTEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"


namespace multiscale {

    namespace verification {

        //! Abstract class used for evaluating constraints
        class ConstraintEvaluator {

            public:

                virtual ~ConstraintEvaluator() {};

                //! Filter the set of spatial entities for a timepoint considering the given constraint(s)
                /*!
                 * \param initialTimePoint      The initial timepoint
                 * \param constraintTimePoint   The result of applying constraints to the initial timepoint
                 */
                virtual TimePoint evaluate(const TimePoint &initialTimePoint,
                                           const TimePoint &constraintTimePoint) const = 0;
        };

    };

};

#endif
