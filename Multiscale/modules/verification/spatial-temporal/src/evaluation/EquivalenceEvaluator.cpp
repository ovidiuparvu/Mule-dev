#include "multiscale/verification/spatial-temporal/evaluation/EquivalenceEvaluator.hpp"

using namespace multiscale::verification;


bool EquivalenceEvaluator::operator()(bool firstOperand, bool secondOperand) const {
	return ((!firstOperand) || secondOperand) && ((!secondOperand) || (firstOperand));
}
