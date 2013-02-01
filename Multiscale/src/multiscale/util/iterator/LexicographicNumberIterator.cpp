#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"

using namespace multiscale;


// Constructor for the class
LexicographicNumberIterator::LexicographicNumberIterator(unsigned int upperBound) : NumberIterator(upperBound) {
    initialise();
    reset();
}

// Destructor for the class
LexicographicNumberIterator::~LexicographicNumberIterator() {
    upperBoundDigits.clear();
    currentNumberDigits.clear();
}

// Return the current number
unsigned int LexicographicNumberIterator::number() {
    return digitsToNumber(currentNumberDigits);
}

// Initialise the vectors of digits
void LexicographicNumberIterator::initialise() {
    numberToDigits(upperBound, upperBoundDigits);

    currentNumberDigits.reserve(upperBoundDigits.size());
}

// Check if there is a next number when in initialised state
bool LexicographicNumberIterator::hasNextInitialised() {
    unsigned char lastDigit = currentNumberDigits.back();

    if (((lastDigit + 1) <= 9) && (!isLargerThanUpperBound(lastDigit + 1))) {
        currentNumberDigits[currentNumberDigits.size() - 1]++;

        padWithZeros();
    } else if (currentNumberDigits.size() > 1) {
        currentNumberDigits.pop_back();
    } else {
        return false;
    }

    return true;
}

// Reset the value of the current number
void LexicographicNumberIterator::resetCurrentNumber() {
    currentNumberDigits.clear();
    currentNumberDigits.push_back(1);

    int nrOfDigits = upperBoundDigits.size();

    for (int i = 1; i < nrOfDigits; i++) {
        currentNumberDigits.push_back(0);
    }
}

// Convert the number to a vector of digits
void LexicographicNumberIterator::numberToDigits(unsigned int number, vector<unsigned char>& digits) {
    while (number != 0) {
        digits.push_back(number % 10);

        number = number / 10;
    }

    reverseDigits(digits);
}

// Reverse the order of the digits
void LexicographicNumberIterator::reverseDigits(vector<unsigned char>& digits) {
    int             nrOfDigits = digits.size();
    unsigned char   tmpDigit   = 0;

    for (int i = 0; i < (nrOfDigits / 2); i++) {
        tmpDigit                    = digits[i];
        digits[i]                   = digits[nrOfDigits - 1 - i];
        digits[nrOfDigits - 1 - i]  = tmpDigit;
    }
}

// Convert the digits into a number
unsigned int LexicographicNumberIterator::digitsToNumber(vector<unsigned char>& digits) {
    unsigned int number = 0;

    int nrOfDigits = digits.size();

    for (int i = nrOfDigits; i > 0; i--) {
        number = (number * 10) + digits[nrOfDigits - i];
    }

    return number;
}

/*
 * Check if the current number is greater than the upper bound
 * when replacing the last digit of the current number with the
 * provided digit
 */
bool LexicographicNumberIterator::isLargerThanUpperBound(unsigned char lastDigit) {
    unsigned int nrOfDigitsCurrent = currentNumberDigits.size();
    unsigned int nrOfDigitsUpper   = upperBoundDigits.size();

    if (nrOfDigitsCurrent == nrOfDigitsUpper) {
        for (int i = 0; i < (nrOfDigitsCurrent - 1); i++) {
            if (currentNumberDigits[i] > upperBoundDigits[i]) {
                return true;
            } else if (currentNumberDigits[i] < upperBoundDigits[i]) {
                return false;
            }
        }

        if (lastDigit > upperBoundDigits[nrOfDigitsUpper - 1]) {
            return true;
        }
    }

    return false;
}

/*
 * Pad the current number with as many zeros as possible in order not to
 * become larger than the upper bound
 */
void LexicographicNumberIterator::padWithZeros() {
    int possibleZeros = upperBoundDigits.size() - currentNumberDigits.size() - 1;

    for (int i = 0; i < possibleZeros; i++) {
        currentNumberDigits.push_back(0);
    }

    unsigned int currentNumber = digitsToNumber(currentNumberDigits);

    if ((currentNumber * 10) <= upperBound) {
        currentNumberDigits.push_back(0);
    }
}
