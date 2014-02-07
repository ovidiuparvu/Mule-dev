#include "multiscale/verification/spatial-temporal/evaluation/AndEvaluator.hpp"

using namespace multiscale::verification;


bool AndEvaluator::operator()(bool firstOperand, bool secondOperand) const {
	return (firstOperand && secondOperand);
}
