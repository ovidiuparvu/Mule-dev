#include "multiscale/util/NumberIterator.hpp"

using namespace multiscale;


NumberIterator::NumberIterator(unsigned int upperBound) {
    init(upperBound);
}

void NumberIterator::init(unsigned int upperBound) {
    this->upperBound = upperBound;
}

bool NumberIterator::hasNext() {
    if (!isInitialized) {
        return hasNextNotInitialized();
    } else {
        return hasNextInitialized();
    }
}

void NumberIterator::reset() {
    resetCurrentNumber();

    this->isInitialized = false;
}

bool NumberIterator::hasNextNotInitialized() {
    this->isInitialized = true;

    return true;
}
