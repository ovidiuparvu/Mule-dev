#ifndef FILTERSUBSETATTRIBUTE_HPP
#define FILTERSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a filter subset attribute
		struct FilterSubsetAttribute {
			SubsetSpecificAttribute subsetSpecific;
			ConstraintAttribute		constraint;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FilterSubsetAttribute,
    (multiscale::verification::SubsetSpecificAttribute, subsetSpecific)
    (multiscale::verification::ConstraintAttribute, constraint)
)

#endif
