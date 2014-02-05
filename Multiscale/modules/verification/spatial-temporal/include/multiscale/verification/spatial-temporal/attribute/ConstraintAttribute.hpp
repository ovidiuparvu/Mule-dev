#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
//#include "multiscale/verification/spatial-temporal/attribute/SpatialNumericComparisonAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		// Forward declaration
		struct ConstraintAttribute;
		struct NotConstraintAttribute;
		struct OrConstraintAttribute;

		//! Variant for a constraint attribute
		typedef boost::variant<
			NumericStateVariableAttribute,
			boost::recursive_wrapper<ConstraintAttribute>,
			boost::recursive_wrapper<NotConstraintAttribute>,
			boost::recursive_wrapper<multiscale::verification::OrConstraintAttribute>
			//multiscale::verification::SpatialNumericComparisonAttribute
		> constraintAttribute_;

		//! Structure for representing a constraint attribute
		struct ConstraintAttribute {
			constraintAttribute_ constraint;
		};

		//! Structure for representing a "not" constraint attribute
		struct NotConstraintAttribute {
			constraintAttribute_ constraint;
		};

		//! Structure for representing an "or" constraint attribute
		struct OrConstraintAttribute {
			constraintAttribute_	lhsConstraint;
			constraintAttribute_	rhsConstraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::constraintAttribute_, constraint)
)

BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotConstraintAttribute,
    (multiscale::verification::constraintAttribute_, constraint)
)

BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrConstraintAttribute,
    (multiscale::verification::constraintAttribute_, lhsConstraint)
    (multiscale::verification::constraintAttribute_, rhsConstraint)
)

#endif
