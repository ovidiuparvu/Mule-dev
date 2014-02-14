#ifndef UNARYNUMERICSPATIALATTRIBUTE_HPP
#define UNARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a unary numeric spatial attribute
		class UnaryNumericSpatialAttribute {

			public:

				UnaryNumericMeasureAttribute 	unaryNumericMeasure;		/*!< The unary numeric measure */
				NumericSpatialAttributeType		numericSpatialMeasure;		/*!< The numeric spatial measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericSpatialAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericSpatialAttributeType, numericSpatialMeasure)
)

#endif
