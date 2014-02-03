#ifndef NUMERICNUMERICCOMPARISONATTRIBUTE_HPP
#define NUMERICNUMERICCOMPARISONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"


using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a numeric numeric comparison attribute
		struct NumericNumericComparisonAttribute {
			NumericStateVariableAttribute 	numericStateVariable;
			ComparatorAttribute				comparator;
			NumericAttribute				numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericNumericComparisonAttribute,
    (NumericStateVariableAttribute, numericStateVariable)
	(ComparatorAttribute, comparator)
	(NumericAttribute, numericMeasure)
)

#endif
