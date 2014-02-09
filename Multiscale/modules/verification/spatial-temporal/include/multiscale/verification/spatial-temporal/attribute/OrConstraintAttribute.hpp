#ifndef ORCONSTRAINTATTRIBUTE_HPP
#define ORCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/evaluation/OrEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

	namespace verification {

		//! Class for representing an "or" constraint attribute
		class OrConstraintAttribute : public Attribute {

		public:

			ConstraintAttributeType constraint;	/*!< The constraint following the "or" operator */

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

                return OrEvaluator()(truthValue, constraintEvaluation);
            }

		};

	};

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
