#ifndef LOGICPROPERTYATTRIBUTE_HPP
#define LOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <vector>


namespace multiscale {

	namespace verification {

		// Forward declaration of classes
		class AndLogicPropertyAttribute;
		class EquivalenceLogicPropertyAttribute;
		class ImplicationLogicPropertyAttribute;
		class OrLogicPropertyAttribute;
		class PrimaryLogicPropertyAttribute;
		class UntilLogicPropertyAttribute;


		//! Variant for the logic property attribute
		typedef boost::variant<
			Nil,
			boost::recursive_wrapper<OrLogicPropertyAttribute>,
			boost::recursive_wrapper<AndLogicPropertyAttribute>,
			boost::recursive_wrapper<ImplicationLogicPropertyAttribute>,
			boost::recursive_wrapper<EquivalenceLogicPropertyAttribute>,
			boost::recursive_wrapper<UntilLogicPropertyAttribute>,
			boost::recursive_wrapper<PrimaryLogicPropertyAttribute>
		> LogicPropertyAttributeType;


		//! Class for representing a logic property attribute
		class LogicPropertyAttribute {

			LogicPropertyAttributeType 				firstLogicProperty;		/*!< The first logic property */
			std::vector<LogicPropertyAttributeType>	nextLogicProperties; 	/*!< The next logic properties */
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::LogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, firstLogicProperty)
    (std::vector<multiscale::verification::LogicPropertyAttributeType>, nextLogicProperties)
)

#endif
