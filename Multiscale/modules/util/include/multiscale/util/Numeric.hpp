#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;


namespace multiscale {

    //! Class for manipulating numbers (shorts, ints, floats, doubles etc.)
    class Numeric {

        private:

            static double epsilon;  /*!< Value of epsilon used to compare two real numbers */

        public:

            //! Check if the first number is greater than or equal to the second number
            static bool greaterOrEqual(double number1, double number2);

            //! Check if the first number is less than or equal to the second number
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

            //! Return the maximum of the provided numbers
            static double maximum(double number1, double number2, double number3);

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

        private:

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

    };

};

#endif
