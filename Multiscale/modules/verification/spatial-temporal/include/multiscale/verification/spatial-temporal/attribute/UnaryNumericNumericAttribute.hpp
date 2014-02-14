#ifndef UNARYNUMERICNUMERICATTRIBUTE_HPP
#define UNARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a unary numeric numeric measure attribute
		class UnaryNumericNumericMeasureAttribute {

			public:

				UnaryNumericMeasureAttribute 	unaryNumericMeasure;	/*!< The unary numeric measure */
				NumericMeasureAttributeType		numericMeasure;			/*!< The considered numeric measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericNumericMeasureAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
