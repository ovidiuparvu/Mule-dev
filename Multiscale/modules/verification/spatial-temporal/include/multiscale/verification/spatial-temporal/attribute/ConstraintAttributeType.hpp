#ifndef CONSTRAINTATTRIBUTETYPE_HPP
#define CONSTRAINTATTRIBUTETYPE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryConstraintAttribute.hpp"

#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		// Forward declaration of classes
		class ConstraintAttribute;
		class UnaryConstraintAttribute;


		//! Variant for a constraint attribute type
		typedef boost::variant<
			Nil,
			boost::recursive_wrapper<ConstraintAttribute>,
			boost::recursive_wrapper<UnaryConstraintAttribute>
		> ConstraintAttributeType;

	};

};

#endif
