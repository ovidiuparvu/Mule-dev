#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include "multiscale/exception/NumericException.hpp"
#include "multiscale/util/ConsolePrinter.hpp"

#include <algorithm>
#include <cmath>
#include <limits>


namespace multiscale {


    //! Class for processing numeric (shorts, ints, floats, doubles etc.) expressions
    class Numeric {

        private:

            static double epsilon;  /*!< Value of epsilon used to compare two real numbers */

        public:

            //! Check if the first number is greater than or equal to the second number
            /*!
             * \param number1 The first number
             * \param number2 The second number
             */
            static bool greaterOrEqual(double number1, double number2);

            //! Check if the first number is less than or equal to the second number
            /*!
             * \param number1 The first number
             * \param number2 The second number
             */
            static bool lessOrEqual(double number1, double number2);

            //! Check if the two numbers are equal (almost)
            /*!
             * The expression for determining if two real numbers are equal is:
             * if (Abs(x - y) <= EPSILON * Max(1.0f, Abs(x), Abs(y))).
             *
             * \param number1 First number
             * \param number2 Second number
             */
            static bool almostEqual(double number1, double number2);

            //! Return the average (arithmetic mean) of the provided numbers
            /*!
             * \f$ average = \frac{1}{n} \sum\limits^{n}_{i = 1}{x_{i}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double average(const std::vector<double> &numbers);

            //! Return combinations of n taken as groups of k
            /*!
             * \param n The total number of elements
             * \param k The number of elements in each combination
             */
            static double combinations(unsigned int n, unsigned int k);

            //! Return the covariance for the provided collections of values
            /*!
             * \param values1   The first collection of values
             * \param values2   The second collection of values
             */
            static double covariance(const std::vector<double> &values1, const std::vector<double> &values2);

            //! Return the result of dividing two numbers
            /*! If the denominator is almost equal to zero then return zero.
             *  Otherwise return the result of dividing the nominator to the
             *  denominator.
             *
             * \param nominator     The nominator
             * \param denominator   The denominator
             */
            static double division(double nominator, double denominator);

            //! Return the factorial of a number
            /*!
             * \param number The number for which factorial should be computed
             */
            static unsigned long factorial(unsigned int number);

            //! Return the geometric mean of the provided numbers
            /*!
             * \f$ geometricMean = e ^ {\frac{1}{n} \sum\limits_{i = 1}^{n}{log(x_{i})}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double geometricMean(const std::vector<double> &numbers);

            //! Return the harmonic mean of the provided numbers
            /*!
             *  \f$ harmonicMean = \frac{n}{\sum\limits_{i = 1}^{n}{\frac{1}{x_{i}}}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double harmonicMean(const std::vector<double> &numbers);

            //! Return the kurtosis of the provided numbers
            /*!
             * \f$ kurtosis = \frac{n (n + 1)}{(n - 1)(n - 2)(n - 3)} \left( \sum\limits_{i=1}^{n}{(\frac{x_i - mean}{stdev})^{4}} \right) - \frac{3 (n - 1)^{2}} {(n - 2) (n - 3)} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double kurtosis(const std::vector<double> &numbers);

            //! Return the logarithm of a number considering the given base
            /*!
             * The conditions imposed on the number and base are:
             *     - number: a positive real number
             *     - base:   a positive real number different from 1
             *
             *  \param number   The considered number
             *  \param base     The considered base
             */
            static double log(double number, double base);

            //! Return the maximum of the provided numbers
            /*!
             * \param number1 The first number
             * \param number2 The second number
             * \param number3 The third number
             */
            static double maximum(double number1, double number2, double number3);

            //! Return the maximum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double maximum(const std::vector<double> &numbers);

            //! Return the median of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double median(const std::vector<double> &numbers);

            //! Return the mode of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double mode(const std::vector<double> &numbers);

            //! Return the minimum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double minimum(const std::vector<double> &numbers);

            //! Return the p-th percentile of the provided set of values
            /*!
             * \param numbers       The collection of values
             * \param percentile    The p-th percentile
             */
            static double percentile(const std::vector<double> &numbers, double percentile);

            //! Return the product of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double product(const std::vector<double> &numbers);

            //! Return the q-th quartile of the provided set of values
            /*!
             * \param numbers   The collection of values
             * \param quartile  The q-th quartile
             */
            static double quartile(const std::vector<double> &numbers, double quartile);

            //! Round the number considering the given precision
            /*!
             * \param number    The given number
             * \param precision The considered precision
             */
            template <typename FloatingPointType>
            static FloatingPointType round(FloatingPointType number, unsigned int precision = 2) {
                FloatingPointType precisionMultiplierFactor = std::pow(10.0, static_cast<FloatingPointType>(precision));

                return (
                    (std::round(number * precisionMultiplierFactor)) /
                    (precisionMultiplierFactor)
                );
            }

