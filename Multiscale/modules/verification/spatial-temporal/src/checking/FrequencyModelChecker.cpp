#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


FrequencyModelChecker::FrequencyModelChecker(const AbstractSyntaxTree &abstractSyntaxTree)
                                             : ModelChecker(abstractSyntaxTree) {
    initialise();
}

FrequencyModelChecker::~FrequencyModelChecker() {}

void FrequencyModelChecker::evaluate(const SpatialTemporalTrace &trace) {
    if (abstractSyntaxTree.evaluate(trace)) {
        totalNumberOfTrueEvaluations++;
    }

    totalNumberOfEvaluations++;
}

bool FrequencyModelChecker::acceptsMoreTraces() {
    return true;
}

bool FrequencyModelChecker::requiresMoreTraces() {
    return false;
}

bool FrequencyModelChecker::doesPropertyHold() {
    double probability = computeProbabilityThatPropertyHolds();

    return (ComparatorEvaluator::evaluate(probability, abstractSyntaxTree.getComparator(),
                                          abstractSyntaxTree.getProbability()));
}

std::string FrequencyModelChecker::getDetailedResults() {
    return (
        PROPERTY_HOLDS_WITH_PROBABILITY_LABEL +
        resultToString()
    );
}

void FrequencyModelChecker::initialise() {
    totalNumberOfEvaluations     = 0;
    totalNumberOfTrueEvaluations = 0;
}

std::string FrequencyModelChecker::resultToString() {
    double probability = computeProbabilityThatPropertyHolds();

    return StringManipulator::toString(probability);
}

double FrequencyModelChecker::computeProbabilityThatPropertyHolds() {
    if (totalNumberOfEvaluations != 0) {
        return (static_cast<double>(totalNumberOfTrueEvaluations) /
                totalNumberOfEvaluations);
    } else {
        return 0;
    }
}


// Constants
const std::string FrequencyModelChecker::PROPERTY_HOLDS_WITH_PROBABILITY_LABEL  = "The probability for the logic property to hold given the spatial-temporal traces is: ";
