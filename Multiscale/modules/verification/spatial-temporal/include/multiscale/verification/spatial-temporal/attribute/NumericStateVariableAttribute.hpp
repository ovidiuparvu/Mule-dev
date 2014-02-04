#ifndef NUMERICSTATEVARIABLEATTRIBUTE_HPP
#define NUMERICSTATEVARIABLEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/StateVariableAttribute.hpp"

using namespace multiscale::verification;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


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
