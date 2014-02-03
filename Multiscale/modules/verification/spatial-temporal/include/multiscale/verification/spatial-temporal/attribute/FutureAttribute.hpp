#ifndef FUTUREATTRIBUTE_HPP
#define FUTUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a Future attribute
		struct FutureAttribute {
			unsigned long			startTimepoint;
			unsigned long			endTimepoint;
			LogicPropertyAttribute 	logicalProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FutureAttribute,
    (unsigned long, startTimepoint)
	(unsigned long, endTimepoint)
	(LogicPropertyAttribute, logicalProperty)
)

#endif
