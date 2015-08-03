#include "multiscale/core/Multiscale.hpp"
#include "multiscale/util/Timer.hpp"

#include <iostream>

using namespace multiscale;


int main(int argc, char** argv) {
    double number1 = 12312312123.123;
    double number2 = 42524253.132;

    Timer::start();

    double result = number1 - number2;

    double executionTime = Timer::stop();

    std::cout << number1 << " - " << number2 << " = " << result
              << " (Execution time: " << executionTime << " nanoseconds)." << std::endl;

    return EXEC_SUCCESS_CODE;
}
