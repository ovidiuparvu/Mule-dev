#ifndef ANDATTRIBUTE_HPP
#define ANDATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing an and attribute
		struct AndAttribute {
			LogicPropertyAttribute lhsLogicalProperty;
			LogicPropertyAttribute rhsLogicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndAttribute,
    (LogicPropertyAttribute, lhsLogicalProperty)
    (LogicPropertyAttribute, rhsLogicalProperty)
)

#endif
