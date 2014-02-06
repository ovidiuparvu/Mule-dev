#ifndef NUMERICSTATEVARIABLEATTRIBUTE_HPP
#define NUMERICSTATEVARIABLEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AttributeVisitor.hpp"
#include "multiscale/verification/spatial-temporal/attribute/StateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing a numeric state variable attribute
		class NumericStateVariableAttribute : public Attribute {

			public:

				StateVariableAttribute name;

				//! Evaluate the constraint
				bool evaluate() const override {
					return name.evaluate();
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericStateVariableAttribute,
    (multiscale::verification::StateVariableAttribute, name)
)

#endif
