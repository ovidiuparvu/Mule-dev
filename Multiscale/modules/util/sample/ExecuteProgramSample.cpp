#include "multiscale/util/OperatingSystem.hpp"

#include <iostream>

using namespace multiscale;


// Main function
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ExecuteProgramSample <path-to-executable>" << std::endl;

        return 1;
    }

    OperatingSystem::executeProgram(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
