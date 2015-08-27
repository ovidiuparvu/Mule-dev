#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelChecker.hpp"

using namespace multiscale;
using namespace multiscale::verification;


ApproximateBayesianModelChecker::ApproximateBayesianModelChecker(
    const AbstractSyntaxTree &abstractSyntaxTree,
    const MultiscaleArchitectureGraph &multiscaleArchitectureGraph,
    double alpha, double beta, double varianceThreshold
) : ModelChecker(abstractSyntaxTree, multiscaleArchitectureGraph) {
    validateInput(alpha, beta, varianceThreshold);

    this->alpha                 = alpha;
    this->beta                  = beta;
    this->varianceThreshold     = varianceThreshold;

    initialize();
}

ApproximateBayesianModelChecker::~ApproximateBayesianModelChecker() {}

bool ApproximateBayesianModelChecker::acceptsMoreTraces() {
    updateModelCheckingResult();

    return (modelCheckingResult == ApproximateBayesianModelCheckingResult::MORE_TRACES_REQUIRED);
}

bool ApproximateBayesianModelChecker::requiresMoreTraces() {
    return acceptsMoreTraces();
}

bool ApproximateBayesianModelChecker::doesPropertyHold() {
    updateModelCheckingResult();

    return doesPropertyHoldConsideringResult();
}

std::string ApproximateBayesianModelChecker::getDetailedResults() {
    updateModelCheckingResult();

    return getDetailedUpdatedResults();
}

void ApproximateBayesianModelChecker::updateDerivedModelCheckerForTrueEvaluation()  {}

void ApproximateBayesianModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}

void ApproximateBayesianModelChecker::validateInput(double alpha, double beta, double varianceThreshold) {
    validateShapeParameters(alpha, beta);
    validateVarianceThreshold(varianceThreshold);
}

void ApproximateBayesianModelChecker::validateShapeParameters(double alpha, double beta) {
    if (!((isValidShapeParameter(alpha)) && (isValidShapeParameter(beta)))) {
        MS_throw(
            InvalidInputException,
            ERR_SHAPE_PARAMETERS_BEGIN  + StringManipulator::toString(alpha)  +
            ERR_SHAPE_PARAMETERS_MIDDLE + StringManipulator::toString(beta) +
            ERR_SHAPE_PARAMETERS_END
        );
    }
}

bool ApproximateBayesianModelChecker::isValidShapeParameter(double shapeParameter) {
    return (shapeParameter > 0);
}

void ApproximateBayesianModelChecker::validateVarianceThreshold(double varianceThreshold) {
    if (Numeric::lessOrEqual(varianceThreshold, 0)) {
        MS_throw(
            InvalidInputException,
            ERR_VARIANCE_THRESHOLD_BEGIN +
            StringManipulator::toString(varianceThreshold) +
            ERR_VARIANCE_THRESHOLD_END
        );
    }
}

void ApproximateBayesianModelChecker::initialize() {
    probability = abstractSyntaxTree.getProbability();

    mean        = 0;
    variance    = 0;
}

void ApproximateBayesianModelChecker::updateModelCheckingResult() {
    updateMeanAndVariance();
    updateModelCheckingResult(variance);
}

void ApproximateBayesianModelChecker::updateMeanAndVariance() {
    updateMean();
    updateVariance();
}

void ApproximateBayesianModelChecker::updateMean() {
    double nominator    = static_cast<double>(totalNumberOfTrueEvaluations) + alpha;
    double denominator  = alpha + beta + static_cast<double>(totalNumberOfEvaluations);

    mean = Numeric::division(nominator, denominator);
}

void ApproximateBayesianModelChecker::updateVariance() {
    double nominator    = (alpha + static_cast<double>(totalNumberOfTrueEvaluations)) *
                          (static_cast<double>(totalNumberOfEvaluations - totalNumberOfTrueEvaluations) + beta);
    double denominator  = std::pow((alpha + static_cast<double>(totalNumberOfEvaluations) + beta), 2) *
                          (alpha + static_cast<double>(totalNumberOfEvaluations) + beta + 1);

    variance = Numeric::division(nominator, denominator);
}

