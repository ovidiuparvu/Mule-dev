#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


ProbabilisticBlackBoxModelChecker::ProbabilisticBlackBoxModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                                                     const TypeSemanticsTable &typeSemanticsTable)
                                                                     : ModelChecker(
                                                                           abstractSyntaxTree,
                                                                           typeSemanticsTable
                                                                       ) {}

ProbabilisticBlackBoxModelChecker::~ProbabilisticBlackBoxModelChecker() {}

bool ProbabilisticBlackBoxModelChecker::acceptsMoreTraces() {
    return true;
}

bool ProbabilisticBlackBoxModelChecker::requiresMoreTraces() {
    return false;
}

bool ProbabilisticBlackBoxModelChecker::doesPropertyHold() {
    return doesPropertyHoldUsingPValues();
}

std::string ProbabilisticBlackBoxModelChecker::getDetailedResults() {
    return getDetailedResultsUsingPValues();
}

void ProbabilisticBlackBoxModelChecker::updateDerivedModelCheckerForTrueEvaluation() {}

void ProbabilisticBlackBoxModelChecker::updateDerivedModelCheckerForFalseEvaluation() {}
