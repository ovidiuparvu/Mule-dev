#ifndef SUBSETSPECIFICATTRIBUTE_HPP
#define SUBSETSPECIFICATTRIBUTE_HPP

#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a subset specific attribute
		struct SubsetSpecificAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSpecificAttribute,
    (string, name)
)

#endif
