#ifndef DIFFERENCEATTRIBUTE_HPP
#define DIFFERENCEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a difference attribute
        class DifferenceAttribute {
//        class DifferenceAttribute : public LogicPropertyEvaluator {

            public:

                NumericMeasureAttributeType    lhsNumericMeasure;    /*!< The left hand side numeric measure */
                ComparatorAttribute            comparator;           /*!< The comparator */
                NumericMeasureAttributeType    rhsNumericMeasure;    /*!< The right hand side numeric measure */

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
    multiscale::verification::DifferenceAttribute,
    (multiscale::verification::NumericMeasureAttributeType, lhsNumericMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, rhsNumericMeasure)
)

#endif
