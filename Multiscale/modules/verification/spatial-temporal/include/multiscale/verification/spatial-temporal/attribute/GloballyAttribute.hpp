#ifndef GLOBALLYATTRIBUTE_HPP
#define GLOBALLYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a Globally attribute
		struct GloballyAttribute {
			unsigned long			startTimepoint;
			unsigned long			endTimepoint;
			LogicPropertyAttribute 	logicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::GloballyAttribute,
    (unsigned long, startTimepoint)
	(unsigned long, endTimepoint)
	(LogicPropertyAttribute, logicalProperty)
)

#endif
