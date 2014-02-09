#ifndef OREVALUATOR_HPP
#define OREVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/evaluation/BooleanEvaluator.hpp"


namespace multiscale {

	namespace verification {

	    //! Class for representing the evaluation of an "or" logical expression
		class OrEvaluator : public BooleanEvaluator {

		public:

			//! Evaluate the truth value of (firstOperand OR secondOperand)
			/*!
			 * \param firstOperand	First boolean operand
			 * \param secondOperand	Second boolean operand
			 */
			bool operator()(bool firstOperand, bool secondOperand) const override;

		};

	};

};

#endif
