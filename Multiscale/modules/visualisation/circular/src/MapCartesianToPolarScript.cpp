/**
 * This program is used for mapping a grid from the cartesian to the
 * polar coordinate system.
 *
 * Snoopy, the simulator used by us, cannot handle polar coordinates. Therefore, we will
 * discretise the polar space and map it onto a matrix which Snoopy can handle. Then,
 * the results need to be mapped back to the polar representation and this is what this
 * program does. It maps the grid containing the output of Snoopy (i.e. concentrations in each
 * cell of the grid) to the polar coordinate system.
 *
 * More details about the mapping of the circles represented in the polar coordinate system
 * to the grid used by Snoopy can be found in the PowerPoint presentation "PhaseVariation" or
 * the ".pdf" file generated from the presentation.
 *
 * FORMAT OF INPUT FILE:
 * First line contains the numbers N and M, where N is the number of rows in the grid and
 * M is the number of columns in the grid.
 * Subsequent lines of the input file contain the normalised concentrations of the positions
 * in the grid. Each concentration has a value between 0 and 1.
 *
 * FORMAT OF OUTPUT FILE:
 * Each line corresponds to an annular sector and contains information about the
 * starting radius, ending radius, starting angle, ending angle and the concentration
 * of bacteria.
 *
 * FORMAT OF SCRIPT:
 * The script will generate the gnuplot script corresponding to the input file.
 *
 * GNUPLOT version: 4.6
 * BOOST version: 1.52.0
 *
 * Author: Ovidiu Pârvu
 * Date created: 21.12.2012
 * Date modified: 09.01.2013
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/visualisation/circular/CartesianToPolarConverter.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace multiscale;
using namespace multiscale::visualisation;

namespace po = boost::program_options;


// Initialize the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("input-file,i", po::value<std::string>(), "provide the path to the input file\n")
                                  ("output-file,o",po::value<std::string>(), "provide the path of the output file (without extension)\n")
                                  ("output-type,t", po::value<int>()->default_value(0), "Specify the type of the output:\n"
                                                                                        "\t 0 - output as script.\n"
                                                                                        "\t 1 - output as file.\n\n"
                                                                                        "Remark: Output is implicitly script.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, usageDescription), vm);
    po::notify(vm);
    return vm;
}

// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &usageDescription) {
    std::cout << usageDescription << std::endl;
}

// Print error message if wrong parameters are provided
void printWrongParameters() {
    std::cout << ERR_MSG << "Wrong input arguments provided." << std::endl;
    std::cout << "Run the program with the argument \"--help\" for more information." << std::endl;
}

// Check if the output type is valid
bool isValidOutputType(const po::variables_map &vm, bool &isScript) {
    if (vm.count("output-type")) {
        int outputType = vm["output-type"].as<int>();

        if ((outputType < 0) || (outputType > 1)) {
            std::cout << ERR_MSG
                    << "Parameter output-type can have either the value 0 or 1."
                    << std::endl;

            return false;
        }

        if (outputType == 1) {
            isScript = false;
        }
    }

    return true;
}

// Get the needed parameters
bool areValidParameters(std::string &inputFilepath, std::string &outputFilename, bool &isScript, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    isScript = true;

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file"))) {
        inputFilepath  = vm["input-file"].as<std::string>();
        outputFilename = vm["output-file"].as<std::string>();

        return isValidOutputType(vm, isScript);
    }

    return false;
}

// Main function
int main(int argc, char** argv) {
    std::string inputFilePath;
    std::string outputFilepath;
    bool   isScript = true;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, isScript, argc, argv)) {
            CartesianToPolarConverter converter(inputFilePath, outputFilepath);

            converter.convert(isScript);
        } else {
            printWrongParameters();
        }
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXEC_SUCCESS_CODE;
}
