/**
 * This program is used for converting one .csv file containing the positions of entities
 * to "n" input files for the MapCartesianToScript program
 *
 * FORMAT OF INPUT FILE:
 * .csv file containing time series information regarding the position of entities
 *
 * FORMAT OF OUTPUT FILE:
 * Check format of input files for MapCartesianToScript program
 *
 * Author: Ovidiu Pârvu
 * Date created: 22.07.2013
 * Date modified: 22.07.2013
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/visualisation/rectangular/RectangularEntityCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
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
                                  ("output-file,o", po::value<std::string>(), "provide the path of the output file (without extension)\n")
                                  ("height,e", po::value<unsigned int>(), "provide the height of the grid (number of rows)\n")
                                  ("width,w", po::value<unsigned int>(), "provide the width of the grid (number of columns)\n")
                                  ("nr-entities,n", po::value<unsigned int>(), "provide the number of entities observed in the simulation\n")
                                  ("max-pileup,m", po::value<unsigned int>(), "provide the maximum number of entities which can occupy a grid position at the same time\n")
                                  ("lexicographic-iterator,l", "use lexicographic number iterator for numbering the columns of the .csv file\n");

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

// Set the number iterator type to lexicographic if requested
void setNumberIteratorType(const po::variables_map &vm, NumberIteratorType &numberIteratorType) {
    numberIteratorType = multiscale::LEXICOGRAPHIC;
}

// Get the needed parameters
bool areValidParameters(std::string &inputFilepath, std::string &outputFilename, unsigned int &height,
                   unsigned int &width, unsigned int &nrOfEntities, unsigned int &maxPileup,
                   NumberIteratorType &numberIteratorType, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file")) &&
        (vm.count("height")) && (vm.count("width")) &&
        (vm.count("nr-entities")) && (vm.count("max-pileup"))) {
        inputFilepath  = vm["input-file"].as<std::string>();
        outputFilename = vm["output-file"].as<std::string>();

        height = vm["height"].as<unsigned int>();
        width  = vm["width"].as<unsigned int>();

        nrOfEntities = vm["nr-entities"].as<unsigned int>();
        maxPileup = vm["max-pileup"].as<unsigned int>();

        if (vm.count("lexicographic-iterator")) {
            setNumberIteratorType(vm, numberIteratorType);
        }

        return true;
    }

    return false;
}

// Main function
int main(int argc, char** argv) {
    std::string inputFilePath;
    std::string outputFilepath;

    unsigned int height;
    unsigned int width;

    unsigned int nrOfEntities;
    unsigned int maxPileup;

    NumberIteratorType numberIteratorType = multiscale::STANDARD;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, height, width, nrOfEntities, maxPileup,
                               numberIteratorType, argc, argv)) {
            RectangularEntityCsvToInputFilesConverter converter(inputFilePath, outputFilepath,
                                                                height, width, nrOfEntities,
                                                                maxPileup, numberIteratorType);

            converter.convert();
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
