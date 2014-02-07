#ifndef NOTCONSTRAINTATTRIBUTE_HPP
#define NOTCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a "not" constraint attribute
		class NotConstraintAttribute : public Attribute {

			public:

				ConstraintAttributeType constraint;	/*!< The constraint which will be negated */

				//! Evaluate the constraint
				bool evaluate() const override {
					return !(evaluateUnaryExpression(constraint));
				}
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
