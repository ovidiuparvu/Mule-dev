#ifndef BINARYNUMERICMEASUREATTRIBUTE_HPP
#define BINARYNUMERICMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a binary numeric measure type
		enum class BinaryNumericMeasureType : int {
			Div = 1,	/*!< Division */
			Log = 2,	/*!< Logarithm */
			Minus = 3,	/*!< Subtraction */
			Mod = 4,	/*!< Remainder of division */
			Plus = 5,	/*!< Addition */
			Power = 6,	/*!< Raise to power */
			Times = 7	/*!< Multiplication */
		};

		//! Class for representing a binary numeric measure attribute
		class BinaryNumericMeasureAttribute {

			public:

				BinaryNumericMeasureType binaryNumericMeasure;	/*!< The binary numeric measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericMeasureAttribute,
    (multiscale::verification::BinaryNumericMeasureType, binaryNumericMeasure)
)

#endif
