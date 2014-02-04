#ifndef NUMERICSPATIALATTRIBUTE_HPP
#define NUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


namespace multiscale {

	namespace verification {

		//! Variant for a numeric spatial attribute
		typedef boost::variant<
			multiscale::verification::UnarySubsetAttribute,
			multiscale::verification::BinarySubsetAttribute,
			multiscale::verification::TernarySubsetAttribute,
			multiscale::verification::QuaternarySubsetAttribute,
			multiscale::verification::UnaryNumericSpatialAttribute,
			multiscale::verification::BinaryNumericSpatialAttribute
		> numericSpatialAttribute_;

		//! Structure for representing a numeric spatial attribute
		struct NumericSpatialAttribute {
			numericSpatialAttribute_ numericSpatialMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialAttribute,
    (multiscale::verification::numericSpatialAttribute_, numericSpatialMeasure)
)

#endif