void ApproximateBayesianModelChecker::updateModelCheckingResult(double variance) {
    if (variance < varianceThreshold) {
        updateModelCheckingResultEnoughTraces(variance);
    } else {
        updateModelCheckingResultNotEnoughTraces();
    }
}

void ApproximateBayesianModelChecker::updateModelCheckingResultEnoughTraces(double variance) {
    if (isModelCheckingResultTrueConsideringComparator(variance)) {
        modelCheckingResult = ApproximateBayesianModelCheckingResult::TRUE;
    } else {
        modelCheckingResult = ApproximateBayesianModelCheckingResult::FALSE;
    }
}

bool ApproximateBayesianModelChecker::isModelCheckingResultTrueConsideringComparator(double variance) {
    if (isGreaterThanOrEqualToComparator()) {
        return (Numeric::greaterOrEqual(mean, probability));
    } else {
        return (Numeric::lessOrEqual(mean, probability));
    }
}

void ApproximateBayesianModelChecker::updateModelCheckingResultNotEnoughTraces() {
    modelCheckingResult = ApproximateBayesianModelCheckingResult::MORE_TRACES_REQUIRED;
}

bool ApproximateBayesianModelChecker::doesPropertyHoldConsideringResult() {
    switch (modelCheckingResult) {
        case ApproximateBayesianModelCheckingResult::TRUE:
            return true;

        case ApproximateBayesianModelCheckingResult::FALSE:
            return false;

        case ApproximateBayesianModelCheckingResult::MORE_TRACES_REQUIRED:
            return doesPropertyHoldUsingPValues();

        default:
            MS_throw(UnexpectedBehaviourException, ERR_UNEXPECTED_MODEL_CHECKING_RESULT);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return false;
}

std::string ApproximateBayesianModelChecker::getDetailedUpdatedResults() {
    if (modelCheckingResult == ApproximateBayesianModelCheckingResult::MORE_TRACES_REQUIRED) {
        return (MSG_OUTPUT_MORE_TRACES_REQUIRED + MSG_OUTPUT_SEPARATOR +
                getDetailedResultsUsingPValues());
    } else {
        return (
            MSG_OUTPUT_RESULT_BEGIN     + StringManipulator::toString(alpha)  +
            MSG_OUTPUT_RESULT_MIDDLE1   + StringManipulator::toString(beta) +
            MSG_OUTPUT_RESULT_MIDDLE2   + StringManipulator::toString(varianceThreshold) +
            MSG_OUTPUT_RESULT_END
        );
    }
}


// Constants
const std::string ApproximateBayesianModelChecker::ERR_UNEXPECTED_MODEL_CHECKING_RESULT     = "An invalid ApproximateBayesian model checking result was obtained. Please check source code.";

const std::string ApproximateBayesianModelChecker::ERR_SHAPE_PARAMETERS_BEGIN               = "The provided Beta distribution shape parameters alpha and beta (";
const std::string ApproximateBayesianModelChecker::ERR_SHAPE_PARAMETERS_MIDDLE              = ", ";
const std::string ApproximateBayesianModelChecker::ERR_SHAPE_PARAMETERS_END                 = ") should be greater than zero. Please change.";

const std::string ApproximateBayesianModelChecker::ERR_VARIANCE_THRESHOLD_BEGIN             = "The provided variance threshold (";
const std::string ApproximateBayesianModelChecker::ERR_VARIANCE_THRESHOLD_END               = ") should be greater than zero. Please change.";

const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_MORE_TRACES_REQUIRED          = "More traces are required to provide a true/false answer assuming the given Beta distribution shape parameters and variance threshold value. Probabilistic black-box model checking was used instead to provide an answer.";

const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_RESULT_BEGIN                  = "The provided answer is given for the Beta distribution shape parameters alpha = ";
const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE1                = " and beta = ";
const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE2                = ", and variance threshold value = ";
const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_RESULT_END                    = "";

const std::string ApproximateBayesianModelChecker::MSG_OUTPUT_SEPARATOR                     = " ";
