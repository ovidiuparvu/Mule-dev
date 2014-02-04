#ifndef SPATIALMEASUREATTRIBUTE_HPP
#define SPATIALMEASUREATTRIBUTE_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

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
