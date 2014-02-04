#ifndef STATEVARIABLEATTRIBUTE_HPP
#define STATEVARIABLEATTRIBUTE_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Structure for representing a state variable attribute
		struct StateVariableAttribute {
			std::string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::StateVariableAttribute,
    (std::string, name)
)

#endif
