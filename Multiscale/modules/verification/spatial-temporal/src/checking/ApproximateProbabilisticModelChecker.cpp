#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateProbabilisticModelChecker.hpp"

using namespace multiscale;
using namespace multiscale::verification;


ApproximateProbabilisticModelChecker::ApproximateProbabilisticModelChecker(const AbstractSyntaxTree
                                                                           &abstractSyntaxTree,
                                                                           const TypeSemanticsTable
                                                                           &typeSemanticsTable,
                                                                           double delta, double epsilon)
                                                                           : ModelChecker(
                                                                                 abstractSyntaxTree,
                                                                                 typeSemanticsTable
                                                                             ) {
    validateInput(delta, epsilon);

    this->delta     = delta;
    this->epsilon   = epsilon;

    initialise();
}

ApproximateProbabilisticModelChecker::~ApproximateProbabilisticModelChecker() {}

bool ApproximateProbabilisticModelChecker::acceptsMoreTraces() {
    return (totalNumberOfEvaluations < nrOfRequiredTraces);
}

bool ApproximateProbabilisticModelChecker::requiresMoreTraces() {
    return acceptsMoreTraces();
}

bool ApproximateProbabilisticModelChecker::doesPropertyHold() {
    if (requiresMoreTraces()) {
        return doesPropertyHoldUsingPValues();
    } else {
        return doesPropertyHoldConsideringProbabilityComparator();
    }
}

std::string ApproximateProbabilisticModelChecker::getDetailedResults() {
    if (requiresMoreTraces()) {
        return (
            MSG_OUTPUT_MORE_TRACES_REQUIRED + MSG_OUTPUT_SEPARATOR +
            getDetailedResultsUsingPValues()
        );
    } else {
        return (
            MSG_OUTPUT_RESULT_BEGIN     + StringManipulator::toString(epsilon) +
            MSG_OUTPUT_RESULT_MIDDLE1   + StringManipulator::toString(delta) +
            MSG_OUTPUT_RESULT_MIDDLE2   + StringManipulator::toString(nrOfRequiredTraces) +
            MSG_OUTPUT_RESULT_END
        );
    }
}

void ApproximateProbabilisticModelChecker::updateDerivedModelCheckerForTrueEvaluation() {}

void ApproximateProbabilisticModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}

void ApproximateProbabilisticModelChecker::validateInput(double delta, double epsilon) {
    if (!(isBetweenZeroAndOne(delta) && isBetweenZeroAndOne(epsilon))) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_INPUT_BEGIN     + StringManipulator::toString(delta)    +
            ERR_INVALID_INPUT_MIDDLE    + StringManipulator::toString(epsilon)  +
            ERR_INVALID_INPUT_END
        );
    }
}

bool ApproximateProbabilisticModelChecker::isBetweenZeroAndOne(double value) {
    return ((0 < value) && (value < 1));
}

void ApproximateProbabilisticModelChecker::initialise() {
    probability = abstractSyntaxTree.getProbability();

    initialiseNumberOfRequiredTraces();
}

void ApproximateProbabilisticModelChecker::initialiseNumberOfRequiredTraces() {
    double firstTerm    = (4 / (epsilon * epsilon));
    double secondTerm   = std::log(2 / delta);

    nrOfRequiredTraces = static_cast<unsigned int>(std::ceil(firstTerm * secondTerm));
}

bool ApproximateProbabilisticModelChecker::doesPropertyHoldConsideringProbabilityComparator() {
    double computedProbability = (static_cast<double>(totalNumberOfTrueEvaluations) /
                                  static_cast<double>(totalNumberOfEvaluations));

    if (isGreaterThanOrEqualToComparator()) {
        return (Numeric::greaterOrEqual((computedProbability - epsilon), probability));
    } else {
        return (Numeric::lessOrEqual((computedProbability + epsilon), probability));
    }
}


// Constants
const std::string ApproximateProbabilisticModelChecker::ERR_INVALID_INPUT_BEGIN         = "The values of the provided input parameters delta and epsilon (";
const std::string ApproximateProbabilisticModelChecker::ERR_INVALID_INPUT_MIDDLE        = ", ";
const std::string ApproximateProbabilisticModelChecker::ERR_INVALID_INPUT_END           = ") must be between zero and one (exclusive). Please change.";

const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_MORE_TRACES_REQUIRED = "More traces are required to provide a true/false answer assuming the given upper bound on the probability of the computed probability to deviate from the true probability. Probabilistic black-box model checking was used instead to provide an answer.";

const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_RESULT_BEGIN         = "The provided answer is given assuming the upper bound on the probability to deviate more than epsilon = ";
const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_RESULT_MIDDLE1       = " from the true probability is delta = ";
const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_RESULT_MIDDLE2       = ". The number of required samples was N = ";
const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_RESULT_END           = "";

const std::string ApproximateProbabilisticModelChecker::MSG_OUTPUT_SEPARATOR            = " ";
