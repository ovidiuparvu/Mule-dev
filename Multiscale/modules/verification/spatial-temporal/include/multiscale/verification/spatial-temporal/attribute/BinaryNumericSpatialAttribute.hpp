#ifndef BINARYNUMERICSPATIALATTRIBUTE_HPP
#define BINARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary numeric spatial attribute
		struct BinaryNumericSpatialAttribute {
			BinaryNumericMeasureAttribute 	binaryNumericMeasure;
			NumericSpatialAttribute			numericSpatialMeasure;
			NumericAttribute				numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericMeasureAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericSpatialAttribute, numericSpatialMeasure)
    (multiscale::verification::NumericAttribute, numericMeasure)
)

#endif
