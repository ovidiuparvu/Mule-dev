#ifndef NUMERICSPATIALNUMERICCOMPARISONATTRIBUTE_HPP
#define NUMERICSPATIALNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a numeric spatial numeric comparison attribute
		struct NumericSpatialNumericComparisonAttribute {
			NumericSpatialAttribute 		numericSpatialMeasure;
			ComparatorAttribute				comparator;
			NumericAttribute				numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialNumericComparisonAttribute,
    (NumericSpatialAttribute, numericSpatialMeasure)
	(ComparatorAttribute, comparator)
	(NumericAttribute, numericMeasure)
)

#endif
