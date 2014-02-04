#ifndef STATEVARIABLEATTRIBUTE_HPP
#define STATEVARIABLEATTRIBUTE_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a state variable attribute
		struct StateVariableAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::StateVariableAttribute,
    (string, name)
)

#endif
