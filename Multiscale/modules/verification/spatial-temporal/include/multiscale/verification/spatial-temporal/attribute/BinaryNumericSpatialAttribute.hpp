#ifndef BINARYNUMERICSPATIALATTRIBUTE_HPP
#define BINARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a binary numeric spatial attribute
		class BinaryNumericSpatialAttribute {

			public:

				BinaryNumericMeasureAttribute 	binaryNumericMeasure;		/*!< The binary numeric measure */
				NumericSpatialAttributeType		numericSpatialMeasure;		/*!< The numeric spatial measure */
				NumericMeasureAttributeType		numericMeasure;				/*!< The numeric measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericSpatialAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericSpatialAttributeType, numericSpatialMeasure)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
