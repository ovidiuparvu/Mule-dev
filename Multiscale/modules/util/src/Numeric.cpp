#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <algorithm>
#include <cfenv>
#include <cmath>
#include <limits>
#include <vector>

using namespace multiscale;


double Numeric::epsilon = 1E-9;


bool Numeric::greaterOrEqual(double number1, double number2) {
    return (
        (number1 > number2) ||
        (almostEqual(number1, number2))
    );
}

bool Numeric::lessOrEqual(double number1, double number2) {
    return (
        (number1 < number2) ||
        (almostEqual(number1, number2))
    );
}

bool Numeric::almostEqual(double number1, double number2) {
    return (
        (std::fabs(number1 - number2) <=
        (epsilon * maximum(1.0, std::fabs(number1), std::fabs(number2))))
    );
}

double Numeric::average(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_AVERAGE_FUNCTION_NAME);

        return 0;
    }

    return average(numbers, nrOfValues);
}

double Numeric::combinations(unsigned int n, unsigned int k) {
    if (n < k) {
        MS_throw(
            NumericException,
            ERR_COMBINATIONS_START + StringManipulator::toString(n) +
            ERR_COMBINATIONS_MIDDLE + StringManipulator::toString(k) +
            ERR_COMBINATIONS_END
        );
    }

    return computeCombinations(n, k);
}

double Numeric::covariance(const std::vector<double> &values1, const std::vector<double> &values2) {
    unsigned int nrOfValues = std::min(values1.size(), values2.size());

    if (nrOfValues <= 1) {
        printNoValuesWarningMessage(WRN_COVARIANCE_FUNCTION_NAME);

        return 0;
    }

    return covariance(values1, values2, nrOfValues);
}

double Numeric::division(double nominator, double denominator) {
    return (
        (almostEqual(denominator, 0))
            ? 0
            : (nominator / denominator)
    );
}

unsigned long Numeric::factorial(unsigned int number) {
    unsigned long result = 1;

    for (unsigned long i = 2; i <= number; i++) {
        result = applyOperation(MultiplicationOperation(), result, i);
    }

    return result;
}

double Numeric::geometricMean(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_GEOMETRIC_MEAN_FUNCTION_NAME);

        return 0;
    }

    return geometricMean(numbers, nrOfValues);
}

double Numeric::harmonicMean(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_HARMONIC_MEAN_FUNCTION_NAME);

        return 0;
    }

    return harmonicMean(numbers, nrOfValues);
}

double Numeric::kurtosis(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues <= 3) {
        printNoValuesWarningMessage(WRN_KURTOSIS_FUNCTION_NAME);

        return 0;
    }

    return kurtosis(numbers, nrOfValues);
}

double Numeric::log(double number, double base) {
    validateLogNumberAndBase(number, base);

    return ((std::log(number)) / (std::log(base)));
}

double Numeric::maximum(double number1, double number2, double number3) {
    return std::max(std::max(number1, number2), number3);
}

double Numeric::maximum(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_MAXIMUM_FUNCTION_NAME);

        return 0;
    }

    return maximum(numbers, nrOfValues);
}

double Numeric::median(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_MEDIAN_FUNCTION_NAME);

        return 0;
    }

    return median(numbers, nrOfValues);
}

double Numeric::minimum(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_MINIMUM_FUNCTION_NAME);

        return 0;
    }

    return minimum(numbers, nrOfValues);
}

double Numeric::mode(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_MODE_FUNCTION_NAME);

        return 0;
    }

    return mode(numbers, nrOfValues);
}

double Numeric::percentile(const std::vector<double> &numbers, double percentile) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_PERCENTILE_FUNCTION_NAME);

        return 0;
    }

    return Numeric::percentile(numbers, percentile, nrOfValues);
}

double Numeric::product(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_PRODUCT_FUNCTION_NAME);

        return 0;
    }

    return Numeric::product(numbers, nrOfValues);
}

