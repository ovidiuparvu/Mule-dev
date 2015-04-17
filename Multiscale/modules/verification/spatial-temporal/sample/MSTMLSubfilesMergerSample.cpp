/**
 * This program is used for merging MSTML subfiles from a folder into a single MSTML file.
 *
 * Author: Ovidiu Parvu
 * Date created: 12.11.2014
 * Date modified: 12.11.2014
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/data/MSTMLSubfilesMerger.hpp"

#include <boost/program_options.hpp>

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;

namespace po = boost::program_options;


// Enumeration which records the possible command line arguments validation result
enum class CmdLineArgsValidationResult {
    Invalid         = 0,    /*!< Invalid command line arguments */
    HelpRequested      ,    /*!< The help flag was specified */
    Valid                   /*!< Valid command line arguments */
};


// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &usageDescription) {
    std::cout << usageDescription << std::endl;
}

// Print error message if wrong parameters are provided
void printInvalidCommandLineArguments() {
    std::cout << ERR_MSG << "Wrong input arguments provided." << std::endl;
    std::cout << "Run the program with the argument \"--help\" for more information." << std::endl;
}

// Initialize the command line arguments configuration
po::options_description initCommandLineArgumentsConfig() {
    // Provide a title for the usage options description
    po::options_description usageDescription("Usage");

    // Configure which command line arguments are optional and/or required
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("mstml-subfiles-folder,m"    , po::value<std::string>(), "provide the path to the MSTML subfiles folder\n")
                                  ("timepoints-values-file,t"   , po::value<std::string>(), "provide the path to the timepoints values input file\n")
                                  ("mstml-output-file,o"        , po::value<std::string>(), "provide the path to the MSTML output file\n");

    return usageDescription;
}

// Parse the command line arguments and store the values, if valid, in a variables map
po::variables_map parseCommandLineArguments(int argc, char **argv,
                                            const po::options_description &usageDescription) {
    po::variables_map variablesMap;

    po::store(po::parse_command_line(argc, argv, usageDescription), variablesMap);
    po::notify(variablesMap);

    return variablesMap;
}

// Check if the provided command line arguments are valid
CmdLineArgsValidationResult areValidParameters(std::string &mstmlSubfilesFolderPath,
                                               std::string &timepointsValuesFilePath,
                                               std::string &mstmlOutputFilePath,
                                               int argc, char** argv) {
    // Initialize the command line arguments configuration
    po::options_description usageDescription = initCommandLineArgumentsConfig();

    // Parse the command line arguments
    po::variables_map variablesMap = parseCommandLineArguments(argc, argv, usageDescription);

    // If the user requests to see help information print the relevant information and return "HelpRequested"
    if (variablesMap.count("help")) {
        printHelpInformation(variablesMap, usageDescription);

        return CmdLineArgsValidationResult::HelpRequested;
    }

    // If the provided command line arguments are valid return "Valid"
    if (
        (variablesMap.count("mstml-subfiles-folder")) &&
        (variablesMap.count("timepoints-values-file")) &&
        (variablesMap.count("mstml-output-file"))
    ) {
        mstmlSubfilesFolderPath     = variablesMap["mstml-subfiles-folder"].as<std::string>();
        timepointsValuesFilePath    = variablesMap["timepoints-values-file"].as<std::string>();
        mstmlOutputFilePath         = variablesMap["mstml-output-file"].as<std::string>();

        return CmdLineArgsValidationResult::Valid;
    }

    // Otherwise return "Invalid"
    return CmdLineArgsValidationResult::Invalid;
}

// Merge the MSTML subfiles considering the provided paths
void mergeMSTMLSubfiles(const std::string &mstmlSubfilesFolderPath,
                        const std::string &timepointsValuesFilePath,
                        const std::string &mstmlOutputFilePath) {
    MSTMLSubfilesMerger mstmlSubfilesMerger(mstmlSubfilesFolderPath, timepointsValuesFilePath);

    mstmlSubfilesMerger.mergeMSTMLSubfiles();
    mstmlSubfilesMerger.outputResultingMSTMLFile(mstmlOutputFilePath);
}

// Merge the MSTML subfiles considering the provided command line arguments
void mergeMSTMLSubfiles(int argc, char **argv) {
    std::string mstmlSubfilesFolderPath;
    std::string timepointsValuesFilePath;
    std::string mstmlOutputFilePath;

    // Check if the command line arguments are valid and initialize the provided strings accordingly
    CmdLineArgsValidationResult cmdLineArgsValidationResult
        = areValidParameters(
              mstmlSubfilesFolderPath, timepointsValuesFilePath, mstmlOutputFilePath,
              argc, argv
          );

    // If the command line arguments are valid merge MSTML subfiles
    switch (cmdLineArgsValidationResult) {
        case CmdLineArgsValidationResult::Invalid:
            printInvalidCommandLineArguments();
            break;

        case CmdLineArgsValidationResult::Valid:
            mergeMSTMLSubfiles(mstmlSubfilesFolderPath, timepointsValuesFilePath, mstmlOutputFilePath);
            break;

        default:
            // Do nothing;
            break;
    }
}

// Main function
int main(int argc, char** argv) {
    try {
        mergeMSTMLSubfiles(argc, argv);
    } catch(const MultiscaleException &e) {
        ExceptionHandler::printRawErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;

        return EXEC_ERR_CODE;
    }

    return EXEC_SUCCESS_CODE;
}
