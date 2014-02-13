#ifndef NUMERICMEASUREATTRIBUTE_HPP
#define NUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericNumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericNumericAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		//! Variant for the numeric attribute
		typedef boost::variant<
			multiscale::verification::NumericSpatialAttribute,
			double,
			multiscale::verification::NumericStateVariableAttribute,
			multiscale::verification::UnaryNumericNumericAttribute,
			multiscale::verification::BinaryNumericNumericAttribute
		> numericAttribute_;

		//! Class for representing a numeric measure attribute
		class NumericMeasureAttribute {

			public:

				numericAttribute_ numericMeasure;

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericMeasureAttribute,
    (numericAttribute_, numericMeasure)
)

#endif
