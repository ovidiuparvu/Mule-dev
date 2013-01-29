#include "multiscale/util/iterator/StandardNumberIterator.hpp"

using namespace multiscale;


// Constructor for the class
StandardNumberIterator::StandardNumberIterator(unsigned int upperBound)
							: NumberIterator(upperBound) {
	initialise();
	reset();
}

// Destructor for the class
StandardNumberIterator::~StandardNumberIterator() {
	// Do nothing
}

// Return the current number
unsigned int StandardNumberIterator::number() {
	return currentNumber;
}

// Initialise the current number
void StandardNumberIterator::initialise() {
	// Do nothing
}

// Check if there is a next number after the current one and update the number
bool StandardNumberIterator::hasNextInitialised() {
	if (currentNumber == upperBound) {
		return false;
	} else {
		currentNumber++;

		return true;
	}
}

// Reset the current number
void StandardNumberIterator::resetCurrentNumber() {
	this->currentNumber = 1;
}
