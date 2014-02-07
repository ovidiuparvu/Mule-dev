#ifndef IMPLICATIONEVALUATOR_HPP
#define IMPLICATIONEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/evaluation/BooleanEvaluator.hpp"


namespace multiscale {

	namespace verification {

		class ImplicationEvaluator : public BooleanEvaluator {

		public:

			//! Evaluate the truth value of (firstOperand IMPLIES secondOperand)
			/*!
			 * \param firstOperand	First boolean operand
			 * \param secondOperand	Second boolean operand
			 */
			bool operator()(bool firstOperand, bool secondOperand) const override;

		};

	};

};

#endif
