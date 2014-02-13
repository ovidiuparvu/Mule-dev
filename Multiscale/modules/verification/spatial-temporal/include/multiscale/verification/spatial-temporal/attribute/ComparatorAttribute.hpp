#ifndef COMPARATORATTRIBUTE_HPP
#define COMPARATORATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Enumeration for representing a comparator type
		enum class ComparatorType : int {
			GreaterThanOrEqual = 1,		/*!< Greater than or equal*/
			LessThanOrEqual = 2,		/*!< Less than or equal */
			Equal = 3					/*!< Equal */
		};

		//! Class for representing a comparator attribute
		class ComparatorAttribute {

			public:

				ComparatorType comparator;	/*!< The comparator */

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ComparatorAttribute,
    (multiscale::verification::ComparatorType, comparator)
)

#endif
