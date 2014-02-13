#ifndef QUATERNARYSUBSETMEASUREATTRIBUTE_HPP
#define QUATERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a quaternary subset measure type
		enum class QuaternarySubsetMeasureType : int {
			Covar = 1	/*!< Covariance */
		};

		//! Class for representing a quaternary subset measure attribute
		class QuaternarySubsetMeasureAttribute {

			public:

				QuaternarySubsetMeasureType quaternarySubsetMeasure;	/*!< The quaternary subset measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::QuaternarySubsetMeasureAttribute,
    (multiscale::verification::QuaternarySubsetMeasureType, quaternarySubsetMeasure)
)

#endif
