#ifndef TERNARYSUBSETMEASUREATTRIBUTE_HPP
#define TERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a ternary subset measure type
		enum class TernarySubsetMeasureType : int {
			Percentile = 1,		/*!< The percentile */
			Quartile = 2		/*!< The quartile */
		};

		//! Class for representing a ternary subset measure attribute
		class TernarySubsetMeasureAttribute {

			public:

				TernarySubsetMeasureType ternarySubsetMeasure;	/*!< The ternary subset measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TernarySubsetMeasureAttribute,
    (multiscale::verification::TernarySubsetMeasureType, ternarySubsetMeasure)
)

#endif
