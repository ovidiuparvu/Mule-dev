#ifndef DIFFERENCEATTRIBUTE_HPP
#define DIFFERENCEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a difference attribute
		struct DifferenceAttribute {
			NumericAttribute		lhsNumericMeasure;
			ComparatorAttribute		comparator;
			NumericAttribute		rhsNumericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::DifferenceAttribute,
    (NumericAttribute, lhsNumericMeasure)
	(ComparatorAttribute, comparator)
	(NumericAttribute, rhsNumericMeasure)
)

#endif
