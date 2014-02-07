#ifndef ANDEVALUATOR_HPP
#define ANDEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/evaluation/BooleanEvaluator.hpp"


namespace multiscale {

	namespace verification {

		class AndEvaluator : public BooleanEvaluator {

		public:

			//! Evaluate the truth value of (firstOperand AND secondOperand)
			/*!
			 * \param firstOperand	First boolean operand
			 * \param secondOperand	Second boolean operand
			 */
			bool operator()(bool firstOperand, bool secondOperand) const override;

		};

	};

};

#endif
