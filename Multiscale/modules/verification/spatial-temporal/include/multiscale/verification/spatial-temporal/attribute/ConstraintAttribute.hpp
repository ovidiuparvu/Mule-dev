#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a constraint attribute
		class ConstraintAttribute : public Attribute {

			public:

				ConstraintAttributeType	constraint;		/*!< The constraint */

				//! Evaluate the constraint
				bool evaluate() const override {
					return evaluateUnaryExpression(constraint);
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
