#ifndef ANDCONSTRAINTATTRIBUTE_HPP
#define ANDCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing an "and" constraint attribute
		class AndConstraintAttribute : public Attribute {

		public:

            ConstraintAttributeType constraint;	/*!< The constraint following the "and" operator */

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

                return (truthValue && constraintEvaluation);
            }

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
