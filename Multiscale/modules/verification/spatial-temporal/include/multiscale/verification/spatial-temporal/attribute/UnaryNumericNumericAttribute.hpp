#ifndef UNARYNUMERICNUMERICATTRIBUTE_HPP
#define UNARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

using namespace multiscale::verification;


namespace multiscale {

	namespace verification {

		//! Structure for representing a unary numeric numeric measure attribute
		struct UnaryNumericNumericAttribute {
			UnaryNumericMeasureAttribute 	unaryNumericMeasure;
			NumericAttribute				numericMeasure;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericNumericAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericAttribute, numericMeasure)
)

#endif
