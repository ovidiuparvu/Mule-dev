#ifndef NUMERICEVALUATOR_HPP
#define NUMERICEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Abstract class used for evaluation numeric measures
        class NumericEvaluator {

            public:

                virtual ~NumericEvaluator() {};

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
                virtual double evaluate(const TimePoint &timePoint) const = 0;

        };
    };

};

#endif
