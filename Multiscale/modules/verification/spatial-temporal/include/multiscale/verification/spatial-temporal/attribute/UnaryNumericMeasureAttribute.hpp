#ifndef UNARYNUMERICMEASURE_HPP
#define UNARYNUMERICMEASURE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary numeric measure attribute
		struct UnaryNumericMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericMeasureAttribute,
    (string, name)
)

#endif
