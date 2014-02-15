#ifndef SUBSETATTRIBUTE_HPP
#define SUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/FilterSubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

	    // Forward declaration of classes
	    class SubsetAttribute;


		//! Variant for a subset attribute
		typedef boost::variant<
			Nil,
			multiscale::verification::SubsetSpecificAttribute,
			multiscale::verification::FilterSubsetAttribute,
			boost::recursive_wrapper<multiscale::verification::SubsetAttribute>
		> SubsetAttributeType;


		//! Class for representing a subset attribute
		class SubsetAttribute {

			public:

				SubsetAttributeType subset; /*!< The subset */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetAttribute,
    (multiscale::verification::SubsetAttributeType, subset)
)

#endif
