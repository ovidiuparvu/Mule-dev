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

bool AbstractSyntaxTree::evaluate(const SpatialTemporalTrace &spatialTemporalTrace) {
    if (!isInitialised) {

    }
    // TODO: Replace the below line with return abstractSyntaxTree.evaluate(spatialTemporalTrace);
    return true;
}


// Constants
const std::string ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALISED = "The abstract syntax tree was not initialised before evaluation. Call the method initialiseTree(...) before calling the method evaluate(...).";
