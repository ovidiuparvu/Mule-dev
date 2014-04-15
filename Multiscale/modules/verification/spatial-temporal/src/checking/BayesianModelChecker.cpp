#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/BayesianModelChecker.hpp"

#include <limits>

using namespace multiscale;
using namespace multiscale::verification;


BayesianModelChecker::BayesianModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                           double alpha, double beta, double bayesFactorThreshold)
                                           : ModelChecker(abstractSyntaxTree) {
    validateShapeParameters(alpha, beta);

    this->alpha = alpha;
    this->beta  = beta;
    this->bayesFactorThreshold = bayesFactorThreshold;

    initialise();
}

BayesianModelChecker::~BayesianModelChecker() {}

bool BayesianModelChecker::acceptsMoreTraces() {
    updateModelCheckingResult();

    return (modelCheckingResult == BayesianModelCheckingResult::MORE_TRACES_REQUIRED);
}

bool BayesianModelChecker::requiresMoreTraces() {
    return acceptsMoreTraces();
}

bool BayesianModelChecker::doesPropertyHold() {
    switch (modelCheckingResult) {
        case BayesianModelCheckingResult::TRUE:
            return doesPropertyHoldConsideringProbabilityComparator(true);

        case BayesianModelCheckingResult::FALSE:
            return doesPropertyHoldConsideringProbabilityComparator(false);

        case BayesianModelCheckingResult::MORE_TRACES_REQUIRED:
            return doesPropertyHoldUsingPValues();

        default:
            MS_throw(UnexpectedBehaviourException, ERR_UNEXPECTED_MODEL_CHECKING_RESULT);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return false;
}

std::string BayesianModelChecker::getDetailedResults() {
    if (modelCheckingResult == BayesianModelCheckingResult::MORE_TRACES_REQUIRED) {
        return (MSG_OUTPUT_MORE_TRACES_REQUIRED + MSG_OUTPUT_SEPARATOR +
                getDetailedResultsUsingPValues());
    } else {
        return (
            MSG_OUTPUT_RESULT_BEGIN     + StringManipulator::toString(alpha)  +
            MSG_OUTPUT_RESULT_MIDDLE1   + StringManipulator::toString(beta) +
            MSG_OUTPUT_RESULT_MIDDLE2   + StringManipulator::toString(bayesFactorThreshold) +
            MSG_OUTPUT_RESULT_END
        );
    }
}

void BayesianModelChecker::updateDerivedModelCheckerForTrueEvaluation()  {}

void BayesianModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}

void BayesianModelChecker::validateShapeParameters(double alpha, double beta) {
    if (!((isValidShapeParameter(alpha)) && (isValidShapeParameter(beta)))) {
        MS_throw(
            InvalidInputException,
            ERR_SHAPE_PARAMETERS_BEGIN  + StringManipulator::toString(alpha)  +
            ERR_SHAPE_PARAMETERS_MIDDLE + StringManipulator::toString(beta) +
            ERR_SHAPE_PARAMETERS_END
        );
    }
}

bool BayesianModelChecker::isValidShapeParameter(double shapeParameter) {
    return (shapeParameter > 0);
}

void BayesianModelChecker::initialise() {
    probability = abstractSyntaxTree.getProbability();

    bayesFactorThresholdInverse = (bayesFactorThreshold == 0)
                                      ? (std::numeric_limits<double>::max())
                                      : (1 / bayesFactorThreshold);
}

void BayesianModelChecker::updateModelCheckingResult() {
    modelCheckingResult = StatisticalModelCheckingResult::UNDECIDED;

    updateInitialisedModelCheckingResult();
}

void BayesianModelChecker::updateInitialisedModelCheckingResult() {
    double bayesFactor = computeBayesFactorValue();

    updateModelCheckingResult(bayesFactor);
}

void BayesianModelChecker::updateModelCheckingResult(double bayesFactor) {
    // TODO: Update implementation
    if ((bayesFactor > bayesFactorThreshold) ||
        (bayesFactor < bayesFactorThresholdInverse))) {
        updateModelCheckingResultEnoughTraces(f, fPrime);
    } else {
        updateModelCheckingResultNotEnoughTraces();
    }
}

void StatisticalModelChecker::updateModelCheckingResultEnoughTraces(double f, double fPrime) {
    if ((f < b1FromPaper) && (fPrime < b2FromPaper)) {
        modelCheckingResult = StatisticalModelCheckingResult::TRUE;
    } else if ((f > a1FromPaper) && (fPrime > a2FromPaper)) {
        modelCheckingResult = StatisticalModelCheckingResult::FALSE;
    } else {
        modelCheckingResult = StatisticalModelCheckingResult::UNDECIDED;

        indifferenceIntervalHalf /= 2;
    }
}

void StatisticalModelChecker::updateModelCheckingResultNotEnoughTraces() {
    modelCheckingResult = StatisticalModelCheckingResult::MORE_TRACES_REQUIRED;
}

double BayesianModelChecker::computeBayesFactorValue() {
    // TODO: Implement
}

bool BayesianModelChecker::doesPropertyHoldConsideringProbabilityComparator(bool isNullHypothesisTrue) {
    if (isGreaterThanOrEqualToComparator()) {
        return isNullHypothesisTrue;
    } else {
        return (!isNullHypothesisTrue);
    }
}


// Constants
const std::string BayesianModelChecker::ERR_UNEXPECTED_MODEL_CHECKING_RESULT = "An invalid Bayesian model checking result was obtained. Please check source code.";

const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_BEGIN  = "The provided beta distribution shape parameters alpha and beta (";
const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_MIDDLE = ", ";
const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_END    = ") should be greater than zero. Please change.";

const std::string BayesianModelChecker::MSG_OUTPUT_MORE_TRACES_REQUIRED = "More traces are required to provide a true/false answer assuming the given beta distribution shape parameters and Bayes factor threshold value. Probabilistic black-box model checking was used instead to provide an answer.";

const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_BEGIN     = "The provided answer is given for the beta distribution shape parameters alpha = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE1   = " and beta = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE2   = ", and Bayes factor threshold value = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_END       = "";

const std::string BayesianModelChecker::MSG_OUTPUT_SEPARATOR     = " ";
