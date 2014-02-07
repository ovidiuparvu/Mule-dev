#ifndef EQUIVALENCEEVALUATOR_HPP
#define EQUIVALENCEEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/evaluation/BooleanEvaluator.hpp"


namespace multiscale {

	namespace verification {

		class EquivalenceEvaluator : public BooleanEvaluator {

		public:

			//! Evaluate the truth value of (firstOperand EQUIVALENT secondOperand)
			/*!
			 * \param firstOperand	First boolean operand
			 * \param secondOperand	Second boolean operand
			 */
			bool operator()(bool firstOperand, bool secondOperand) const override;

		};

	};

};

#endif
