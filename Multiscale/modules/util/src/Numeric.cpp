#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

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

double Numeric::average(const std::vector<double> &numbers) {
    double sum = 0;
    int nrOfValues = numbers.size();

    for (double number : numbers) {
        sum = applyOperation(AdditionOperation(), sum, number);
    }

    return (nrOfValues == 0) ? 0
                             : (sum / nrOfValues);
}

double Numeric::covariance(const std::vector<double> &values1, const std::vector<double> &values2) {
    int nrOfValues = std::min(values1.size(), values2.size());

    double mean1 = average(values1);
    double mean2 = average(values2);

    double covariance = 0;

    for (int i = 0; i < nrOfValues; i++) {
        covariance = applyOperation(AdditionOperation(), covariance, (values1[i] - mean1) * (values2[i] - mean2));
    }

    return (nrOfValues > 1) ? (covariance / (nrOfValues - 1))
                            : 0;
}

double Numeric::geometricMean(const std::vector<double> &numbers) {
    double logSum = 0;
    int nrOfValues = numbers.size();

    for (double number : numbers) {
        logSum = applyOperation(AdditionOperation(), logSum, std::log(number));
    }

    return (nrOfValues == 0) ? 0
                             : (std::exp(logSum / nrOfValues));
}

double Numeric::harmonicMean(const std::vector<double> &numbers) {
    double inverseSum = 0;
    int nrOfValues = numbers.size();

    for (double number : numbers) {
        double invertedNumber = (number == 0) ? 0 : (1.0 / number);

        inverseSum = applyOperation(AdditionOperation(), inverseSum, invertedNumber);
    }

    return (inverseSum == 0) ? 0
                             : (nrOfValues * (1.0 / inverseSum));
}

double Numeric::kurtosis(const std::vector<double> &numbers) {
    int nrOfValues = numbers.size();

    double firstTerm = computeKurtosisFirstTerm(nrOfValues);
    double middleTerm = computeKurtosisMiddleTerm(numbers, nrOfValues);
    double lastTerm = computeKurtosisLastTerm(nrOfValues);

    return ((firstTerm * middleTerm) - (lastTerm));
}

double Numeric::log(double number, double base) {
    validateLogNumberAndBase(number, base);

    return ((std::log(number)) / (std::log(base)));
}

double Numeric::maximum(double number1, double number2, double number3) {
    return max(max(number1, number2), number3);
}

double Numeric::maximum(const std::vector<double> &numbers) {
    double maximum = std::numeric_limits<double>::min();

    for (double number : numbers) {
        if (number > maximum) {
            maximum = number;
        }
    }

    return (numbers.size() > 0) ? maximum
                                : 0;
}

double Numeric::median(const std::vector<double> &numbers) {
    std::vector<double> values = numbers;
    int nrOfValues = values.size();

    std::sort(values.begin(), values.end());

    return (nrOfValues == 0) ? 0
                             : (values[nrOfValues / 2]);
}

double Numeric::minimum(const std::vector<double> &numbers) {
    double minimum = std::numeric_limits<double>::max();

    for (double number : numbers) {
        if (number < minimum) {
            minimum = number;
        }
    }

    return (numbers.size() > 0) ? minimum
                                : 0;
}

double Numeric::mode(const std::vector<double> &numbers) {
    std::vector<double> values = numbers;
    int nrOfValues = values.size();

    std::sort(values.begin(), values.end());

    double modeValue = mode(values, nrOfValues);

    return modeValue;
}

double Numeric::percentile(const std::vector<double> &numbers, double percentile) {
    std::vector<double> values = numbers;
    int nrOfValues = values.size();

    std::sort(values.begin(), values.end());

    validatePercentile(percentile);

    return (nrOfValues > 0) ? numbers[std::floor(((percentile / 100) * nrOfValues) + (1 / 2))]
                            : 0;
}

double Numeric::product(const std::vector<double> &numbers) {
    double product = 1;

    for (double number : numbers) {
        product = applyOperation(MultiplicationOperation(), product, number);
    }

    return product;
}

double Numeric::quartile(const std::vector<double> &numbers, double quartile) {
    std::vector<double> values = numbers;
    int nrOfValues = values.size();

    std::sort(values.begin(), values.end());

    validateQuartile(quartile);

    return (nrOfValues > 0) ? computeQuartileValue(quartile, values, nrOfValues)
                            : 0;
}

double Numeric::skew(const std::vector<double> &numbers) {
    int nrOfValues = numbers.size();

    double firstTerm = computeSkewFirstTerm(nrOfValues);
    double lastTerm  = computeSkewLastTerm(numbers, nrOfValues);

    return (firstTerm * lastTerm);
}

int Numeric::sign(double number) {
    return (number > 0) ? 1 : ((number < 0) ? -1 : 0);
}

double Numeric::standardDeviation(const std::vector<double> &numbers) {
    double mean = average(numbers);
    double denominator = 0;
    int nrOfValues = numbers.size();

    for (double number : numbers) {
        denominator = applyOperation(AdditionOperation(), denominator, std::pow(number - mean, 2));
    }

    return (nrOfValues <= 1) ? 0
                             : std::sqrt(denominator / (nrOfValues - 1));
}

double Numeric::sum(const std::vector<double> &numbers) {
    double sum = 0;

    for (double number : numbers) {
        sum = applyOperation(AdditionOperation(), sum, number);
    }

    return sum;
}

double Numeric::variance(const std::vector<double> &numbers) {
    double mean = average(numbers);
    double denominator = 0;
    int nrOfValues = numbers.size();

    for (double number : numbers) {
        denominator = applyOperation(AdditionOperation(), denominator, std::pow(number - mean, 2));
    }

    return (nrOfValues <= 1) ? 0
                             : (denominator / (nrOfValues - 1));
}

