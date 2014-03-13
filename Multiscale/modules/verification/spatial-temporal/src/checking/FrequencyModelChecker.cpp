#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelChecker.hpp"

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

    return (Numeric::greaterOrEqual(probability, THRESH_PROBABILITY_THAT_PROPERTY_HOLDS));
}

void FrequencyModelChecker::getDetailedResults() {
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
    else {
        return 0;
    }
}


// Constants
const std::string FrequencyModelChecker::PROPERTY_HOLDS_WITH_PROBABILITY_LABEL  = "The logic property holds with probability: ";
const double      FrequencyModelChecker::THRESH_PROBABILITY_THAT_PROPERTY_HOLDS = 0.5;
