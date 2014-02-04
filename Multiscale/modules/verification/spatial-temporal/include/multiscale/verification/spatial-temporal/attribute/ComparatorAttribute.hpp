#ifndef COMPARATORATTRIBUTE_HPP
#define COMPARATORATTRIBUTE_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace std;


namespace multiscale {

	namespace verification {

		//! Structure for representing a comparator attribute
		struct ComparatorAttribute {
			string comparator;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ComparatorAttribute,
    (string, comparator)
)

#endif
