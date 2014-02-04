#ifndef NEXTNATTRIBUTE_HPP
#define NEXTNATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a neXt "N" attribute
		struct NextNAttribute {
			LogicPropertyAttribute logicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NextNAttribute,
    (LogicPropertyAttribute, logicalProperty)
)

#endif