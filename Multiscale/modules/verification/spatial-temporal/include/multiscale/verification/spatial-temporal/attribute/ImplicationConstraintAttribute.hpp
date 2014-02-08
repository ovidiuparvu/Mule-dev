#ifndef IMPLICATIONCONSTRAINTATTRIBUTE_HPP
#define IMPLICATIONCONSTRAINTATTRIBUTE_HPP

//#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
//#include "multiscale/verification/spatial-temporal/evaluation/ImplicationEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing an "implication" constraint attribute
		class ImplicationConstraintAttribute {
//		class ImplicationConstraintAttribute : public Attribute {

		public:

            ConstraintAttributeType constraint; /*!< The constraint */

			//! Evaluate the constraint
//			bool evaluate() const override {
//				return evaluateNaryExpression(firstConstraint, nextConstraints, ImplicationEvaluator());
//			}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ImplicationConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
