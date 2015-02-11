#include "multiscale/util/NumberIterator.hpp"

using namespace multiscale;


NumberIterator::NumberIterator(unsigned int upperBound) {
    init(upperBound);
}

void NumberIterator::init(unsigned int upperBound) {
    this->upperBound = upperBound;
}

bool NumberIterator::hasNext() {
    if (!isInitialised) {
        return hasNextNotInitialised();
    } else {
        return hasNextInitialised();
    }
}

void NumberIterator::reset() {
    resetCurrentNumber();

    this->isInitialised = false;
}

bool NumberIterator::hasNextNotInitialised() {
    this->isInitialised = true;

    return true;
}
