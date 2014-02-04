#ifndef TERNARYSUBSETATTRIBUTE_HPP
#define TERNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a ternary subset attribute
		struct TernarySubsetAttribute {
			TernarySubsetMeasureAttribute 	ternarySubsetMeasure;
			SubsetAttribute					subset;
			SpatialMeasureAttribute			spatialMeasure;
			double							realNumber;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TernarySubsetAttribute,
    (multiscale::verification::TernarySubsetMeasureAttribute, ternarySubsetMeasure)
    (multiscale::verification::SubsetAttribute, subset)
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (double, realNumber)
)

#endif