double Numeric::quartile(const std::vector<double> &numbers, double quartile) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_QUARTILE_FUNCTION_NAME);

        return 0;
    }

    return Numeric::quartile(numbers, quartile, nrOfValues);
}

double Numeric::skew(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_SKEW_FUNCTION_NAME);

        return 0;
    }

    return Numeric::skew(numbers, nrOfValues);
}

int Numeric::sign(double number) {
    return (number > 0) ? 1 : ((number < 0) ? -1 : 0);
}

double Numeric::standardDeviation(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues <= 1) {
        printNoValuesWarningMessage(WRN_STANDARD_DEVIATION_FUNCTION_NAME);

        return 0;
    }

    return Numeric::standardDeviation(numbers, nrOfValues);
}

double Numeric::sum(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues == 0) {
        printNoValuesWarningMessage(WRN_SUM_FUNCTION_NAME);

        return 0;
    }

    return Numeric::sum(numbers, nrOfValues);
}

double Numeric::variance(const std::vector<double> &numbers) {
    unsigned int nrOfValues = numbers.size();

    if (nrOfValues <= 1) {
        printNoValuesWarningMessage(WRN_VARIANCE_FUNCTION_NAME);

        return 0;
    }

    return Numeric::variance(numbers, nrOfValues);
}

void Numeric::printNoValuesWarningMessage(const std::string &functionName) {
    ConsolePrinter::printWarningMessage(WRN_NOT_ENOUGH_VALUES_START + functionName + WRN_NOT_ENOUGH_VALUES_END);
}

double Numeric::average(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double sum = 0;

    for (double number : numbers) {
        sum = applyOperation(AdditionOperation(), sum, number);
    }

    return (division(sum, nrOfValues));
}

double Numeric::computeCombinations(unsigned int n, unsigned int k) {
    double result = 1;

    for (unsigned int i = 0; i < k; i++) {
        result = result * (n - i);
        result = result / (i + 1);
    }

    return result;
}

double Numeric::covariance(const std::vector<double> &values1, const std::vector<double> &values2,
                           unsigned int nrOfValues) {
    double mean1 = average(values1);
    double mean2 = average(values2);

    double covariance = 0;

    for (unsigned int i = 0; i < nrOfValues; i++) {
        covariance = applyOperation(AdditionOperation(), covariance, (values1[i] - mean1) * (values2[i] - mean2));
    }

    return (division(covariance, (nrOfValues - 1)));
}

double Numeric::geometricMean(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double logSum = 0;

    for (double number : numbers) {
        validateLogNumber(number);

        logSum = applyOperation(AdditionOperation(), logSum, std::log(number));
    }

    return (nrOfValues == 0) ? 0
                             : (std::exp(logSum / nrOfValues));
}

double Numeric::harmonicMean(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double inverseSum = 0;

    for (double number : numbers) {
        double invertedNumber = numberInverse(number);

        inverseSum = applyOperation(AdditionOperation(), inverseSum, invertedNumber);
    }

    return (nrOfValues * (division(1.0, inverseSum)));
}

double Numeric::kurtosis(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double firstTerm = computeKurtosisFirstTerm(nrOfValues);
    double middleTerm = computeKurtosisMiddleTerm(numbers, nrOfValues);
    double lastTerm = computeKurtosisLastTerm(nrOfValues);

    return ((firstTerm * middleTerm) - (lastTerm));
}

double Numeric::computeKurtosisFirstTerm(unsigned int nrOfValues) {
    double nrOfValues_ = static_cast<double>(nrOfValues);

    return (nrOfValues_ > 3) ? (nrOfValues_ * (nrOfValues_ + 1)) /
                               ((nrOfValues_ - 1) * (nrOfValues_ - 2) * (nrOfValues_ - 3))
                             : 0;
}

