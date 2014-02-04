#ifndef UNARYNUMERICSPATIALATTRIBUTE_HPP
#define UNARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary numeric spatial attribute
		struct UnaryNumericSpatialAttribute {
			UnaryNumericMeasureAttribute 	unaryNumericMeasure;
			NumericSpatialAttribute			numericSpatialMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericSpatialAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericSpatialAttribute, numericSpatialMeasure)
)

#endif
