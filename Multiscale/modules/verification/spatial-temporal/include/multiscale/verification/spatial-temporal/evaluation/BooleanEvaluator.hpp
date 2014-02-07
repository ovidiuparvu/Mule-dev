#ifndef BOOLEANEVALUATOR_HPP
#define BOOLEANEVALUATOR_HPP

namespace multiscale {

	namespace verification {

		class BooleanEvaluator {

			public:

				virtual ~BooleanEvaluator() {};

				//! Evaluate the truth value of firstOperand BOOLEAN_OPERATOR secondOperand
				/*!
				 * \param firstOperand	First boolean operand
				 * \param secondOperand	Second boolean operand
				 */
				virtual bool operator()(bool firstOperand, bool secondOperand) const = 0;

		};

	};

};

#endif
