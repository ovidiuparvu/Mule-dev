#include "multiscale/verification/spatial-temporal/evaluation/ImplicationEvaluator.hpp"

using namespace multiscale::verification;


bool ImplicationEvaluator::operator()(bool firstOperand, bool secondOperand) const {
	return ((!firstOperand) || secondOperand);
}
