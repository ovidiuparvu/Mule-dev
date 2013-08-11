#include "multiscale/util/Numeric.hpp"

using namespace multiscale;


double Numeric::epsilon = 1E-7;


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
