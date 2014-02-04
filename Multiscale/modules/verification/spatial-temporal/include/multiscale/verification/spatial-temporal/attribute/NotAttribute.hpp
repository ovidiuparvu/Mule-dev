#ifndef NOTATTRIBUTE_HPP
#define NOTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

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
