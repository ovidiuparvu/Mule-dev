#ifndef NUMERICSPATIALATTRIBUTE_HPP
#define NUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		// Forward declaration of classes
		class NumericSpatialAttribute;


		//! Variant for a numeric spatial attribute
		typedef boost::variant<
			UnarySubsetAttribute,
			BinarySubsetAttribute,
			TernarySubsetAttribute,
			QuaternarySubsetAttribute,
			boost::recursive_wrapper<NumericSpatialAttribute>
		> NumericSpatialAttributeType;


		//! Class for representing a numeric spatial attribute
		class NumericSpatialAttribute {

			public:

				NumericSpatialAttributeType numericSpatialMeasure;	/*!< The numeric spatial measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialAttribute,
    (multiscale::verification::NumericSpatialAttributeType, numericSpatialMeasure)
)

#endif
