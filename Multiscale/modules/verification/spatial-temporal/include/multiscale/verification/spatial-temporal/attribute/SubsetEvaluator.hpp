#ifndef SUBSETEVALUATOR_HPP
#define SUBSETEVALUATOR_HPP

# include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"


namespace multiscale {

    namespace verification {

        //! Abstract class used for evaluating subsets
        class SubsetEvaluator {

            public:

                virtual ~SubsetEvaluator() {};

                //! Compute a subset of spatial entities for the given timepoint
                /*!
                 * \param timePoint The given timepoint
                 */
                virtual TimePoint evaluate(const TimePoint timePoint) const = 0;

        };

    };

};



#endif
