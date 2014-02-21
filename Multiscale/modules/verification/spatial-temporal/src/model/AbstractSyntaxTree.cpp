#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

using namespace multiscale::verification;


AbstractSyntaxTree::AbstractSyntaxTree(ProbabilisticLogicPropertyAttribute &probabilisticLogicPropertyAttribute) {
    this->probabilisticLogicProperty = probabilisticLogicPropertyAttribute;
}

ComparatorType AbstractSyntaxTree::getComparator() {
    return probabilisticLogicProperty.getComparator();
}

double AbstractSyntaxTree::getProbability() {
    return probabilisticLogicProperty.getProbability();
}

bool AbstractSyntaxTree::evaluate(const SpatialTemporalTrace &spatialTemporalTrace) {
    // TODO: Replace the below line with return abstractSyntaxTree.evaluate(spatialTemporalTrace);
    return true;
}
