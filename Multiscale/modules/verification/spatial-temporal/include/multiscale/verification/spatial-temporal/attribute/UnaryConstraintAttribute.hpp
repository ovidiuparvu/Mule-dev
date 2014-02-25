#ifndef UNARYCONSTRAINTATTRIBUTE_HPP
#define UNARYCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "unary" constraint attribute
        class UnaryConstraintAttribute : public ConstraintEvaluator {

            public:

                SpatialMeasureAttribute     spatialMeasure;    /*!< The spatial measure */
                ComparatorAttribute         comparator;        /*!< The comparator */
                NumericMeasureAttributeType numericMeasure;    /*!< The numeric measure */

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
    multiscale::verification::UnaryConstraintAttribute,
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