double Numeric::computeKurtosisMiddleTerm(const std::vector<double> &values, unsigned int nrOfValues) {
    double mean  = average(values);
    double stdev = standardDeviation(values);

    double nominator   = 0;
    double denominator = std::pow(stdev, 4);

    for (double value : values) {
        nominator = applyOperation(AdditionOperation(), nominator, std::pow((value - mean), 4));
    }

    return (division(nominator, denominator));
}

double Numeric::computeKurtosisLastTerm(unsigned int nrOfValues) {
    double nrOfValues_ = static_cast<double>(nrOfValues);

    return (nrOfValues_ > 3) ? (std::pow((nrOfValues_ - 1), 2) * 3) /
                               ((nrOfValues_ - 2) * (nrOfValues_ - 3))
                             : 0;
}

double Numeric::maximum(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double maximum = std::numeric_limits<double>::lowest();

    for (double number : numbers) {
        if (number > maximum) {
            maximum = number;
        }
    }

    return (nrOfValues > 0) ? maximum
                            : 0;
}

double Numeric::median(const std::vector<double> &numbers, unsigned int nrOfValues) {
    std::vector<double> values = numbers;

    std::sort(values.begin(), values.end());

    return (nrOfValues == 0) ? 0
                             : (values[nrOfValues / 2]);
}

double Numeric::minimum(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double minimum = std::numeric_limits<double>::max();

    for (double number : numbers) {
        if (number < minimum) {
            minimum = number;
        }
    }

    return (nrOfValues > 0) ? minimum
                            : 0;
}

double Numeric::mode(const std::vector<double> &numbers, unsigned int nrOfValues) {
    std::vector<double> values = numbers;

    std::sort(values.begin(), values.end());

    double modeValue = computeMode(values, nrOfValues);

    return modeValue;
}

