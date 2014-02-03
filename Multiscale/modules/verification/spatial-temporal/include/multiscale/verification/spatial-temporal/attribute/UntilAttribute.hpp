#ifndef UNTILATTRIBUTE_HPP
#define UNTILATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing an Until attribute
		struct UntilAttribute {
			LogicPropertyAttribute 	lhsLogicalProperty;
			unsigned long			startTimepoint;
			unsigned long			endTimepoint;
			LogicPropertyAttribute 	rhsLogicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UntilAttribute,
    (LogicPropertyAttribute, lhsLogicalProperty)
	(unsigned long, startTimepoint)
	(unsigned long, endTimepoint)
	(LogicPropertyAttribute, rhsLogicalProperty)
)

#endif
