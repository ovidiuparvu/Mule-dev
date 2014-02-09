#ifndef UNARYEVALUATOR_HPP
#define UNARYEVALUATOR_HPP

namespace multiscale {

	namespace verification {

	    //! Class for representing the evaluation of a unary logical expression
		class UnaryEvaluator {

			public:

				virtual ~UnaryEvaluator() {};

				//! Evaluate the truth value of UNARY_OPERATOR operand
				/*!
				 * \param operand   The operand
				 */
				virtual bool operator()(bool operand) const = 0;

		};

	};

};

#endif
