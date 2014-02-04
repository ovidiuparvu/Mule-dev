#ifndef BINARYSUBSETATTRIBUTE_HPP
#define BINARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary subset attribute
		struct BinarySubsetAttribute {
			BinarySubsetMeasureAttribute 	binarySubsetMeasure;
			SubsetAttribute					subset;
			SpatialMeasureAttribute			spatialMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinarySubsetAttribute,
    (multiscale::verification::BinarySubsetMeasureAttribute, binarySubsetMeasure)
    (multiscale::verification::SubsetAttribute, subset)
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
)

#endif
