#include "multiscale/util/iterator/StandardNumberIterator.hpp"

using namespace multiscale;


StandardNumberIterator::StandardNumberIterator(unsigned int upperBound) : NumberIterator(upperBound) {
    initialise();
    reset();
}

StandardNumberIterator::~StandardNumberIterator() {}

unsigned int StandardNumberIterator::number() {
    return currentNumber;
}

void StandardNumberIterator::initialise() {}

bool StandardNumberIterator::hasNextInitialised() {
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
