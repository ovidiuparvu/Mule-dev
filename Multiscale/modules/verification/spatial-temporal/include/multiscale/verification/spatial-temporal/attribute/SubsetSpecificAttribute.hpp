#ifndef SUBSETSPECIFICATTRIBUTE_HPP
#define SUBSETSPECIFICATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>


namespace multiscale {

	namespace verification {

		//! Structure for representing a subset specific attribute
		struct SubsetSpecificAttribute {
			std::string name;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSpecificAttribute,
    (std::string, name)
)

#endif
