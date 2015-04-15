#include "multiscale/util/statistics/BinomialDistribution.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"

using namespace multiscale::verification;


bool ModelChecker::evaluate(const SpatialTemporalTrace &trace) {
    bool evaluationResult = abstractSyntaxTree.evaluate(trace, multiscaleArchitectureGraph);

    updateModelChecker(evaluationResult);

    return evaluationResult;
}

void ModelChecker::updateHypothesesPValues() {
    if (!arePValuesUpdatedFlag) {
        updateHypothesesPValuesConsideringComparator();

        arePValuesUpdatedFlag = true;
    }
}

bool ModelChecker::doesPropertyHoldUsingPValues() {
    updateHypothesesPValues();

    return (nullHypothesisPValue < alternativeHypothesisPValue);
}

std::string ModelChecker::getDetailedResultsUsingPValues() {
    updateHypothesesPValues();

    return (
        MSG_OUTPUT_P_VALUE_BEGIN +
        StringManipulator::toString(std::min(nullHypothesisPValue, alternativeHypothesisPValue)) +
        MSG_OUTPUT_P_VALUE_MIDDLE1 + StringManipulator::toString(nullHypothesisPValue) +
        MSG_OUTPUT_P_VALUE_MIDDLE2 + StringManipulator::toString(alternativeHypothesisPValue) +
        MSG_OUTPUT_P_VALUE_END
    );
}

bool ModelChecker::isGreaterThanOrEqualToComparator() {
    ComparatorType comparator = abstractSyntaxTree.getComparator();

    return (
        (comparator == ComparatorType::GreaterThan) ||
        (comparator == ComparatorType::GreaterThanOrEqual)
    );
}

void ModelChecker::updateModelChecker(bool evaluationResult) {
    updateModelCheckerForEvaluationResult(evaluationResult);

    arePValuesUpdatedFlag = false;
}

void ModelChecker::updateModelCheckerForEvaluationResult(bool evaluationResult) {
    if (evaluationResult) {
        updateModelCheckerForTrueEvaluation();
    } else {
        updateModelCheckerForFalseEvaluation();
    }
}

void ModelChecker::updateModelCheckerForTrueEvaluation() {
    totalNumberOfTrueEvaluations++;
    totalNumberOfEvaluations++;
}

void ModelChecker::updateModelCheckerForFalseEvaluation() {
    totalNumberOfEvaluations++;
}

void ModelChecker::updateHypothesesPValuesConsideringComparator() {
    if (isGreaterThanOrEqualToComparator()) {
        updateHypothesesPValuesForGreaterThan();
    } else {
        updateHypothesesPValuesForLessThan();
    }
}

void ModelChecker::updateHypothesesPValuesForGreaterThan() {
    unsigned int nrOfEvaluations = totalNumberOfEvaluations;
    unsigned int nrOfSuccesses   = totalNumberOfTrueEvaluations;
    double       probability     = abstractSyntaxTree.getProbability();

    updateNullAndAlternativeHypothesesPValues(nrOfEvaluations, nrOfSuccesses, probability);
}

void ModelChecker::updateHypothesesPValuesForLessThan() {
    unsigned int nrOfEvaluations = totalNumberOfEvaluations;
    unsigned int nrOfSuccesses   = (totalNumberOfEvaluations - totalNumberOfTrueEvaluations);
    double       probability     = abstractSyntaxTree.getProbability();

    updateNullAndAlternativeHypothesesPValues(nrOfEvaluations, nrOfSuccesses, probability);
}

void ModelChecker::updateNullAndAlternativeHypothesesPValues(unsigned int nrOfEvaluations,
                                                             unsigned int nrOfSuccesses,
                                                             double probability) {
    updateNullHypothesisPValue       (nrOfEvaluations, nrOfSuccesses, probability);
    updateAlternativeHypothesisPValue(nrOfEvaluations, nrOfSuccesses, probability);
}

void ModelChecker::updateNullHypothesisPValue(unsigned int nrOfEvaluations,
                                              unsigned int nrOfSuccesses,
                                              double probability) {
    if (nrOfSuccesses == 0) {
        nullHypothesisPValue = 1;
    } else {
        nullHypothesisPValue = 1 - BinomialDistribution::cdf(nrOfEvaluations, nrOfSuccesses - 1, probability);
    }
}

void ModelChecker::updateAlternativeHypothesisPValue(unsigned int nrOfEvaluations,
                                                     unsigned int nrOfSuccesses,
                                                     double probability) {
    alternativeHypothesisPValue = BinomialDistribution::cdf(nrOfEvaluations, nrOfSuccesses, probability);
}


// Constants
const std::string ModelChecker::MSG_OUTPUT_P_VALUE_BEGIN    = "The confidence level of the answer expressed as a p-value (lower is better): ";
const std::string ModelChecker::MSG_OUTPUT_P_VALUE_MIDDLE1  = " (p-value H0: ";
const std::string ModelChecker::MSG_OUTPUT_P_VALUE_MIDDLE2  = ", p-value H1: ";
const std::string ModelChecker::MSG_OUTPUT_P_VALUE_END      = ")";
