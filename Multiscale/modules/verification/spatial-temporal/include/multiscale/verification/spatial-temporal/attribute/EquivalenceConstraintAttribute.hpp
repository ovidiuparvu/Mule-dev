#ifndef EQUIVALENCECONSTRAINTATTRIBUTE_HPP
#define EQUIVALENCECONSTRAINTATTRIBUTE_HPP

//#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
//#include "multiscale/verification/spatial-temporal/evaluation/EquivalenceEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "equivalence" constraint attribute
		class EquivalenceConstraintAttribute {
//		class EquivalenceConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType constraint; /*!< The constraint */

			//! Evaluate the constraint
//			bool evaluate() const override {
//				return evaluateNaryExpression(firstConstraint, nextConstraints, EquivalenceEvaluator());
//			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::EquivalenceConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
