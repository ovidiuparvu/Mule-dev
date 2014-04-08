#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


ProbabilisticBlackBoxModelChecker::ProbabilisticBlackBoxModelChecker(const AbstractSyntaxTree &abstractSyntaxTree)
                                             : ModelChecker(abstractSyntaxTree) {
    initialise();
}

ProbabilisticBlackBoxModelChecker::~ProbabilisticBlackBoxModelChecker() {}

bool ProbabilisticBlackBoxModelChecker::acceptsMoreTraces() {
    return true;
}

bool ProbabilisticBlackBoxModelChecker::requiresMoreTraces() {
    return false;
}

bool ProbabilisticBlackBoxModelChecker::doesPropertyHold() {
    double probability = computeProbabilityThatPropertyHolds();

    return (ComparatorEvaluator::evaluate(probability, abstractSyntaxTree.getComparator(),
                                          abstractSyntaxTree.getProbability()));
}

std::string ProbabilisticBlackBoxModelChecker::getDetailedResults() {
    return (
        PROPERTY_HOLDS_WITH_PROBABILITY_LABEL +
        resultToString()
    );
}

void ProbabilisticBlackBoxModelChecker::updateModelCheckerForTrueEvaluation() {
    totalNumberOfTrueEvaluations++;
    totalNumberOfEvaluations++;
}

void ProbabilisticBlackBoxModelChecker::updateModelCheckerForFalseEvaluation() {
    totalNumberOfEvaluations++;
}

void ProbabilisticBlackBoxModelChecker::initialise() {
    totalNumberOfEvaluations     = 0;
    totalNumberOfTrueEvaluations = 0;
}

std::string ProbabilisticBlackBoxModelChecker::resultToString() {
    double probability = computeProbabilityThatPropertyHolds();

    return StringManipulator::toString(probability);
}

double ProbabilisticBlackBoxModelChecker::computeProbabilityThatPropertyHolds() {
    if (totalNumberOfEvaluations != 0) {
        return (static_cast<double>(totalNumberOfTrueEvaluations) /
                totalNumberOfEvaluations);
    } else {
        return 0;
    }
}


// Constants
const std::string ProbabilisticBlackBoxModelChecker::PROPERTY_HOLDS_WITH_PROBABILITY_LABEL  = "The probability for the logic property to hold given the spatial-temporal traces is: ";
