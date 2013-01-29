#include "multiscale/util/NumberIterator.hpp"

using namespace multiscale;

// Constructor for the class
NumberIterator::NumberIterator(unsigned int upperBound) {
	init(upperBound);
}

// Initialisation function
void NumberIterator::init(unsigned int upperBound) {
	this->upperBound = upperBound;
}

// Check if there is a next number and update the current number accordingly
bool NumberIterator::hasNext() {
	if (!isInitialised) {
		return hasNextNotInitialised();
	} else {
		return hasNextInitialised();
	}
}

// Reset the current number and initialised state
void NumberIterator::reset() {
	resetCurrentNumber();

	this->isInitialised = false;
}

// Initialise and return true
bool NumberIterator::hasNextNotInitialised() {
	this->isInitialised = true;

	return true;
}
