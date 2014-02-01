#ifndef NUMERICSTATEVARIABLEATTRIBUTE_HPP
#define NUMERICSTATEVARIABLEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/StateVariableAttribute.hpp"

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a numeric state variable attribute
		struct NumericStateVariableAttribute {
			StateVariableAttribute name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericStateVariableAttribute,
    (StateVariableAttribute, name)
)

#endif
