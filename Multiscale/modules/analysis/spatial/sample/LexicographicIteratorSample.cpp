#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"

#include <iostream>

using namespace multiscale;

// Main function

int main() {
    LexicographicNumberIterator it(1023);

    while (it.hasNext()) {
        std::cout << it.number() << std::endl;
    }
}
