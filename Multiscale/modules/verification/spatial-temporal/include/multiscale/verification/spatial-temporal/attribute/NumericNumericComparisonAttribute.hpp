#ifndef NUMERICNUMERICCOMPARISONATTRIBUTE_HPP
#define NUMERICNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a numeric numeric comparison attribute
        class NumericNumericComparisonAttribute {
//        class NumericNumericComparisonAttribute : public LogicPropertyEvaluator {

            public:

                NumericStateVariableAttribute   numericStateVariable;   /*!< The numeric state variable preceding the comparator */
                ComparatorAttribute             comparator;             /*!< The comparator */
                NumericMeasureAttributeType     numericMeasure;         /*!< The numeric measure following the comparator */

            public:

                //! Evaluate the truth value of the logic property considering the given spatial temporal trace
                /*!
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
//                bool evaluate(const SpatialTemporalTrace &trace,
//                              const LogicPropertyAttributeType &lhsLogicProperty) const override {
//                    return true;
//                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericNumericComparisonAttribute,
    (multiscale::verification::NumericStateVariableAttribute, numericStateVariable)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
