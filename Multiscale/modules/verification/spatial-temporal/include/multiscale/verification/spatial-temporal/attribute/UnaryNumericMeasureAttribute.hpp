#ifndef UNARYNUMERICMEASURE_HPP
#define UNARYNUMERICMEASURE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a unary numeric measure type
		enum class UnaryNumericMeasureType : int {
			Abs = 1,	/*!< Absolute value */
			Ceil = 2,	/*!< Ceiling */
			Floor = 3,	/*!< Floor */
			Round = 4,	/*!< Round */
			Sign = 5,	/*!< Sign: -1 (-), +1 (+) or 0 (0) */
			Sqrt = 6,	/*!< Square root */
			Trunc = 7	/*!< Truncation */
		};

		//! Class for representing a unary numeric measure attribute
		class UnaryNumericMeasureAttribute {

			public:

				UnaryNumericMeasureType unaryNumericMeasure;	/*!< The unary numeric measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericMeasureAttribute,
    (multiscale::verification::UnaryNumericMeasureType, unaryNumericMeasure)
)

#endif
