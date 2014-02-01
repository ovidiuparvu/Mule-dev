#ifndef QUATERNARYSUBSETMEASUREATTRIBUTE_HPP
#define QUATERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a quaternary subset measure attribute
		struct QuaternarySubsetMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::QuaternarySubsetMeasureAttribute,
    (string, name)
)

#endif
