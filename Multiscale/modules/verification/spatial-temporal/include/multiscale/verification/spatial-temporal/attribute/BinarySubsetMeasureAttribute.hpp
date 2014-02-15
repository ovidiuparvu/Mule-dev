#ifndef BINARYSUBSETMEASUREATTRIBUTE_HPP
#define BINARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a binary subset measure type
		enum class BinarySubsetMeasureType : int {
			Avg     = 1,    /*!< The average (arithmetic mean) */
			Geomean = 2,	/*!< The geometric mean */
			Harmean = 3,	/*!< The harmonic mean */
			Kurt    = 4,	/*!< The kurtosis */
			Max     = 5,	/*!< The maximum */
			Median  = 6,	/*!< The median */
			Min     = 7,	/*!< The minimum */
			Mode    = 8, 	/*!< The mode */
			Product = 9,	/*!< The product */
			Skew    = 10,	/*!< The skew */
			Stdev   = 11,	/*!< The standard deviation */
			Sum     = 12,	/*!< The sum */
			Var     = 13	/*!< The variance */
		};

		//! Overload the output stream operator for the enumeration
		/*!
		 * \param out						Output stream
		 * \param binarySubsetMeasureType	The binary subset measure type to be printed out
		 */
		std::ostream& operator<<(std::ostream& out, const BinarySubsetMeasureType &binarySubsetMeasureType);


		//! Class for representing a binary subset measure attribute
		class BinarySubsetMeasureAttribute {

			public:

				BinarySubsetMeasureType binarySubsetMeasure;	/*!< The binary subset measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinarySubsetMeasureAttribute,
    (multiscale::verification::BinarySubsetMeasureType, binarySubsetMeasure)
)

#endif
