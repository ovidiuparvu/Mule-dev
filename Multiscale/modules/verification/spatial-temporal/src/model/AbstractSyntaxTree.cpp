#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

using namespace multiscale::verification;


AbstractSyntaxTree::AbstractSyntaxTree() {
    isInitialized = false;
}

AbstractSyntaxTree::~AbstractSyntaxTree() {}

void AbstractSyntaxTree::initializeTree(const ProbabilisticLogicPropertyAttribute
                                        &probabilisticLogicPropertyAttribute) {
    this->probabilisticLogicProperty = probabilisticLogicPropertyAttribute;
    this->isInitialized              = true;
}

ComparatorType AbstractSyntaxTree::getComparator() {
    return probabilisticLogicProperty.getComparator();
}

double AbstractSyntaxTree::getProbability() {
    return probabilisticLogicProperty.getProbability();
}

bool AbstractSyntaxTree::evaluate(SpatialTemporalTrace &spatialTemporalTrace,
                                  const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    if (!isInitialized) {
        MS_throw(UnexpectedBehaviourException, ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALIZED);
    }

    return (
        probabilisticLogicProperty.evaluate(
            spatialTemporalTrace,
            multiscaleArchitectureGraph
        )
    );
}


// Constants
const std::string AbstractSyntaxTree::ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALIZED = "The abstract syntax tree was not initialized before evaluation. Please call the method initializeTree(...) before calling the method evaluate(...).";
