#ifndef BINARYNUMERICNUMERICATTRIBUTE_HPP
#define BINARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary numeric numeric measure attribute
        class BinaryNumericNumericAttribute : public NumericEvaluator {

            public:

                BinaryNumericMeasureAttribute   binaryNumericMeasure;   /*!< The binary numeric measure */
                NumericMeasureAttributeType     firstNumericMeasure;    /*!< The first numeric measure */
                NumericMeasureAttributeType     secondNumericMeasure;   /*!< The second numeric measure */

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
    multiscale::verification::BinaryNumericNumericAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericMeasureAttributeType, firstNumericMeasure)
    (multiscale::verification::NumericMeasureAttributeType, secondNumericMeasure)
)

#endif
