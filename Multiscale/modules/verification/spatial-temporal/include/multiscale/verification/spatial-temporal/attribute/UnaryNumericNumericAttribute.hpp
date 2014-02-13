#ifndef UNARYNUMERICNUMERICATTRIBUTE_HPP
#define UNARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary numeric numeric measure attribute
		struct UnaryNumericNumericMeasureAttribute {
			UnaryNumericMeasureAttribute 	unaryNumericMeasure;
			NumericMeasureAttribute			numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericNumericMeasureAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericMeasureAttribute, numericMeasure)
)

#endif
