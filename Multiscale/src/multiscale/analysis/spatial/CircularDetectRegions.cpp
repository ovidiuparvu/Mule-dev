/**
 * This program is used for detecting regions of high intensity in grayscale images considering a circular geometry
 *
 * FORMAT OF INPUT FILE:
 * Images generated with CircularGeometryViewer
 *
 * FORMAT OF OUTPUT FILE:
 * If in debug mode, then display results. Else print them to a .csv/xml file.
 *
 * Author: Ovidiu Parvu
 * Date created: 18.03.2013
 * Date modified: 27.03.2013
 */

#include "multiscale/analysis/spatial/RegionDetector.hpp"
#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"

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
bool areValidParameters(string &inputFilepath, string &outputFilename, bool &debugFlag, int argc, char** argv) {
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

    try {
        if (areValidParameters(inputFilePath, outputFilepath, debugFlag, argc, argv)) {
            Mat image = CircularMatFactory().createFromViewerImage(inputFilePath);

            RegionDetector detector(image, outputFilepath, debugFlag);

            detector.detect();
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
