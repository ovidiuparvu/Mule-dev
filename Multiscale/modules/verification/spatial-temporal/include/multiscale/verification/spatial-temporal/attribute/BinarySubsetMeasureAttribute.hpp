#ifndef BINARYSUBSETMEASUREATTRIBUTE_HPP
#define BINARYSUBSETMEASUREATTRIBUTE_HPP

#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary subset measure attribute
		struct BinarySubsetMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinarySubsetMeasureAttribute,
    (string, name)
)

#endif
