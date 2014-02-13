#ifndef SUBSETSPECIFICATTRIBUTE_HPP
#define SUBSETSPECIFICATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a specific subset type
		enum class SubsetSpecificType : int {
			Clusters = 1,
			Regions = 2
		};

		//! Class for representing a subset specific attribute
		class SubsetSpecificAttribute {

			public:

				SubsetSpecificType subsetSpecific;	/*!< The specific subset which should be considered */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSpecificAttribute,
    (multiscale::verification::SubsetSpecificType, subsetSpecific)
)

#endif
