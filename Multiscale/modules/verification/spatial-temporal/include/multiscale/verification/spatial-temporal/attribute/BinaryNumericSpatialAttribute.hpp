#ifndef BINARYNUMERICSPATIALATTRIBUTE_HPP
#define BINARYNUMERICSPATIALATTRIBUTE_HPP

// TODO: Add missing imports
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary numeric spatial attribute
		struct BinaryNumericSpatialAttribute {
			// TODO: Add missing fields
			BinaryNumericMeasureAttribute binaryNumericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericMeasureAttribute,
    (BinaryNumericMeasureAttribute, binaryNumericMeasure)
)

#endif
