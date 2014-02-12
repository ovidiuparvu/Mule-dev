#ifndef EQUIVALENCECONSTRAINTATTRIBUTE_HPP
#define EQUIVALENCECONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing an "equivalence" constraint attribute
		class EquivalenceConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType constraint; /*!< The constraint following the "equivalence" operator */

            //! Evaluate the constraint
            bool evaluate() const override {
                return evaluateConsideringTruthValue(false);
            }

            //! Evaluate the constraint considering the given truth value
            /*!
             * \param truthValue The given truth value
             */
            bool evaluateConsideringTruthValue(const bool &truthValue) const override{
                bool constraintEvaluation = evaluateUnaryExpression(constraint);

                return (
                	((!truthValue) || (constraintEvaluation)) &&
                	((!constraintEvaluation) || (truthValue))
                );
            }

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::EquivalenceConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
