#ifndef QUATERNARYSUBSETATTRIBUTE_HPP
#define QUATERNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a quaternary subset attribute
		struct QuaternarySubsetAttribute {
			QuaternarySubsetMeasureAttribute 	quaternarySubsetMeasure;
			SubsetAttribute						firstSubset;
			SpatialMeasureAttribute				firstSpatialMeasure;
			SubsetAttribute						secondSubset;
			SpatialMeasureAttribute				secondSpatialMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::QuaternarySubsetAttribute,
    (multiscale::verification::QuaternarySubsetMeasureAttribute, quaternarySubsetMeasure)
    (multiscale::verification::SubsetAttribute, firstSubset)
    (multiscale::verification::SpatialMeasureAttribute, firstSpatialMeasure)
    (multiscale::verification::SubsetAttribute, secondSubset)
    (multiscale::verification::SpatialMeasureAttribute, secondSpatialMeasure)
)

#endif
