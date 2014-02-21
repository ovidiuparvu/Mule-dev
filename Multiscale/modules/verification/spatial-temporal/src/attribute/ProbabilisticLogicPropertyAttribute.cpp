#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"

using namespace multiscale::verification;


ComparatorType ProbabilisticLogicPropertyAttribute::getComparator() {
    return comparator.comparator;
}

double ProbabilisticLogicPropertyAttribute::getProbability() {
    return probability;
}

bool ProbabilisticLogicPropertyAttribute::evaluate(const SpatialTemporalTrace &trace) {
    return true;
}
