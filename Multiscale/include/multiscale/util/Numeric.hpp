#ifndef NUMERIC_HPP_
#define NUMERIC_HPP_

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

    };

};

#endif
