#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"

using namespace multiscale::verification;


ComparatorType ProbabilisticLogicPropertyAttribute::getComparator() {
    return comparator.comparatorType;
}

double ProbabilisticLogicPropertyAttribute::getProbability() {
    return probability;
}
