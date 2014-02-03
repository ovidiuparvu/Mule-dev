#ifndef NOTATTRIBUTE_HPP
#define NOTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a not attribute
		struct NotAttribute {
			LogicPropertyAttribute logicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotAttribute,
    (LogicPropertyAttribute, logicalProperty)
)

#endif
