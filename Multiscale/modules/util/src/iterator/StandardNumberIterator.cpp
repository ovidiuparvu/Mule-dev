#include "multiscale/util/iterator/StandardNumberIterator.hpp"

using namespace multiscale;


StandardNumberIterator::StandardNumberIterator(unsigned int upperBound) : NumberIterator(upperBound) {
    initialize();
    reset();
}

StandardNumberIterator::~StandardNumberIterator() {}

unsigned int StandardNumberIterator::number() {
    return currentNumber;
}

void StandardNumberIterator::initialize() {}

bool StandardNumberIterator::hasNextInitialized() {
    if (currentNumber == upperBound) {
        return false;
    } else {
        currentNumber++;

        return true;
    }
}

void StandardNumberIterator::resetCurrentNumber() {
    this->currentNumber = 1;
}
