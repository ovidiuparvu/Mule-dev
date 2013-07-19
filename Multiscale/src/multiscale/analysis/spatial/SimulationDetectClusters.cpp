/**
 * This program is used for detecting clusters in grayscale 2D images considering a rectangular geometry
 *
 * FORMAT OF INPUT FILE:
 * Images generated with RectangularGeometryViewer
 *
 * FORMAT OF OUTPUT FILE:
 * If in debug mode, then display results. Else print them in a .csv/xml file.
 *
 * Author: Ovidiu Parvu
 * Date created: 03.07.2013
 * Date modified: 05.07.2013
 */

#include "multiscale/analysis/spatial/cluster/SimulationClusterDetector.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace std;
using namespace multiscale::analysis;

namespace po = boost::program_options;

#define ERR_CODE 1
#define ERR_MSG  "An error occurred: "


// Initialise the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("height,e", po::value<unsigned int>(), "provide the height of the grid (number of rows)\n")
                                  ("width,w", po::value<unsigned int>(), "provide the width of the grid (number of columns)\n")
                                  ("input-file,i", po::value<string>(), "provide the path to the input file\n")
                                  ("output-file,o", po::value<string>(), "provide the path of the output file (without extension)\n")
                                  ("debug-mode,d", po::value<bool>()->implicit_value(false), "start the program in debug mode\n");

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
bool areValidParameters(string &inputFilepath, string &outputFilename, bool &debugFlag, unsigned int &height,
                        unsigned int &width, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file")) && (vm.count("height")) && (vm.count("width"))) {
        inputFilepath  = vm["input-file"].as<string>();
        outputFilename = vm["output-file"].as<string>();

        height = vm["height"].as<unsigned int>();
        width = vm["width"].as<unsigned int>();

        if (vm.count("debug-mode")) {
            debugFlag = vm["debug-mode"].as<bool>();
        }

        return true;
    }

    return false;
}

// Main function
int main(int argc, char** argv) {
    string inputFilePath;
    string outputFilepath;

    bool debugFlag = false;

    unsigned int height;
    unsigned int width;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, debugFlag, height, width, argc, argv)) {
            Mat image = RectangularMatFactory().createFromViewerImage(inputFilePath);

            SimulationClusterDetector detector(height, width, debugFlag);

            detector.detect(image);
            detector.outputResults(outputFilepath);
        } else {
            printWrongParameters();
        }
    } catch(const string &e) {
        cerr << ERR_MSG << e << endl;

        return ERR_CODE;
    } catch(const char* e) {
        cerr << ERR_MSG << e << endl;

        return ERR_CODE;
    } catch(exception &e) {
        cerr << ERR_MSG << e.what() << endl;

        return ERR_CODE;
    } catch(...) {
        cerr << "Exception of unknown type!" << endl;
    }

    return 0;
}
