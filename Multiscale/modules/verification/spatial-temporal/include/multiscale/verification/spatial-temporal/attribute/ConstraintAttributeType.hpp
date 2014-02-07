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
		class OrConstraintAttribute;
		class AndConstraintAttribute;
		class ImplicationConstraintAttribute;
		class EquivalenceConstraintAttribute;
		class UnaryConstraintAttribute;


		//! Variant for a constraint attribute type
		typedef boost::variant<
			Nil,
			boost::recursive_wrapper<ConstraintAttribute>,
			boost::recursive_wrapper<OrConstraintAttribute>,
			boost::recursive_wrapper<AndConstraintAttribute>,
			boost::recursive_wrapper<ImplicationConstraintAttribute>,
			boost::recursive_wrapper<EquivalenceConstraintAttribute>,
			boost::recursive_wrapper<UnaryConstraintAttribute>
		> ConstraintAttributeType;

	};

};

#endif
