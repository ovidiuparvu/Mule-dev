#include "multiscale/core/Multiscale.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>

using namespace multiscale;


int main() {
    std::cout << RGBColourGenerator().generate(0, 1, 0.5);
    std::cout << RGBColourGenerator().generate(0, 1, 0.25);
    std::cout << RGBColourGenerator().generate(0, 1, 0.75);
    std::cout << RGBColourGenerator().generate(0, 1, 1);

    return EXEC_SUCCESS_CODE;
}
