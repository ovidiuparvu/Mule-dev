#ifndef SPATIALMEASUREATTRIBUTE_HPP
#define SPATIALMEASUREATTRIBUTE_HPP

#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a spatial measure attribute
		struct SpatialMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SpatialMeasureAttribute,
    (string, name)
)

#endif