double Numeric::computeKurtosisFirstTerm(int nrOfValues) {
    return (nrOfValues > 3) ? (nrOfValues * (nrOfValues + 1)) /
                              ((nrOfValues - 1) * (nrOfValues - 2) * (nrOfValues - 3))
                            : 0;
}

double Numeric::computeKurtosisMiddleTerm(const std::vector<double> &values, int nrOfValues) {
    double middleTerm = 0;

    double mean  = average(values);
    double stdev = standardDeviation(values);

    for (double value : values) {
        middleTerm = applyOperation(AdditionOperation(), middleTerm, std::pow(value - mean, 4));
    }

    return (stdev != 0) ? (middleTerm / (std::pow(stdev, 4)))
                        : 0;
}

double Numeric::computeKurtosisLastTerm(int nrOfValues) {
    return (nrOfValues > 3) ? (3 * std::pow(nrOfValues - 1, 2)) /
                              ((nrOfValues - 2) * (nrOfValues - 3))
                            : 0;
}

double Numeric::computeQuartileValue(double quartile, const std::vector<double> &values, int nrOfValues) {
    int medianIndex = nrOfValues / 2;

    if (Numeric::almostEqual(quartile, 50)) {
        return values[medianIndex];
    } else if (Numeric::almostEqual(quartile, 25)) {
        return (nrOfValues < 2) ? values[medianIndex]
                                : values[(medianIndex - 1) / 2];
    } else {
        return (nrOfValues < 3) ? values[medianIndex]
                                : values[(medianIndex + 1) + ((nrOfValues - medianIndex - 1) / 2)];
    }
}

double Numeric::computeSkewFirstTerm(int nrOfValues) {
    return (nrOfValues > 2) ? (nrOfValues) / ((nrOfValues - 1) * (nrOfValues - 2))
                            : 0;
}

double Numeric::computeSkewLastTerm(const std::vector<double> &numbers, int nrOfValues) {
    double skewSum = 0;

    double mean  = average(numbers);
    double stdev = standardDeviation(numbers);

    for (double number : numbers) {
        skewSum = applyOperation(AdditionOperation(), skewSum, std::pow((number - mean) / (stdev), 3));
    }

    return skewSum;
}

double Numeric::mode(const std::vector<double> &values, int nrOfValues) {
    int index = 0;
    double modeValue = numeric_limits<double>::min();
    double countValue = 0;
    int maxCount = 0;

    while (index < nrOfValues) {
        countValue = 1;

        while ((index < (nrOfValues - 1)) && (values[index] == values[index + 1])) {
            index++;
            countValue++;
        }

        if (maxCount < countValue) {
            maxCount = countValue;
            modeValue = values[index];
        }

        index++;
    }

    return modeValue;
}

void Numeric::resetOverflowUnderflowFlags() {
    std::feclearexcept(FE_OVERFLOW);
    std::feclearexcept(FE_UNDERFLOW);
}

bool Numeric::areOverflowUnderflowFlagsSet() {
    bool isOverflowFlagSet = (bool)std::fetestexcept(FE_OVERFLOW);
    bool isUnderflowFlagSet = (bool)std::fetestexcept(FE_UNDERFLOW);

    return (isOverflowFlagSet || isUnderflowFlagSet);
}

void Numeric::validateLogNumberAndBase(double number, double base) {
    validateLogNumber(number);
    validateLogBase(base);
}

void Numeric::validateLogNumber(double number) {
    if (!isPositive(number)) {
        MS_throw_detailed(NumericException, ERR_LOG_NUMBER_START,
                          StringManipulator::toString(number), ERR_LOG_NUMBER_END);
    }
}

void Numeric::validateLogBase(double base) {
    if ((!isPositive(base)) || (almostEqual(base, 1))) {
        MS_throw_detailed(NumericException, ERR_LOG_BASE_START,
                          StringManipulator::toString(base), ERR_LOG_BASE_END);
    }
}

void Numeric::validatePercentile(double percentile) {
    if ((percentile < 0) || (percentile > 100)) {
        MS_throw_detailed(NumericException, ERR_PERCENTILE_VALUE_START, StringManipulator::toString<double>(percentile),
                ERR_PERCENTILE_VALUE_END);
    }
}

void Numeric::validateQuartile(double quartile) {
    if ((!almostEqual(quartile, 25)) && (!almostEqual(quartile, 50)) && (!almostEqual(quartile, 75))) {
        MS_throw_detailed(NumericException, ERR_QUARTILE_VALUE_START, StringManipulator::toString<double>(quartile),
                ERR_QUARTILE_VALUE_END);
    }
}


// Constants

const std::string Numeric::ERR_LOG_BASE_START = "The base provided to the log function (";
const std::string Numeric::ERR_LOG_BASE_END   = ") should be a positive real number different from 1. Please change.";
const std::string Numeric::ERR_LOG_NUMBER_START = "The number provided to the log function (";
const std::string Numeric::ERR_LOG_NUMBER_END   = ") should be a positive real number. Please change.";

const std::string Numeric::ERR_OVERFLOW_UNDERFLOW = "An underflow/overflow exception occurred.";

const std::string Numeric::ERR_PERCENTILE_VALUE_START = "The provided percentile value (";
const std::string Numeric::ERR_PERCENTILE_VALUE_END   = ") should be between 0 and 100. Please change.";

const std::string Numeric::ERR_QUARTILE_VALUE_START = "The provided quartile value (";
const std::string Numeric::ERR_QUARTILE_VALUE_END   = ") should be 25, 50 or 75. Please change.";
