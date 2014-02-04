#ifndef BINARYNUMERICNUMERICATTRIBUTE_HPP
#define BINARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a binary numeric numeric measure attribute
		struct BinaryNumericNumericAttribute {
			BinaryNumericMeasureAttribute 	binaryNumericMeasure;
			NumericAttribute			firstNumericMeasure;
			NumericAttribute				secondNumericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericNumericAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericAttribute, firstNumericMeasure)
    (multiscale::verification::NumericAttribute, secondNumericMeasure)
)

#endif
