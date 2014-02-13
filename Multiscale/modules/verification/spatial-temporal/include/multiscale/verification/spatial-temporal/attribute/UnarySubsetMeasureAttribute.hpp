#ifndef UNARYSUBSETMEASUREATTRIBUTE_HPP
#define UNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a unary subset measure type
		enum class UnarySubsetMeasureType : int {
			Count = 1,			/*!< Number of spatial entities */
			Clusteredness = 2,	/*!< The overall clusteredness of the entities */
			Density = 3			/*!< The overall density of the entities */
		};

		//! Class for representing a unary subset measure attribute
		class UnarySubsetMeasureAttribute {

			public:

				UnarySubsetMeasureType unarySubsetMeasure;	/*!< The unary subset measure */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetMeasureAttribute,
    (multiscale::verification::UnarySubsetMeasureType, unarySubsetMeasure)
)

#endif
