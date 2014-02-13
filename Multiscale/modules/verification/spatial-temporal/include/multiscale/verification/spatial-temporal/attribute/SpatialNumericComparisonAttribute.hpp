#ifndef SPATIALNUMERICCOMPARISONATTRIBUTE_HPP
#define SPATIALNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a spatial numeric comparison attribute
		struct SpatialNumericComparisonAttribute {
			SpatialMeasureAttribute spatialMeasure;
			ComparatorAttribute		comparator;
			NumericMeasureAttribute		numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SpatialNumericComparisonAttribute,
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttribute, numericMeasure)
)

#endif
