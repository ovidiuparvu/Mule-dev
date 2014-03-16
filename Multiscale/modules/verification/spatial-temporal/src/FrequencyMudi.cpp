/**
 * This program is used for frequency MUltiDImensional model checking
 *
 * Author: Ovidiu Parvu
 * Date created: 16.03.2014
 * Date modified: 16.03.2014
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;

namespace po = boost::program_options;


// Initialise the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("logic-queries,q", po::value<string>(), "provide the path to the spatial-temporal queries input file\n")
                                  ("spatial-temporal-traces,t", po::value<string>(), "provide the path to the folder containing spatial-temporal traces\n")
                                  ("extra-evaluation-time,e", po::value<unsigned long>(), "provide the maximum number of minutes the application can wait before finishing evaluation\n");

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

// Check if help information was requested
bool isHelpInformationRequested(const po::variables_map &vm,
                                const po::options_description &usageDescription) {
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return true;
    }

    return false;
}

// Check if all required parameters were given as input
bool areValidParameters(string &logicQueriesFilepath, string &tracesFolderPath,
                        unsigned long &extraEvaluationTime, const po::variables_map &vm) {
    if ((vm.count("logic-queries")) && (vm.count("spatial-temporal-traces")) &&
        (vm.count("extra-evaluation-time"))) {
        logicQueriesFilepath  = vm["logic-queries"].as<string>();
        tracesFolderPath      = vm["spatial-temporal-traces"].as<string>();
        extraEvaluationTime   = vm["extra-evaluation-time"].as<unsigned long>();

        return true;
    }

    return false;
}

// Get the needed parameters
bool areValidParameters(string &logicQueriesFilepath, string &tracesFolderPath,
                        unsigned long &extraEvaluationTime, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (isHelpInformationRequested(vm, usageDescription)) {
        return false;
    }

    // Check if the given parameters are correct
    if (areValidParameters(logicQueriesFilepath, tracesFolderPath,
                           extraEvaluationTime, vm)) {
        return true;
    }

    return false;
}

// Run the model checking operations
void runModelCheckers(int argc, char **argv) {
    string logicQueriesFilePath;
    string tracesFolderPath;

    unsigned long extraEvaluationTime;

    if (areValidParameters(logicQueriesFilePath, tracesFolderPath,
                           extraEvaluationTime, argc, argv)) {
        std::shared_ptr<FrequencyModelCheckerFactory> modelCheckerFactory = make_shared<FrequencyModelCheckerFactory>();

        ModelCheckingManager manager(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime);

        manager.runModelCheckingTasks(modelCheckerFactory);
    } else {
        printWrongParameters();
    }
}

// Main function
int main(int argc, char** argv) {
    try {
        runModelCheckers(argc, argv);
    } catch(const exception &e) {
        ExceptionHandler::printErrorMessage(e);

        return ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;

        return ERR_CODE;
    }

    return 0;
}
