#ifndef ORCONSTRAINTATTRIBUTE_HPP
#define ORCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"
#include "multiscale/verification/spatial-temporal/evaluation/OrEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "or" constraint attribute
		class OrConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType					firstConstraint;	/*!< The first constraint */
			std::list<ConstraintAttributeType>		nextConstraints;	/*!< The next constraints */

			//! Evaluate the constraint
			bool evaluate() const override {
				return evaluateNaryExpression(firstConstraint, nextConstraints, OrEvaluator());
			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::list<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
