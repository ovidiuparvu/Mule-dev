#ifndef ORATTRIBUTE_HPP
#define ORATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

using namespace multiscale::verification;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


namespace multiscale {

	namespace verification {

		//! Structure for representing an or attribute
		struct OrAttribute {
			LogicPropertyAttribute lhsLogicalProperty;
			LogicPropertyAttribute rhsLogicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrAttribute,
    (LogicPropertyAttribute, lhsLogicalProperty)
    (LogicPropertyAttribute, rhsLogicalProperty)
)

#endif
