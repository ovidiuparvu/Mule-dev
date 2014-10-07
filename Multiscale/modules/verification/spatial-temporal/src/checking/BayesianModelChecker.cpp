#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/BetaDistribution.hpp"
#include "multiscale/util/statistics/BinomialDistribution.hpp"
#include "multiscale/verification/spatial-temporal/checking/BayesianModelChecker.hpp"

#include <limits>

using namespace multiscale;
using namespace multiscale::verification;


BayesianModelChecker::BayesianModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                           const TypeSemanticsTable &typeSemanticsTable,
                                           double alpha, double beta, double bayesFactorThreshold)
                                           : ModelChecker(abstractSyntaxTree, typeSemanticsTable) {
    validateInput(alpha, beta, bayesFactorThreshold);

    this->alpha                 = alpha;
    this->beta                  = beta;
    this->bayesFactorThreshold  = bayesFactorThreshold;

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
    updateModelCheckingResult();

    return doesPropertyHoldConsideringResult();
}

std::string BayesianModelChecker::getDetailedResults() {
    updateModelCheckingResult();

    return getDetailedUpdatedResults();
}

void BayesianModelChecker::updateDerivedModelCheckerForTrueEvaluation()  {}

void BayesianModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}

void BayesianModelChecker::validateInput(double alpha, double beta, double bayesFactorThreshold) {
    validateShapeParameters(alpha, beta);
    validateBayesFactorThreshold(bayesFactorThreshold);
}

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

void BayesianModelChecker::validateBayesFactorThreshold(double bayesFactorThreshold) {
    if (Numeric::lessOrEqual(bayesFactorThreshold, 1)) {
        MS_throw(
            InvalidInputException,
            ERR_BAYES_FACTOR_THRESHOLD_BEGIN +
            StringManipulator::toString(bayesFactorThreshold) +
            ERR_BAYES_FACTOR_THRESHOLD_END
        );
    }
}

void BayesianModelChecker::initialise() {
    probability             = abstractSyntaxTree.getProbability();
    typeIErrorUpperBound    = 0;

    // Since the Bayes factor threshold should be greater than 1 the conditional statement is not mandatory
    bayesFactorThresholdInverse = (Numeric::almostEqual(bayesFactorThreshold, 0))
                                      ? (std::numeric_limits<double>::max())
                                      : (1 / bayesFactorThreshold);
}

void BayesianModelChecker::updateModelCheckingResult() {
    double bayesFactor = computeBayesFactorValue(totalNumberOfEvaluations,
                                                 totalNumberOfTrueEvaluations);

    updateModelCheckingResult(bayesFactor);
    updateTypeIErrorUpperBound();
}

void BayesianModelChecker::updateModelCheckingResult(double bayesFactor) {
    if ((bayesFactor > bayesFactorThreshold) ||
        (bayesFactor < bayesFactorThresholdInverse)) {
        updateModelCheckingResultEnoughTraces(bayesFactor);
    } else {
        updateModelCheckingResultNotEnoughTraces();
    }
}

void BayesianModelChecker::updateModelCheckingResultEnoughTraces(double bayesFactor) {
    if (bayesFactor > bayesFactorThreshold) {
        modelCheckingResult = BayesianModelCheckingResult::TRUE;
    } else if (bayesFactor < bayesFactorThresholdInverse) {
        modelCheckingResult = BayesianModelCheckingResult::FALSE;
    }
}

void BayesianModelChecker::updateModelCheckingResultNotEnoughTraces() {
    modelCheckingResult = BayesianModelCheckingResult::MORE_TRACES_REQUIRED;
}

void BayesianModelChecker::updateTypeIErrorUpperBound() {
    typeIErrorUpperBound = 0;

    for (unsigned int i = 0; i < totalNumberOfEvaluations; i++) {
        if (indicatorFunction(i)) {
            typeIErrorUpperBound += computeMaximumBinomialPDF(i);
        }
    }
}

bool BayesianModelChecker::indicatorFunction(unsigned int nrOfSuccesses) {
    double bayesFactor = computeBayesFactorValue(totalNumberOfEvaluations, nrOfSuccesses);

    return (bayesFactor < bayesFactorThresholdInverse);
}

