/**
 * This program is used for converting one .csv file to "n" input files for the
 * MapCartesianToPolar program
 *
 * The purpose of this program is to help simulate the "Phase Variation" case
 * study using a polar coordinate system instead of a cartesian one. It is our
 * belief that the polar approach will better reflect what is observed by biologists
 * in vitro.
 *
 * FORMAT OF INPUT FILE:
 * Typical .csv file containing time series information
 *
 * FORMAT OF OUTPUT FILE:
 * Check format of input files for MapCartesianToPolar program
 *
 * Author: Ovidiu Parvu
 * Date created: 13.01.2013
 * Date modified: 13.01.2013
 */

#include "../include/CsvToInputFilesConverter.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace std;
using namespace multiscale;

namespace po = boost::program_options;

#define ERR_CODE 1
#define ERR_MSG  "An error occurred: "


// Initialise the arguments configuration
po::variables_map initArgumentsConfig(po::options_description usageDescription, int argc, char** argv) {
	usageDescription.add_options()("help,h", "display help message\n")
						          ("input-file,i", po::value<string>(), "provide the path to the input file\n")
						          ("output-file,o", po::value<string>(), "provide the path of the output file (without extension)\n")
						          ("nr-concentric-circles,c", po::value<unsigned int>(), "provide the number of concentric circles\n")
						          ("nr-sectors,s", po::value<unsigned int>(), "provide the number of sectors\n")
						          ("nr-concentrations-position,p", po::value<unsigned int>()->default_value(1), "provide the number of concentrations for each position\n");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, usageDescription), vm);
	po::notify(vm);
	return vm;
}

// Print help message if needed
void printIfHelp(const po::variables_map& vm,
		const po::options_description& usageDescription) {
	if (vm.count("help")) {
		cout << usageDescription << endl;
	}
}

// Print error message if no arguments are provided
void printIfNoArguments(int argc) {
	if (argc == 1) {
		cout << ERR_MSG << "No input arguments provided." << endl;
		cout << "Run the program with the argument \"--help\" for more information." << endl;
	}
}

// Check if the number of concentrations for one position is valid
bool isValidNrOfConcentrationsForPosition(const po::variables_map& vm, unsigned int& nrOfConcentrationsForPosition) {
	if (vm.count("nr-concentrations-position")) {
		nrOfConcentrationsForPosition = vm["nr-concentrations-position"].as<unsigned int>();

		if (nrOfConcentrationsForPosition == 0) {
			cout << ERR_MSG
					<< "Parameter nr-concentrations-position must be greater than 0."
					<< endl;

			return false;
		}
	}

	return true;
}

// Get the needed parameters
bool areParameters(string& inputFilepath, string& outputFilename, unsigned int& nrOfConcentricCircles,
		           unsigned int& nrOfSectors, unsigned int& nrOfConcentrationsForPosition,
		           int argc, char** argv) {
	po::options_description usageDescription("Usage");

	po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

	printIfHelp(vm, usageDescription);

	if ((vm.count("input-file")) && (vm.count("output-file")) &&
		(vm.count("nr-concentric-circles")) && (vm.count("nr-sectors"))) {
		inputFilepath  = vm["input-file"].as<string>();
		outputFilename = vm["output-file"].as<string>();

		nrOfConcentricCircles = vm["nr-concentric-circles"].as<unsigned int>();
		nrOfSectors			  = vm["nr-sectors"].as<unsigned int>();

		if (isValidNrOfConcentrationsForPosition(vm, nrOfConcentrationsForPosition)) {
			return true;
		}
	}

	printIfNoArguments(argc);

	return false;
}

// Main function
int main(int argc, char** argv) {
	string inputFilePath;
	string outputFilepath;

	unsigned int nrOfConcentricCircles;
	unsigned int nrOfSectors;
	unsigned int nrOfConcentrationsForPosition;

    try {
    	if (areParameters(inputFilePath, outputFilepath, nrOfConcentricCircles,
    			          nrOfSectors, nrOfConcentrationsForPosition, argc, argv)) {
    		CsvToInputFilesConverter converter(inputFilePath, outputFilepath, nrOfConcentricCircles,
    										   nrOfSectors, nrOfConcentrationsForPosition);

    		converter.convert();
    	}
    } catch(const string& e) {
        cerr << ERR_MSG << e << endl;

        return ERR_CODE;
    } catch(const char* e) {
            cerr << ERR_MSG << e << endl;

            return ERR_CODE;
    } catch(exception& e) {
        cerr << ERR_MSG << e.what() << endl;

        return ERR_CODE;
    } catch(...) {
            cerr << "Exception of unknown type!" << endl;
        }

    return 0;
}
