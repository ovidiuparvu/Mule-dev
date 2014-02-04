#ifndef UNARYSUBSETMEASUREATTRIBUTE_HPP
#define UNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary subset measure attribute
		struct UnarySubsetMeasureAttribute {
			string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetMeasureAttribute,
    (string, name)
)

#endif
