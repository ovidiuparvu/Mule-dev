#ifndef ORCONSTRAINTATTRIBUTE_HPP
#define ORCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

using namespace multiscale::verification;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


namespace multiscale {

	namespace verification {

		//! Structure for representing an "or" constraint attribute
		struct OrConstraintAttribute {
			ConstraintAttribute	lhsConstraint;
			ConstraintAttribute rhsConstraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrConstraintAttribute,
    (multiscale::verification::ConstraintAttribute, lhsConstraint)
    (multiscale::verification::ConstraintAttribute, rhsConstraint)
)

#endif
