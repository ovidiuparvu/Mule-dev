#ifndef DIFFERENCEATTRIBUTE_HPP
#define DIFFERENCEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a difference attribute
		struct DifferenceAttribute {
			NumericMeasureAttribute		lhsNumericMeasure;
			ComparatorAttribute		comparator;
			NumericMeasureAttribute		rhsNumericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::DifferenceAttribute,
    (NumericMeasureAttribute, lhsNumericMeasure)
	(ComparatorAttribute, comparator)
	(NumericMeasureAttribute, rhsNumericMeasure)
)

#endif
