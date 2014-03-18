#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"

using namespace multiscale::verification;


bool ModelChecker::evaluate(const SpatialTemporalTrace &trace) {
    bool evaluationResult = abstractSyntaxTree.evaluate(trace);

    updateModelChecker(evaluationResult);

    return evaluationResult;
}

void ModelChecker::updateModelChecker(bool evaluationResult) {
    if (evaluationResult) {
        updateModelCheckerForTrueEvaluation();
    } else {
        updateModelCheckerForFalseEvaluation();
    }
}
