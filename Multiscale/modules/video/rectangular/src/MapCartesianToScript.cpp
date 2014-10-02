/**
 * This program is used for scaling concentrations from a grid and generating the
 * gnuplot script for visualising the grid.
 *
 * FORMAT OF INPUT FILE:
 * First line contains the numbers N and M, where N is the number of rows in the grid and
 * M is the number of columns in the grid.
 * Subsequent lines of the input file contain the normalised concentrations of the positions
 * in the grid. Each concentration has a value between 0 and 1.
 *
 * FORMAT OF SCRIPT:
 * The script will generate the gnuplot script corresponding to the input file.
 *
 * GNUPLOT version: 4.6
 * BOOST version: 1.52.0
 *
 * Author: Ovidiu Parvu
 * Date created: 07.02.2013
 * Date modified: 07.02.2013
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/video/rectangular/CartesianToConcentrationsConverter.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace std;
using namespace multiscale;
using namespace multiscale::video;

namespace po = boost::program_options;


// Initialise the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("input-file,i", po::value<string>(), "provide the path to the input file\n")
                                  ("output-file,o",po::value<string>(), "provide the path of the output file (without extension)\n");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, usageDescription), vm);
    po::notify(vm);
    return vm;
}

// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &usageDescription) {
    cout << usageDescription << endl;
}

// Print error message if wrong parameters are provided
void printWrongParameters() {
    cout << ERR_MSG << "Wrong input arguments provided." << endl;
    cout << "Run the program with the argument \"--help\" for more information." << endl;
}

// Get the needed parameters
bool areValidParameters(string &inputFilepath, string &outputFilename, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file"))) {
        inputFilepath  = vm["input-file"].as<string>();
        outputFilename = vm["output-file"].as<string>();

        return true;
    }

    return false;
}

// Main function
int main(int argc, char** argv) {
    string inputFilePath;
    string outputFilepath;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, argc, argv)) {
            CartesianToConcentrationsConverter converter(inputFilePath, outputFilepath);

            converter.convert();
        } else {
            printWrongParameters();
        }
    } catch(const exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        cerr << "Exception of unknown type!" << endl;
    }

    return EXEC_SUCCESS_CODE;
}
