#ifndef NOTCONSTRAINTATTRIBUTE_HPP
#define NOTCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a "not" constraint attribute
		struct NotConstraintAttribute {
			ConstraintAttribute constraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotConstraintAttribute,
    (multiscale::verification::ConstraintAttribute, constraint)
)

#endif
