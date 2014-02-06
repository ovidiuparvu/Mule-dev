#ifndef UNARYCONSTRAINTATTRIBUTE_HPP
#define UNARYCONSTRAINTATTRIBUTE_HPP

//#include "multiscale/verification/spatial-temporal/attribute/NotConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		// Forward declarations
		class NotConstraintAttribute;


		//! Variant for a unary constraint attribute
		typedef boost::variant<
			NumericStateVariableAttribute,
			boost::recursive_wrapper<NotConstraintAttribute>
		> UnaryConstraintAttributeType;


		//! Class for representing a "unary" constraint attribute
		class UnaryConstraintAttribute : public Attribute {

			public:

				UnaryConstraintAttributeType unaryConstraint;		/*!< The unary constraint */

				//! Evaluate the constraint
				bool evaluate() override {
					return true;
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryConstraintAttribute,
    (multiscale::verification::UnaryConstraintAttributeType, unaryConstraint)
)

#endif
