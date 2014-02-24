#ifndef NUMERICSPATIALATTRIBUTE_HPP
#define NUMERICSPATIALATTRIBUTE_HPP


#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a numeric spatial attribute
        class NumericSpatialAttribute : public NumericEvaluator {

            public:

                NumericSpatialAttributeType numericSpatialMeasure;  /*!< The numeric spatial measure */

            public:

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
                double evaluate(const TimePoint &timePoint) const override {
                    return 0.0;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialAttribute,
    (multiscale::verification::NumericSpatialAttributeType, numericSpatialMeasure)
)

#endif
