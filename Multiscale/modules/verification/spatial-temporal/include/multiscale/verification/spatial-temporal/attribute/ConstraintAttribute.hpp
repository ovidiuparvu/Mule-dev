#ifndef CONSTRAINTATTRIBUTE_HPP
#define CONSTRAINTATTRIBUTE_HPP

//#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <list>

namespace multiscale {

	namespace verification {

        // Forward declaration of classes
        class ConstraintAttribute;
        class OrConstraintAttribute;
        class AndConstraintAttribute;
        class ImplicationConstraintAttribute;
        class EquivalenceConstraintAttribute;
        class UnaryConstraintAttribute;


        //! Variant for a constraint attribute type
        typedef boost::variant<
            Nil,
            boost::recursive_wrapper<ConstraintAttribute>,
            boost::recursive_wrapper<OrConstraintAttribute>,
            boost::recursive_wrapper<AndConstraintAttribute>,
            boost::recursive_wrapper<ImplicationConstraintAttribute>,
            boost::recursive_wrapper<EquivalenceConstraintAttribute>,
            boost::recursive_wrapper<UnaryConstraintAttribute>
        > ConstraintAttributeType;


		//! Class for representing a constraint attribute
		class ConstraintAttribute {
//		class ConstraintAttribute : public Attribute {

			public:

				ConstraintAttributeType 	        firstConstraint;		/*!< The first constraint */
				std::list<ConstraintAttributeType>	nextConstraints;		/*!< The next constraints */

				//! Evaluate the constraint
//				bool evaluate(bool truthValue) const override {
//					bool firstEvaluationResult = evaluateUnaryExpression(firstConstraint);
//
//					return evaluateNaryNextExpressions(firstEvaluationResult, nextConstraints);
//				}

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, firstConstraint)
    (std::list<multiscale::verification::ConstraintAttributeType>, nextConstraints)
)

#endif
