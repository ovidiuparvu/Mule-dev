#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

using namespace multiscale::verification;


AbstractSyntaxTree::AbstractSyntaxTree() {
    isInitialised = false;
}

AbstractSyntaxTree::~AbstractSyntaxTree() {}

void AbstractSyntaxTree::initialiseTree(const ProbabilisticLogicPropertyAttribute &probabilisticLogicPropertyAttribute) {
    this->probabilisticLogicProperty = probabilisticLogicPropertyAttribute;
    this->isInitialised              = true;
}

ComparatorType AbstractSyntaxTree::getComparator() {
    return probabilisticLogicProperty.getComparator();
}

double AbstractSyntaxTree::getProbability() {
    return probabilisticLogicProperty.getProbability();
}

bool AbstractSyntaxTree::evaluate(const SpatialTemporalTrace &spatialTemporalTrace,
                                  const TypeSemanticsTable &typeSemanticsTable) {
    if (!isInitialised) {
        MS_throw(UnexpectedBehaviourException, ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALISED);
    }

    return probabilisticLogicProperty.evaluate(spatialTemporalTrace, typeSemanticsTable);
}


// Constants
const std::string AbstractSyntaxTree::ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALISED = "The abstract syntax tree was not initialised before evaluation. Call the method initialiseTree(...) before calling the method evaluate(...).";
