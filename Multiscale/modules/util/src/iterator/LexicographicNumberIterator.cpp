#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"

using namespace multiscale;


LexicographicNumberIterator::LexicographicNumberIterator(unsigned int upperBound) : NumberIterator(upperBound) {
    initialize();
    reset();
}

LexicographicNumberIterator::~LexicographicNumberIterator() {
    upperBoundDigits.clear();
    currentNumberDigits.clear();
}

unsigned int LexicographicNumberIterator::number() {
    return digitsToNumber(currentNumberDigits);
}

void LexicographicNumberIterator::initialize() {
    numberToDigits(upperBound, upperBoundDigits);

    currentNumberDigits.reserve(upperBoundDigits.size());
}

bool LexicographicNumberIterator::hasNextInitialized() {
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

void LexicographicNumberIterator::resetCurrentNumber() {
    currentNumberDigits.clear();
    currentNumberDigits.push_back(1);

    int nrOfDigits = upperBoundDigits.size();

    for (int i = 1; i < nrOfDigits; i++) {
        currentNumberDigits.push_back(0);
    }
}

void LexicographicNumberIterator::numberToDigits(unsigned int number, std::vector<unsigned char> &digits) {
    while (number != 0) {
        digits.push_back(number % 10);

        number = number / 10;
    }

    reverseDigits(digits);
}

void LexicographicNumberIterator::reverseDigits(std::vector<unsigned char> &digits) {
    int             nrOfDigits = digits.size();
    unsigned char   tmpDigit   = 0;

    for (int i = 0; i < (nrOfDigits / 2); i++) {
        tmpDigit                    = digits[i];
        digits[i]                   = digits[nrOfDigits - 1 - i];
        digits[nrOfDigits - 1 - i]  = tmpDigit;
    }
}

unsigned int LexicographicNumberIterator::digitsToNumber(std::vector<unsigned char> &digits) {
    unsigned int number = 0;

    int nrOfDigits = digits.size();

    for (int i = nrOfDigits; i > 0; i--) {
        number = (number * 10) + digits[nrOfDigits - i];
    }

    return number;
}

bool LexicographicNumberIterator::isLargerThanUpperBound(unsigned char lastDigit) {
    unsigned int nrOfDigitsCurrent = currentNumberDigits.size();
    unsigned int nrOfDigitsUpper   = upperBoundDigits.size();

    if (nrOfDigitsCurrent == nrOfDigitsUpper) {
        for (unsigned int i = 0; i < (nrOfDigitsCurrent - 1); i++) {
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
