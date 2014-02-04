#ifndef SUBSETATTRIBUTE_HPP
#define SUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FilterSubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Variant for a subset attribute
		typedef boost::variant<
			multiscale::verification::SubsetSpecificAttribute,
			multiscale::verification::FilterSubsetAttribute
		> subsetAttribute_;

		//! Structure for representing a subset attribute
		struct SubsetAttribute {
			multiscale::verification::subsetAttribute_ subset;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetAttribute,
    (multiscale::verification::subsetAttribute_, subset)
)

#endif
