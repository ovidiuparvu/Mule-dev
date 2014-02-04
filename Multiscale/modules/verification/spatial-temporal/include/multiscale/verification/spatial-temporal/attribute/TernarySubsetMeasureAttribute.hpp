#ifndef TERNARYSUBSETMEASUREATTRIBUTE_HPP
#define TERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a ternary subset measure attribute
		struct TernarySubsetMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TernarySubsetMeasureAttribute,
    (string, name)
)

#endif
