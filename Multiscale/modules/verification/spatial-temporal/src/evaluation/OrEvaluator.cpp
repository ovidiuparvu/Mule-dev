#include "multiscale/verification/spatial-temporal/evaluation/OrEvaluator.hpp"

using namespace multiscale::verification;


bool OrEvaluator::operator()(bool firstOperand, bool secondOperand) const {
	return (firstOperand || secondOperand);
}
