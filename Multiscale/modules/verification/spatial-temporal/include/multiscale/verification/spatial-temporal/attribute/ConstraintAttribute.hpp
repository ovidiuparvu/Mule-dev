#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AttributeVisitor.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttributeType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <list>


namespace multiscale {

	namespace verification {

		//! Class for representing a constraint attribute
		class ConstraintAttribute : public Attribute {

			public:

				ConstraintAttributeType				firstConstraint;
				std::list<ConstraintAttributeType> 	nextConstraints;

				//! Evaluate the constraint
				bool evaluate() const override {
					bool evaluationResult = evaluateFirstConstraint();

					if (!evaluationResult) {
						evaluationResult = evaluateNextConstraints();
					}

					return evaluationResult;
				}

				//! Evaluate the first constraint
				bool evaluateFirstConstraint() const {
					return boost::apply_visitor(AttributeVisitor(), firstConstraint);
				}

				//! Evaluate the next constraints
				bool evaluateNextConstraints() const {
					for (const auto &nextConstraint : nextConstraints) {
						if (boost::apply_visitor(AttributeVisitor(), nextConstraint)) {
							return true;
						}
					}

					return false;
				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::list<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
