#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>

using namespace std;
using namespace multiscale;

int main() {
    cout << RGBColourGenerator().generate(0, 1, 0.5);
    cout << RGBColourGenerator().generate(0, 1, 0.25);
    cout << RGBColourGenerator().generate(0, 1, 0.75);
    cout << RGBColourGenerator().generate(0, 1, 1);

    return 0;
}
