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

void FrequencyModelChecker::outputResults() {
    std::cout << resultToString() << std::endl;
}

void FrequencyModelChecker::initialise() {
    totalNumberOfEvaluations     = 0;
    totalNumberOfTrueEvaluations = 0;
}

std::string FrequencyModelChecker::resultToString() {
    double result = (totalNumberOfEvaluations !== 0)
                        ? (static_cast<double>(totalNumberOfTrueEvaluations) /
                           totalNumberOfEvaluations)
                        : 0;

    return StringManipulator::toString(result);
}
