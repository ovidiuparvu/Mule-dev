#include "multiscale/verification/spatial-temporal/evaluation/NotEvaluator.hpp"

using namespace multiscale::verification;


bool NotEvaluator::operator()(bool operand) const {
    return (!operand);
}
