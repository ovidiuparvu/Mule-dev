#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/StatisticalModelChecker.hpp"

#include <limits>

using namespace multiscale;
using namespace multiscale::verification;


StatisticalModelChecker::StatisticalModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                                 const MultiscaleArchitectureGraph &multiscaleArchitectureGraph,
                                                 double typeIError, double typeIIError)
                                                 : ModelChecker(
                                                     abstractSyntaxTree,
                                                     multiscaleArchitectureGraph
                                                 ) {
    validateTypesErrors(typeIError, typeIIError);

    this->typeIError    = typeIError;
    this->typeIIError   = typeIIError;

    this->minTypesError = std::min(typeIError, typeIIError);

    initialize();
}

StatisticalModelChecker::~StatisticalModelChecker() {}

bool StatisticalModelChecker::acceptsMoreTraces() {
    updateModelCheckingResult();

    return (modelCheckingResult == StatisticalModelCheckingResult::MORE_TRACES_REQUIRED);
}

bool StatisticalModelChecker::requiresMoreTraces() {
    return acceptsMoreTraces();
}

bool StatisticalModelChecker::doesPropertyHold() {
    updateModelCheckingResult();

    return doesPropertyHoldConsideringResult();
}

std::string StatisticalModelChecker::getDetailedResults() {
    updateModelCheckingResult();

    return getDetailedUpdatedResults();
}

void StatisticalModelChecker::updateDerivedModelCheckerForTrueEvaluation()  {}

void StatisticalModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}

void StatisticalModelChecker::validateTypesErrors(double typeIError, double typeIIError) {
    if (!((isValidTypeError(typeIError)) && (isValidTypeError(typeIIError)))) {
        MS_throw(
            InvalidInputException,
            ERR_TYPES_ERROR_VALUES_BEGIN  + StringManipulator::toString(typeIError)  +
            ERR_TYPES_ERROR_VALUES_MIDDLE + StringManipulator::toString(typeIIError) +
            ERR_TYPES_ERROR_VALUES_END
        );
    }
}

void StatisticalModelChecker::initialize() {
    probability              = abstractSyntaxTree.getProbability();
    indifferenceIntervalHalf = computeIndifferenceIntervalHalf(probability);

    a1FromPaper = std::log((1 - minTypesError) / (typeIError));
    b1FromPaper = std::log((minTypesError) / (1 - typeIError));
    a2FromPaper = std::log((1 - typeIIError) / (minTypesError));
    b2FromPaper = std::log((typeIIError) / (1 - minTypesError));
}

double StatisticalModelChecker::computeIndifferenceIntervalHalf(double probability) {
    double kTerm = static_cast<double>(INDIFFERENCE_INTERVAL_HALF_K - 1) /
                   static_cast<double>(INDIFFERENCE_INTERVAL_HALF_K);

    return (kTerm * std::min(probability, 1 - probability));
}

bool StatisticalModelChecker::isValidTypeError(double typeError) {
    return (
        (typeError > 0) &&
        (typeError < 1)
    );
}

void StatisticalModelChecker::updateModelCheckingResult() {
    modelCheckingResult = StatisticalModelCheckingResult::UNDECIDED;

    while (modelCheckingResult == StatisticalModelCheckingResult::UNDECIDED) {
        updateInitializedModelCheckingResult();
    }
}

void StatisticalModelChecker::updateInitializedModelCheckingResult() {
    double f        = computeFValue();
    double fPrime   = computeFPrimeValue();

    updateModelCheckingResult(f, fPrime);
}

