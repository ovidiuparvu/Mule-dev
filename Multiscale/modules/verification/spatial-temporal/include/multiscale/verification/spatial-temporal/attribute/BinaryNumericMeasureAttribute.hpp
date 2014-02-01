#ifndef BINARYNUMERICMEASUREATTRIBUTE_HPP
#define BINARYNUMERICMEASUREATTRIBUTE_HPP

#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary numeric measure attribute
		struct BinaryNumericMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericMeasureAttribute,
    (string, name)
)

#endif
