#ifndef QUATERNARYSUBSETMEASUREATTRIBUTE_HPP
#define QUATERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

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
