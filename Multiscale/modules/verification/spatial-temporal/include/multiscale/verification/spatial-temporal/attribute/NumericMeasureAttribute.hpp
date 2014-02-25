#ifndef NUMERICMEASUREATTRIBUTE_HPP
#define NUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class BinaryNumericNumericAttribute;
        class NumericMeasureAttribute;
        class NumericSpatialAttribute;
        class UnaryNumericNumericAttribute;


        //! Variant for the numeric measure attribute
        typedef boost::variant<
            double,
            multiscale::verification::NumericStateVariableAttribute,
            boost::recursive_wrapper<multiscale::verification::NumericSpatialAttribute>,
            boost::recursive_wrapper<multiscale::verification::UnaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::BinaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::NumericMeasureAttribute>
        > NumericMeasureAttributeType;


        //! Variant for a numeric spatial attribute
        typedef boost::variant<
            UnarySubsetAttribute,
            BinarySubsetAttribute,
            TernarySubsetAttribute,
            QuaternarySubsetAttribute,
            boost::recursive_wrapper<NumericSpatialAttribute>
        > NumericSpatialAttributeType;


        //! Class for representing a numeric measure attribute
        class NumericMeasureAttribute : public NumericEvaluator {

            public:

                NumericMeasureAttributeType numericMeasure; /*!< The numeric measure */

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
    multiscale::verification::NumericMeasureAttribute,
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
