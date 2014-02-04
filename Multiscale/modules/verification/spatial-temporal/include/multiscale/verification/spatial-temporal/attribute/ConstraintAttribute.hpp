#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NotConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/OrConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialNumericComparisonAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Variant for a constraint attribute
		typedef boost::variant<
			multiscale::verification::NotConstraintAttribute,
			multiscale::verification::OrConstraintAttribute,
			multiscale::verification::SpatialNumericComparisonAttribute
		> constraintAttribute_;

		//! Structure for representing a constraint attribute
		struct ConstraintAttribute {
			constraintAttribute_ constraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::constraintAttribute_, constraint)
)

#endif
