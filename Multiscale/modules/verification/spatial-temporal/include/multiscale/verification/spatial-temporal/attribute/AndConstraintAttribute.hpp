#ifndef ANDCONSTRAINTATTRIBUTE_HPP
#define ANDCONSTRAINTATTRIBUTE_HPP

//#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
//#include "multiscale/verification/spatial-temporal/evaluation/AndEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "and" constraint attribute
		class AndConstraintAttribute {
//		class AndConstraintAttribute : public Attribute {

		public:

            ConstraintAttributeType constraint;	/*!< The constraint following the "and" operator */

			//! Evaluate the constraint
//			bool evaluate() const override {
//				return evaluateNaryExpression(firstConstraint, nextConstraints, AndEvaluator());
//			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
