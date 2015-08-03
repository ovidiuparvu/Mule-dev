#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/FileReader.hpp"

#include <iostream>

using namespace multiscale;


// Print file line by line
void printFileLineByLine(const std::vector<std::string> &lines) {
    for (const std::string &line : lines) {
        std::cout << line << std::endl;
    }
}

// Main function
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: FileReaderSample <input-file-path> <input-file-extension>." << std::endl;

        return EXEC_ERR_CODE;
    }

    try {
        // Read file line by line
        std::vector<std::string> lines = FileReader::readFileLineByLine(std::string(argv[1]), std::string(argv[2]));

        // Print out the file line by line
        printFileLineByLine(lines);
    } catch (const MultiscaleException &ex) {
        std::cerr << ex.what() << std::endl;

        return EXEC_ERR_CODE;
    }

    return EXEC_SUCCESS_CODE;
}
