#ifndef IMPLICATIONCONSTRAINTATTRIBUTE_HPP
#define IMPLICATIONCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"
#include "multiscale/verification/spatial-temporal/evaluation/ImplicationEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "implication" constraint attribute
		class ImplicationConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType					firstConstraint;	/*!< The first constraint */
			std::list<ConstraintAttributeType>		nextConstraints;	/*!< The next constraints */

			//! Evaluate the constraint
			bool evaluate() const override {
				return evaluateNaryExpression(firstConstraint, nextConstraints, ImplicationEvaluator());
			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ImplicationConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::list<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
