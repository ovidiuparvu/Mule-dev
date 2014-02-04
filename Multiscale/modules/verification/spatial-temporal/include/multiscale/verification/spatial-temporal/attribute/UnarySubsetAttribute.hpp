#ifndef UNARYSUBSETATTRIBUTE_HPP
#define UNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary subset attribute
		struct UnarySubsetAttribute {
			UnarySubsetMeasureAttribute unarySubsetMeasure;
			SubsetAttribute				subset;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetAttribute,
    (multiscale::verification::UnarySubsetMeasureAttribute, unarySubsetMeasure)
    (multiscale::verification::SubsetAttribute, subset)
)

#endif