void StatisticalModelChecker::updateModelCheckingResult(double f, double fPrime) {
    if (
        !(
            ((b1FromPaper < f)      && (f < a1FromPaper)     ) ||
            ((b2FromPaper < fPrime) && (fPrime < a2FromPaper))
        )
    ) {
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

double StatisticalModelChecker::computeFValue() {
    double fFirstTerm   = computeFValueFirstTerm();
    double fSecondTerm  = computeFValueSecondTerm();

    return (
        (totalNumberOfTrueEvaluations * fFirstTerm) +
        ((totalNumberOfEvaluations - totalNumberOfTrueEvaluations) * fSecondTerm)
    );
}

double StatisticalModelChecker::computeFValueFirstTerm() {
    if ((Numeric::almostEqual(probability - indifferenceIntervalHalf, 0)) ||
        (Numeric::almostEqual(probability, 0))) {
        return LOGARITHM_ZERO_VALUE;
    } else {
        return std::log((probability - indifferenceIntervalHalf) / (probability));
    }
}

double StatisticalModelChecker::computeFValueSecondTerm() {
    if ((Numeric::almostEqual(probability - indifferenceIntervalHalf, 1)) ||
        (Numeric::almostEqual(probability, 1))) {
        return LOGARITHM_ZERO_VALUE;
    } else {
        return std::log((1 - (probability - indifferenceIntervalHalf)) / (1 - probability));
    }
}

double StatisticalModelChecker::computeFPrimeValue() {
    double fPrimeFirstTerm  = computeFPrimeValueFirstTerm();
    double fPrimeSecondTerm = computeFPrimeValueSecondTerm();

    return (
        (totalNumberOfTrueEvaluations * fPrimeFirstTerm) +
        ((totalNumberOfEvaluations - totalNumberOfTrueEvaluations) * fPrimeSecondTerm)
    );
}

double StatisticalModelChecker::computeFPrimeValueFirstTerm() {
    if ((Numeric::almostEqual(probability, 0)) ||
        (Numeric::almostEqual(probability + indifferenceIntervalHalf, 0))) {
        return LOGARITHM_ZERO_VALUE;
    } else {
        return std::log((probability) / (probability + indifferenceIntervalHalf));
    }
}

double StatisticalModelChecker::computeFPrimeValueSecondTerm() {
    if ((Numeric::almostEqual(probability, 1)) ||
        (Numeric::almostEqual(probability + indifferenceIntervalHalf, 1))) {
        return LOGARITHM_ZERO_VALUE;
    } else {
        return std::log((1 - probability) / (1 - (probability + indifferenceIntervalHalf)));
    }
}

bool StatisticalModelChecker::doesPropertyHoldConsideringResult() {
    switch (modelCheckingResult) {
        case StatisticalModelCheckingResult::TRUE:
            return doesPropertyHoldConsideringProbabilityComparator(true);

        case StatisticalModelCheckingResult::FALSE:
            return doesPropertyHoldConsideringProbabilityComparator(false);

        case StatisticalModelCheckingResult::MORE_TRACES_REQUIRED:
            return doesPropertyHoldUsingPValues();

        default:
            MS_throw(UnexpectedBehaviourException, ERR_UNEXPECTED_MODEL_CHECKING_RESULT);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return false;
}

bool StatisticalModelChecker::doesPropertyHoldConsideringProbabilityComparator(bool isNullHypothesisTrue) {
    if (isGreaterThanOrEqualToComparator()) {
        return isNullHypothesisTrue;
    } else {
        return (!isNullHypothesisTrue);
    }
}

std::string StatisticalModelChecker::getDetailedUpdatedResults() {
    if (modelCheckingResult == StatisticalModelCheckingResult::MORE_TRACES_REQUIRED) {
        return (MSG_OUTPUT_MORE_TRACES_REQUIRED + MSG_OUTPUT_SEPARATOR +
                getDetailedResultsUsingPValues());
    } else {
        return (
            MSG_OUTPUT_RESULT_BEGIN  + StringManipulator::toString(typeIError)  +
            MSG_OUTPUT_RESULT_MIDDLE + StringManipulator::toString(typeIIError) +
            MSG_OUTPUT_RESULT_END
        );
    }
}


// Constants
const std::string  StatisticalModelChecker::ERR_UNEXPECTED_MODEL_CHECKING_RESULT = "An invalid statistical model checking result was obtained. Please check source code.";

const std::string  StatisticalModelChecker::ERR_TYPES_ERROR_VALUES_BEGIN     = "The provided probabilities of type I and type II errors (";
const std::string  StatisticalModelChecker::ERR_TYPES_ERROR_VALUES_MIDDLE    = ", ";
const std::string  StatisticalModelChecker::ERR_TYPES_ERROR_VALUES_END       = ") should be greater than zero and less or equal to 1. Please change.";

const std::string  StatisticalModelChecker::MSG_OUTPUT_MORE_TRACES_REQUIRED = "More traces are required to provide a true/false answer assuming the given probabilities of type I and type II errors. Probabilistic black-box model checking was used instead to provide an answer.";

const std::string  StatisticalModelChecker::MSG_OUTPUT_RESULT_BEGIN  = "The provided answer is given for the probability of type I errors = ";
const std::string  StatisticalModelChecker::MSG_OUTPUT_RESULT_MIDDLE = " and the probability of type II errors = ";
const std::string  StatisticalModelChecker::MSG_OUTPUT_RESULT_END    = "";

const std::string  StatisticalModelChecker::MSG_OUTPUT_SEPARATOR     = " ";

//! The value of this constant should be much greater than 1
const unsigned int StatisticalModelChecker::INDIFFERENCE_INTERVAL_HALF_K = (std::numeric_limits<unsigned int>::max() >> 1);

//! The value of this constant should be a large negative number.
/*! This value will be further multiplied by non-negative integer numbers.
 *  In order to avoid overflow the lowest double value is divided by 1E10.
 */
const double       StatisticalModelChecker::LOGARITHM_ZERO_VALUE = (std::numeric_limits<double>::lowest() / 1E+10);
