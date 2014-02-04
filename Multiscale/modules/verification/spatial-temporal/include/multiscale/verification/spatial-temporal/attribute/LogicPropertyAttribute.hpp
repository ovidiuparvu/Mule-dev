#ifndef LOGICPROPERTYATTRIBUTE_HPP
#define LOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/DifferenceAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialNumericComparisonAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericNumericComparisonAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NotAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/OrAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AndAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ImplicationAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/EquivalenceAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UntilAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FutureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/GloballyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NextAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NextNAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		//! Variant for the logic property attribute
		typedef boost::variant<
			multiscale::verification::DifferenceAttribute,
			multiscale::verification::NumericSpatialNumericComparisonAttribute,
			multiscale::verification::NumericNumericComparisonAttribute,
			multiscale::verification::NotAttribute,
			multiscale::verification::OrAttribute,
			multiscale::verification::AndAttribute,
			multiscale::verification::ImplicationAttribute,
			multiscale::verification::EquivalenceAttribute,
			multiscale::verification::UntilAttribute,
			multiscale::verification::FutureAttribute,
			multiscale::verification::GloballyAttribute,
			multiscale::verification::NextAttribute,
			multiscale::verification::NextNAttribute,
			boost::recursive_wrapper<multiscale::verification::LogicPropertyAttribute>
		> logicPropertyAttribute_;

		//! Structure for representing a logic property attribute
		struct LogicPropertyAttribute {
			logicPropertyAttribute_ logicProperty;
		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::LogicPropertyAttribute,
    (multiscale::verification::logicPropertyAttribute_, logicProperty)
)

#endif