double Numeric::computeMode(const std::vector<double> &values, unsigned int nrOfValues) {
    unsigned int index = 0;
    double modeValue = std::numeric_limits<double>::min();
    double countValue = 0;
    int maxCount = 0;

    while (index < nrOfValues) {
        countValue = 1;

        while ((index < (nrOfValues - 1)) && (almostEqual(values[index], values[index + 1]))) {
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

double Numeric::percentile(const std::vector<double> &numbers, double percentile, unsigned int nrOfValues) {
    std::vector<double> values = numbers;
    double nrOfValues_ = static_cast<double>(nrOfValues);

    std::sort(values.begin(), values.end());

    validatePercentile(percentile);

    return (nrOfValues_ > 0) ? values[std::floor(((percentile / 100) * (nrOfValues_ - 1)) + (0.5))]
                             : 0;
}

double Numeric::product(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double product = 1;

    for (double number : numbers) {
        product = applyOperation(MultiplicationOperation(), product, number);
    }

    return product;
}

double Numeric::quartile(const std::vector<double> &numbers, double quartile, unsigned int nrOfValues) {
    std::vector<double> values = numbers;

    std::sort(values.begin(), values.end());

    validateQuartile(quartile);

    return (nrOfValues > 0) ? computeQuartileValue(quartile, values, nrOfValues)
                            : 0;
}

double Numeric::computeQuartileValue(double quartile, const std::vector<double> &values, unsigned int nrOfValues) {
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

double Numeric::skew(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double firstTerm = computeSkewFirstTerm(nrOfValues);
    double lastTerm  = computeSkewLastTerm(numbers, nrOfValues);

    return (firstTerm * lastTerm);
}

double Numeric::computeSkewFirstTerm(unsigned int nrOfValues) {
    double nrOfValues_ = static_cast<double>(nrOfValues);

    return (nrOfValues_ > 2) ? (nrOfValues_) / ((nrOfValues_ - 1) * (nrOfValues_ - 2))
                             : 0;
}

double Numeric::computeSkewLastTerm(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double mean  = average(numbers);
    double stdev = standardDeviation(numbers);

    double nominator    = 0;
    double denominator  = std::pow(stdev, 3);


    for (double number : numbers) {
        nominator = applyOperation(AdditionOperation(), nominator, std::pow((number - mean), 3));
    }

    return (division(nominator, denominator));
}

double Numeric::standardDeviation(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double mean = average(numbers);
    double denominator = 0;

    for (double number : numbers) {
        denominator = applyOperation(AdditionOperation(), denominator, std::pow(number - mean, 2));
    }

    return (nrOfValues <= 1) ? 0
                             : std::sqrt(denominator / (nrOfValues - 1));
}

double Numeric::sum(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double sum = 0;

    for (double number : numbers) {
        sum = applyOperation(AdditionOperation(), sum, number);
    }

    return sum;
}

double Numeric::variance(const std::vector<double> &numbers, unsigned int nrOfValues) {
    double mean = average(numbers);
    double denominator = 0;

    for (double number : numbers) {
        denominator = applyOperation(AdditionOperation(), denominator, std::pow(number - mean, 2));
    }

    return (nrOfValues <= 1) ? 0
                             : (denominator / (nrOfValues - 1));
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

const std::string Numeric::ERR_COMBINATIONS_START   = "The provided number of elements n (";
const std::string Numeric::ERR_COMBINATIONS_MIDDLE  = ") should be greater or equal to the number of elements in each group k (";
const std::string Numeric::ERR_COMBINATIONS_END     = ") when computing combinations.";

const std::string Numeric::ERR_PERCENTILE_VALUE_START = "The provided percentile value (";
const std::string Numeric::ERR_PERCENTILE_VALUE_END   = ") should be between 0 and 100. Please change.";

const std::string Numeric::ERR_QUARTILE_VALUE_START = "The provided quartile value (";
const std::string Numeric::ERR_QUARTILE_VALUE_END   = ") should be 25, 50 or 75. Please change.";

const std::string Numeric::WRN_NUMBER_INVERSE = "You provided the invalid value \"0\" to the Numeric::inverse(...) function. The default value \"0\" was returned.";

const std::string Numeric::WRN_NOT_ENOUGH_VALUES_START  = "You provided less than the minimum required number of values to the Numeric::";
const std::string Numeric::WRN_NOT_ENOUGH_VALUES_END    = "(...) function. The default value \"0\" was returned.";

const std::string Numeric::WRN_AVERAGE_FUNCTION_NAME             = "average";
const std::string Numeric::WRN_COVARIANCE_FUNCTION_NAME          = "covariance";
const std::string Numeric::WRN_GEOMETRIC_MEAN_FUNCTION_NAME      = "geometricMean";
const std::string Numeric::WRN_HARMONIC_MEAN_FUNCTION_NAME       = "harmonicMean";
const std::string Numeric::WRN_KURTOSIS_FUNCTION_NAME            = "kurtosis";
const std::string Numeric::WRN_MAXIMUM_FUNCTION_NAME             = "maximum";
const std::string Numeric::WRN_MEDIAN_FUNCTION_NAME              = "median";
const std::string Numeric::WRN_MODE_FUNCTION_NAME                = "mode";
const std::string Numeric::WRN_MINIMUM_FUNCTION_NAME             = "minimum";
const std::string Numeric::WRN_PERCENTILE_FUNCTION_NAME          = "percentile";
const std::string Numeric::WRN_PRODUCT_FUNCTION_NAME             = "product";
const std::string Numeric::WRN_QUARTILE_FUNCTION_NAME            = "quartile";
const std::string Numeric::WRN_SKEW_FUNCTION_NAME                = "skew";
const std::string Numeric::WRN_STANDARD_DEVIATION_FUNCTION_NAME  = "standardDeviation";
const std::string Numeric::WRN_SUM_FUNCTION_NAME                 = "sum";
const std::string Numeric::WRN_VARIANCE_FUNCTION_NAME            = "variance";
