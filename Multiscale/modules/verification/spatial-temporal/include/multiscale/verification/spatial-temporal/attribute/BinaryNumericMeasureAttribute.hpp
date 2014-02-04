#ifndef BINARYNUMERICMEASUREATTRIBUTE_HPP
#define BINARYNUMERICMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
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
