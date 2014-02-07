#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a constraint attribute
		class ConstraintAttribute : public Attribute {

			public:

				UnaryConstraintAttributeType 	firstConstraint;		/*!< The first constraint */
				ConstraintAttributeType			nextConstraints;		/*!< The next constraints */

				//! Evaluate the constraint
				bool evaluate(bool truthValue) const override {
					bool firstEvaluationResult = evaluateUnaryExpression(firstConstraint);

					return evaluateNaryNextExpressions(firstEvaluationResult, nextConstraints);
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (multiscale::verification::ConstraintAttributeType, nextConstraints)
)

#endif