            //! Return the skew of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double skew(const std::vector<double> &numbers);

            //! Return the sign of the number
            /*!
             * The sign function returns:
             *  -1, if number < 0
             *  +1, if number > 0
             *  0, otherwise
             *
             *  \param number The considered number
             */
            static int sign(double number);

            //! Return the standard deviation of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double standardDeviation(const std::vector<double> &numbers);

            //! Return the sum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double sum(const std::vector<double> &numbers);

            //! Return the variance of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double variance(const std::vector<double> &numbers);

        private:

            //! Print the no values warning message for the given function name
            /*!
             * \param functionName  The provided function name
             */
            static void printNoValuesWarningMessage(const std::string &functionName);

            //! Return the average (arithmetic mean) of the provided numbers
            /*!
             * \f$ average = \frac{1}{n} \sum\limits^{n}_{i = 1}{x_{i}} \f$
             *
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values in the collection of numbers
             */
            static double average(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return combinations of n taken as groups of k
            /*!
             * \param n The total number of elements
             * \param k The number of elements in each combination
             */
            static double computeCombinations(unsigned int n, unsigned int k);

            //! Return the covariance for the provided collections of values
            /*!
             * \param values1       The first collection of values
             * \param values2       The second collection of values
             * \param nrOfValues    The number of values in the collection of numbers
             */
            static double covariance(const std::vector<double> &values1, const std::vector<double> &values2,
                                     unsigned int nrOfValues);

            //! Return the geometric mean of the provided numbers
            /*!
             * \f$ geometricMean = e ^ {\frac{1}{n} \sum\limits_{i = 1}^{n}{log(x_{i})}} \f$
             *
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values in the collection of numbers
             */
            static double geometricMean(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the harmonic mean of the provided numbers
            /*!
             *  \f$ harmonicMean = \frac{n}{\sum\limits_{i = 1}^{n}{\frac{1}{x_{i}}}} \f$
             *
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values in the collection of numbers
             */
            static double harmonicMean(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the kurtosis of the provided numbers
            /*!
             * \f$ kurtosis = \frac{n (n + 1)}{(n - 1)(n - 2)(n - 3)} \left( \sum\limits_{i=1}^{n}{(\frac{x_i - mean}{stdev})^{4}} \right) - \frac{3 (n - 1)^{2}} {(n - 2) (n - 3)} \f$
             *
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values in the collection of numbers
             */
            static double kurtosis(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Compute the kurtosis first term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisFirstTerm(unsigned int nrOfValues);

            //! Compute the kurtosis middle term considering the given values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double computeKurtosisMiddleTerm(const std::vector<double> &values, unsigned int nrOfValues);

            //! Compute the kurtosis last term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisLastTerm(unsigned int nrOfValues);

            //! Return the maximum of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double maximum(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the median of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double median(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Compute the mode for the provided values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double mode(const std::vector<double> &values, unsigned int nrOfValues);

            //! Compute the mode for the provided values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double computeMode(const std::vector<double> &values, unsigned int nrOfValues);

            //! Return the minimum of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double minimum(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the p-th percentile of the provided set of values
            /*!
             * \param numbers       The collection of values
             * \param percentile    The p-th percentile
             * \param nrOfValues    The number of values
             */
            static double percentile(const std::vector<double> &numbers, double percentile, unsigned int nrOfValues);

            //! Return the product of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double product(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the q-th quartile of the provided set of values
            /*!
             * \param numbers       The collection of values
             * \param quartile      The q-th quartile
             * \param nrOfValues    The number of values
             */
            static double quartile(const std::vector<double> &numbers, double quartile, unsigned int nrOfValues);

            //! Compute the quartile for the given collection of values
            /*!
             * \param quartile      The quartile
             * \param values        The collection of values
             * \param nrOfValues    The number of values in the collection
             */
            static double computeQuartileValue(double quartile, const std::vector<double> &values, unsigned int nrOfValues);

            //! Return the skew of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double skew(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the skew first term considering the given values
            /*!
             * \param nrOfValues   The number of values
             */
            static double computeSkewFirstTerm(unsigned int nrOfValues);

            //! Return the skew last term considering the given values
            /*!
             * \param numbers       The collection of values
             * \param nrOfValues    The number of values
             */
            static double computeSkewLastTerm(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the standard deviation of the provided set of values
            /*!
             * \param numbers       The collection of values
             * \param nrOfValues    The number of values
             */
            static double standardDeviation(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the sum of the provided numbers
            /*!
             * \param numbers       The collection of numbers
             * \param nrOfValues    The number of values
             */
            static double sum(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Return the variance of the provided set of values
            /*!
             * \param numbers       The collection of values
             * \param nrOfValues    The number of values
             */
            static double variance(const std::vector<double> &numbers, unsigned int nrOfValues);

            //! Apply the operation on the given operands and throw an exception in case of overflow
            /*!
             * \param operation The operation
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operation, typename Operand>
            static Operand applyOperation(Operation operation, Operand operand1, Operand operand2) {
                resetOverflowUnderflowFlags();

                Operand result = operation(operand1, operand2);

                if (areOverflowUnderflowFlagsSet()) {
                    MS_throw(NumericException, ERR_OVERFLOW_UNDERFLOW);
                }

                return result;
            }

            //! Reset the overflow and underflow flags
            static void resetOverflowUnderflowFlags();

            //! Reset the overflow and underflow flags
            static bool areOverflowUnderflowFlagsSet();

            //! Check if the number and the base are positive real numbers, and if the base is different from 1
            /*!
             * \param number    The considered number
             * \param base      The considered base
             */
            static void validateLogNumberAndBase(double number, double base);

            //! Check if the number is a positive real number
            /*!
             * \param number    The considered number
             */
            static void validateLogNumber(double number);

            //! Check if the base is a positive real number different from 1
            /*!
             * \param base      The considered base
             */
            static void validateLogBase(double base);

            //! Check if the value of the percentile is between 0 and 100
            /*!
             * \param percentile    The percentile value
             */
            static void validatePercentile(double percentile);

            //! Check if the value of the quartile is either 25, 50 or 75
            /*!
             * \param quartile    The quartile value
             */
            static void validateQuartile(double quartile);

            //! Check if the given number is positive
            /*!
             * \param number The given number
             */
            template <typename T>
            static bool isPositive(T number) {
                return (number > 0);
            }

            //! Return the inverse of a number
            /*! If the number is equal to zero then a warning is displayed
             *  and the default value "0" is returned
             *
             * \param number    The given number
             */
            template <typename T>
            static T numberInverse(T number) {
                if (almostEqual(number, 0)) {
                    ConsolePrinter::printWarningMessage(WRN_NUMBER_INVERSE);

                    return 0;
                }

                return (1 / number);
            }


            // Constants
            static const std::string ERR_LOG_BASE_START;
            static const std::string ERR_LOG_BASE_END;
            static const std::string ERR_LOG_NUMBER_START;
            static const std::string ERR_LOG_NUMBER_END;

            static const std::string ERR_OVERFLOW_UNDERFLOW;

            static const std::string ERR_COMBINATIONS_START;
            static const std::string ERR_COMBINATIONS_MIDDLE;
            static const std::string ERR_COMBINATIONS_END;

            static const std::string ERR_PERCENTILE_VALUE_START;
            static const std::string ERR_PERCENTILE_VALUE_END;

            static const std::string ERR_QUARTILE_VALUE_START;
            static const std::string ERR_QUARTILE_VALUE_END;

            static const std::string WRN_NUMBER_INVERSE;

            static const std::string WRN_NOT_ENOUGH_VALUES_START;
            static const std::string WRN_NOT_ENOUGH_VALUES_END;

            static const std::string WRN_AVERAGE_FUNCTION_NAME;
            static const std::string WRN_COVARIANCE_FUNCTION_NAME;
            static const std::string WRN_GEOMETRIC_MEAN_FUNCTION_NAME;
            static const std::string WRN_HARMONIC_MEAN_FUNCTION_NAME;
            static const std::string WRN_KURTOSIS_FUNCTION_NAME;
            static const std::string WRN_MAXIMUM_FUNCTION_NAME;
            static const std::string WRN_MEDIAN_FUNCTION_NAME;
            static const std::string WRN_MODE_FUNCTION_NAME;
            static const std::string WRN_MINIMUM_FUNCTION_NAME;
            static const std::string WRN_PERCENTILE_FUNCTION_NAME;
            static const std::string WRN_PRODUCT_FUNCTION_NAME;
            static const std::string WRN_QUARTILE_FUNCTION_NAME;
            static const std::string WRN_SKEW_FUNCTION_NAME;
            static const std::string WRN_STANDARD_DEVIATION_FUNCTION_NAME;
            static const std::string WRN_SUM_FUNCTION_NAME;
            static const std::string WRN_VARIANCE_FUNCTION_NAME;

    };


    //! Functor representing an addition operation
    class AdditionOperation {

        public:

            //! Add the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 + operand2);
            }

    };

    //! Functor representing a division operation
    class DivisionOperation {

        public:

            //! Divide the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (
                    (Numeric::almostEqual(operand2, 0))
                        ? 0
                        : (operand1 / operand2)
                );
            }

    };

    //! Functor representing a multiplication operation
    class MultiplicationOperation {

        public:

            //! Multiply the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 * operand2);
            }

    };

    //! Functor representing a subtraction operation
    class SubtractionOperation {

        public:

            //! Subtract the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 - operand2);
            }

    };

};


#endif