double BayesianModelChecker::computeMaximumBinomialPDF(unsigned int nrOfSuccesses) {
    double firstBinomialPDF  = computeBinomialPDF(nrOfSuccesses, probability);

    double secondProbability = static_cast<double>(2 * nrOfSuccesses) /
                               static_cast<double>(totalNumberOfEvaluations);
    double secondBinomialPDF = computeBinomialPDF(nrOfSuccesses, secondProbability);

    return std::max(firstBinomialPDF, secondBinomialPDF);
}

double BayesianModelChecker::computeBinomialPDF(unsigned int nrOfSuccesses, double probability) {
    return ((probability < (this->probability)) || (probability > 1))
        ? 0.0
        : BinomialDistribution::pdf(totalNumberOfEvaluations, nrOfSuccesses, probability);
}

double BayesianModelChecker::computeBayesFactorValue(unsigned int nrOfObservations,
                                                     unsigned int nrOfSuccesses) {
    double alphaShapeParameter  = static_cast<double>(nrOfSuccesses) + alpha;
    double betaShapeParameter   = static_cast<double>(nrOfObservations - nrOfSuccesses) + beta;

    double cdfValue     = BetaDistribution::cdf(alphaShapeParameter, betaShapeParameter, probability);
    double cdfInverse   = (Numeric::almostEqual(cdfValue, 0)) ? std::numeric_limits<double>::max()
                                                              : (1 / cdfValue);

    return (cdfInverse - 1);
}

bool BayesianModelChecker::doesPropertyHoldConsideringResult() {
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

bool BayesianModelChecker::doesPropertyHoldConsideringProbabilityComparator(bool isNullHypothesisTrue) {
    if (isGreaterThanOrEqualToComparator()) {
        return isNullHypothesisTrue;
    } else {
        return (!isNullHypothesisTrue);
    }
}

std::string BayesianModelChecker::getDetailedUpdatedResults() {
    if (modelCheckingResult == BayesianModelCheckingResult::MORE_TRACES_REQUIRED) {
        return (MSG_OUTPUT_MORE_TRACES_REQUIRED + MSG_OUTPUT_SEPARATOR +
                getDetailedResultsUsingPValues());
    } else {
        return (
            MSG_OUTPUT_RESULT_BEGIN     + StringManipulator::toString(alpha)  +
            MSG_OUTPUT_RESULT_MIDDLE1   + StringManipulator::toString(beta) +
            MSG_OUTPUT_RESULT_MIDDLE2   + StringManipulator::toString(bayesFactorThreshold) +
            MSG_OUTPUT_RESULT_MIDDLE3   + StringManipulator::toString(typeIErrorUpperBound) +
            MSG_OUTPUT_RESULT_END
        );
    }
}


// Constants
const std::string BayesianModelChecker::ERR_UNEXPECTED_MODEL_CHECKING_RESULT    = "An invalid Bayesian model checking result was obtained. Please check source code.";

const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_BEGIN              = "The provided Beta distribution shape parameters alpha and beta (";
const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_MIDDLE             = ", ";
const std::string BayesianModelChecker::ERR_SHAPE_PARAMETERS_END                = ") should be greater than zero. Please change.";

const std::string BayesianModelChecker::ERR_BAYES_FACTOR_THRESHOLD_BEGIN        = "The provided Bayes factor threshold (";
const std::string BayesianModelChecker::ERR_BAYES_FACTOR_THRESHOLD_END          = ") should be greater than one. Please change.";

const std::string BayesianModelChecker::MSG_OUTPUT_MORE_TRACES_REQUIRED         = "More traces are required to provide a true/false answer assuming the given Beta distribution shape parameters and Bayes factor threshold value. Probabilistic black-box model checking was used instead to provide an answer.";

const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_BEGIN                 = "The provided answer is given for the Beta distribution shape parameters alpha = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE1               = " and beta = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE2               = ", and Bayes factor threshold value = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_MIDDLE3               = ". The type I error upper bound for the provided answer is = ";
const std::string BayesianModelChecker::MSG_OUTPUT_RESULT_END                   = "";

const std::string BayesianModelChecker::MSG_OUTPUT_SEPARATOR                    = " ";
