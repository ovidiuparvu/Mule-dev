#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale;


double Numeric::epsilon = 1E-5;


bool Numeric::greaterOrEqual(double number1, double number2) {
    return ((number1 > number2) || (almostEqual(number1, number2)));
}

bool Numeric::lessOrEqual(double number1, double number2) {
    return ((number1 < number2) || (almostEqual(number1, number2)));
}

bool Numeric::almostEqual(double number1, double number2) {
    return (abs(number1 - number2) <= (epsilon * maximum(1.0, abs(number1), abs(number2))));
}

double Numeric::maximum(double number1, double number2, double number3) {
    return max(max(number1, number2), number3);
}

int Numeric::sign(double number) {
    return (number > 0) ? 1 : ((number < 0) ? -1 : 0);
}

double Numeric::log(double number, double base) {
    validateLogNumberAndBase(number, base);

    return ((std::log(number)) / (std::log(base)));
}

void Numeric::validateLogNumberAndBase(double number, double base) {
    validateLogNumber(number);
    validateLogBase(base);
}

void Numeric::validateLogNumber(double number) {
    if (!isPositive(number)) {
        MS_throw_detailed(InvalidInputException, ERR_LOG_NUMBER_START,
                          StringManipulator::toString(number), ERR_LOG_NUMBER_END);
    }
}

void Numeric::validateLogBase(double base) {
    if ((!isPositive(base)) || (almostEqual(base, 1))) {
        MS_throw_detailed(InvalidInputException, ERR_LOG_BASE_START,
                          StringManipulator::toString(base), ERR_LOG_BASE_END);
    }
}


// Constants

const std::string Numeric::ERR_LOG_BASE_START = "The base provided to the log function (";
const std::string Numeric::ERR_LOG_BASE_END   = ") should be a positive real number different from 1. Please change.";
const std::string Numeric::ERR_LOG_NUMBER_START = "The number provided to the log function (";
const std::string Numeric::ERR_LOG_NUMBER_END   = ") should be a positive real number. Please change.";
