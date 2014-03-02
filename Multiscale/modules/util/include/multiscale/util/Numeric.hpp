#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include <algorithm>
#include <cfenv>
#include <cmath>
#include <limits>

using namespace std;


namespace multiscale {

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
                return (operand1 / operand2);
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

            //! Subtrace the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 - operand2);
            }

    };


    //! Class for manipulating numbers (shorts, ints, floats, doubles etc.)
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
             *      x1 + x2 + ... + xn
             * A = --------------------
             *              n
             *
             * \param numbers   The collection of numbers
             */
            static double average(const std::vector<double> &numbers);

            //! Return the geometric mean of the provided numbers
            /*!
             *            1
             * G = exp ( --- * (log(x1) + log(x2) + ... + log(xn)))
             *            n
             *
             * \param numbers   The collection of numbers
             */
            static double geometricMean(const std::vector<double> &numbers);

            //! Return the harmonic mean of the provided numbers
            /*!
             *                n
             * H = ------------------------
             *       1      1          1
             *      ---- + ---- ... + ----
             *       x1     x2         xn
             *
             * \param numbers   The collection of numbers
             */
            static double harmonicMean(const std::vector<double> &numbers);

            //! Return the kurtosis of the provided numbers
            /*!
             * K = (n)(n + 1) / ((n - 1)(n - 2)(n - 3)) * (\sum_{i=1}^{n}{((x_i - mean) / stdev) ^ 4}) -
             *     (3 * (n - 1) ^ 2) / ((n - 2) * (n - 3))
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

            //! Return the product of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double product(const std::vector<double> &numbers);

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

            //! Compute the kurtosis first term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisFirstTerm(int nrOfValues);

            //! Compute the kurtosis middle term considering the given values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double computeKurtosisMiddleTerm(const std::vector<double> &values, int nrOfValues);

            //! Compute the kurtosis last term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisLastTerm(int nrOfValues);

            //! Return the skew first term considering the given values
            /*!
             * \param numbers   The collection of numbers
             */
            static double computeSkewFirstTerm(int nrOfValues);

            //! Return the skew last term considering the given values
            /*!
             * \param numbers   The collection of numbers
             */
            static double computeSkewLastTerm(const std::vector<double> &numbers, int nrOfValues);

            //! Compute the mode for the provided values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double mode(const std::vector<double> &values, int nrOfValues);

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

                }

                return result;
            }

            //! Reset the overflow and underflow flags
            static void resetOverflowUnderflowFlags();

            //! Reset the overflow and underflow flags
            static bool areOverflowUnderflowFlagsSet();

            //! Check if the number and the base are positive real numbers, and the base is additionally different from 1
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

            //! Check if the given number is positive
            /*!
             * \param number The given number
             */
            template <typename T>
            static bool isPositive(T number) {
                return (number > 0);
            }


            // Constants
            static const std::string ERR_LOG_BASE_START;
            static const std::string ERR_LOG_BASE_END;
            static const std::string ERR_LOG_NUMBER_START;
            static const std::string ERR_LOG_NUMBER_END;

            static const std::string ERR_OVERFLOW_UNDERFLOW;

    };

};

#endif
