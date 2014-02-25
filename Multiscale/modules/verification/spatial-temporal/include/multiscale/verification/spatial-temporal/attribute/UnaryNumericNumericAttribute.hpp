#ifndef UNARYNUMERICNUMERICATTRIBUTE_HPP
#define UNARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary numeric numeric measure attribute
        class UnaryNumericNumericAttribute : public NumericEvaluator {

            public:

                UnaryNumericMeasureAttribute    unaryNumericMeasure;    /*!< The unary numeric measure */
                NumericMeasureAttributeType     numericMeasure;         /*!< The considered numeric measure */

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
    multiscale::verification::UnaryNumericNumericAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
