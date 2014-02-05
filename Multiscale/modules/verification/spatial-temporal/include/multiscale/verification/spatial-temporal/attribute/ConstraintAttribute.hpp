#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

#include <list>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		// Forward declaration
		class ConstraintAttribute;
		class UnaryConstraintAttribute;
		class NotConstraintAttribute;


		//! Variant for a constraint attribute
		typedef boost::variant<
			Nil,
			boost::recursive_wrapper<ConstraintAttribute>,
			boost::recursive_wrapper<UnaryConstraintAttribute>
		> constraintAttribute_;

		//! Class for representing a constraint attribute
		class ConstraintAttribute {

			public:

				constraintAttribute_ 				firstConstraint;
				std::list<constraintAttribute_> 	nextConstraints;
		};


		//! Variant for a unary constraint attribute
		typedef boost::variant<
			NumericStateVariableAttribute,
			boost::recursive_wrapper<NotConstraintAttribute>
		> unaryConstraintAttribute_;

		//! Class for representing a "unary" constraint attribute
		class UnaryConstraintAttribute : public Attribute {

			public:

				unaryConstraintAttribute_ unaryConstraint;

				//! Evaluate the constraint
				bool evaluate() override {
					return true;
				}

		};


		//! Class for representing a "not" constraint attribute
		class NotConstraintAttribute {

			public:

				constraintAttribute_ constraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::constraintAttribute_, firstConstraint)
    (std::list<multiscale::verification::constraintAttribute_>, nextConstraints)
)

BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryConstraintAttribute,
    (multiscale::verification::unaryConstraintAttribute_, unaryConstraint)
)

BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotConstraintAttribute,
    (multiscale::verification::constraintAttribute_, constraint)
)

#endif
