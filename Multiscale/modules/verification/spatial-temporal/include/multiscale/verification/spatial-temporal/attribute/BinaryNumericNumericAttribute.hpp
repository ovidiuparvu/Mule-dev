#ifndef BINARYNUMERICNUMERICATTRIBUTE_HPP
#define BINARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary numeric numeric measure attribute
		struct BinaryNumericNumericMeasureAttribute {
			BinaryNumericMeasureAttribute 	binaryNumericMeasure;
			NumericMeasureAttribute			firstNumericMeasure;
			NumericMeasureAttribute			secondNumericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericNumericMeasureAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericMeasureAttribute, firstNumericMeasure)
    (multiscale::verification::NumericMeasureAttribute, secondNumericMeasure)
)

#endif
