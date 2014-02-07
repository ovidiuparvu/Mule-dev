#ifndef UNARYCONSTRAINTATTRIBUTE_HPP
#define UNARYCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		// Forward declarations
		class NotConstraintAttribute;
		class ConstraintAttribute;

		//! Variant for a unary constraint attribute
		typedef boost::variant<
			NumericStateVariableAttribute,
			boost::recursive_wrapper<NotConstraintAttribute>,
			boost::recursive_wrapper<ConstraintAttribute>
		> UnaryConstraintAttributeType;


		//! Class for representing a "unary" constraint attribute
		class UnaryConstraintAttribute : public Attribute {

			public:

				UnaryConstraintAttributeType unaryConstraint;		/*!< The unary constraint */

				//! Evaluate the constraint
				bool evaluate() const override {
					return evaluateUnaryExpression(unaryConstraint);
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryConstraintAttribute,
    (multiscale::verification::UnaryConstraintAttributeType, unaryConstraint)
)

#endif
