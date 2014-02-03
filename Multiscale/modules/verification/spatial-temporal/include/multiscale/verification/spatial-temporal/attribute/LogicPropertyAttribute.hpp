#ifndef LOGICPROPERTYATTRIBUTE_HPP
#define LOGICPROPERTYATTRIBUTE_HPP

#include <boost/variant/recursive_variant.hpp>


namespace multiscale {

	namespace verification {

		//! Structure for representing a logic property attribute
		struct LogicPropertyAttribute {
			// TODO: Add fields
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::LogicPropertyAttribute,
)

#endif
