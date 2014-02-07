#ifndef ANDCONSTRAINTATTRIBUTE_HPP
#define ANDCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"
#include "multiscale/verification/spatial-temporal/evaluation/AndEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "and" constraint attribute
		class AndConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType					firstConstraint;	/*!< The first constraint */
			std::list<ConstraintAttributeType>		nextConstraints;	/*!< The next constraints */

			//! Evaluate the constraint
			bool evaluate() const override {
				return evaluateNaryExpression(firstConstraint, nextConstraints, AndEvaluator());
			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::list<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
