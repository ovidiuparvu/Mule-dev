#ifndef UNARYSUBSETMEASUREATTRIBUTE_HPP
#define UNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary subset measure attribute
		struct UnarySubsetMeasureAttribute {
			std::string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetMeasureAttribute,
    (std::string, name)
)

#endif
