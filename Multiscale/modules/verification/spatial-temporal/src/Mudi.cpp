/**
 * This program is used for multidimensional model checking
 *
 * Author: Ovidiu Parvu
 * Date created: 16.03.2014
 * Date modified: 18.03.2014
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelCheckerFactory.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

#include <boost/program_options.hpp>
#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;

namespace po = boost::program_options;


// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &allowedOptions) {
    cout << "USAGE: " << endl
         << "\tMudi <required-arguments> [<optional-arguments>]" << endl
         << endl;
    cout << allowedOptions << endl;
}

// Check if help information was requested
bool isHelpInformationRequested(const po::variables_map &vm,
                                const po::options_description &allowedOptions) {
    if (vm.count("help")) {
        printHelpInformation(vm, allowedOptions);

        return true;
    }

    return false;
}

// Initialise the options descriptions
po::options_description initialiseAllowedOptions() {
    po::options_description allowedOptions ("");
    po::options_description requiredOptions("REQUIRED");
    po::options_description optionalOptions("OPTIONAL");

    requiredOptions.add_options()("logic-queries,q"            , po::value<string>()->required()           , "the path to the spatial-temporal queries input file\n")
                                 ("spatial-temporal-traces,t"  , po::value<string>()->required()           , "the path to the folder containing spatial-temporal traces\n")
                                 ("extra-evaluation-time,e"    , po::value<unsigned long>()->required()    , "the maximum number of minutes the application can wait before finishing evaluation\n");

    optionalOptions.add_options()("help,h"                     , "display help message\n")
                                 ("extra-evaluation-program,p" , po::value<string>()                       , "the program which will be executed whenever extra evaluation (and input traces) is required\n")
                                 ("verbose,v"                  , po::bool_switch()                         , "if this flag is set detailed evaluation results will be displayed\n");

    allowedOptions.add(requiredOptions).add(optionalOptions);

    return allowedOptions;
}

// Check if any unrecognized options were entered
bool areUnrecognizedOptions(const po::parsed_options &parsedOptions) {
    std::vector<std::string> unrecognizedOptions = po::collect_unrecognized(parsedOptions.options,
                                                                            po::include_positional);

    return (unrecognizedOptions.size() > 0);
}

// Parse and store the command line options
bool parseAndStoreOptions(int argc, char** argv, const po::options_description &usageDescription,
                          po::variables_map &vm) {
    po::parsed_options parsedOptions = po::command_line_parser(argc, argv).
                                       options(usageDescription).allow_unregistered().run();

    po::store(parsedOptions, vm);

    bool wasHelpOptionEntered       = isHelpInformationRequested(vm, usageDescription);
    bool existUnrecognizedOptions   = areUnrecognizedOptions(parsedOptions);

    po::notify(vm);

    return ((!wasHelpOptionEntered) && (!existUnrecognizedOptions));
}


// Initialise the arguments configuration
bool areValidCommandLineArguments(int argc, char** argv, po::variables_map &vm) {
    po::options_description allowedOptions = initialiseAllowedOptions();

    return parseAndStoreOptions(argc, argv, allowedOptions, vm);
}

// Print error message if wrong parameters are provided
void printWrongParameters() {
    cout << ERR_MSG << "Wrong input arguments provided." << endl;
    cout << "Run the program with the argument \"--help\" for more information." << endl;
}

// Update values of all optional parameters whenever values have been provided
void updateOptionalParameterValues(std::string &extraEvaluationProgramPath, bool &shouldVerboseDetailedResults,
                                   const po::variables_map &vm) {
    if (vm.count("verbose")) {
        shouldVerboseDetailedResults = vm["verbose"].as<bool>();
    }

    if (vm.count("extra-evaluation-program")) {
        extraEvaluationProgramPath = vm["extra-evaluation-program"].as<string>();
    }
}

// Update values of all required parameters
void updateRequiredParameterValues(string &logicQueriesFilepath, string &tracesFolderPath,
                                   unsigned long &extraEvaluationTime, const po::variables_map &vm) {
    logicQueriesFilepath  = vm["logic-queries"].as<string>();
    tracesFolderPath      = vm["spatial-temporal-traces"].as<string>();
    extraEvaluationTime   = vm["extra-evaluation-time"].as<unsigned long>();
}

// Get the needed parameters
bool areValidParameters(string &logicQueriesFilepath, string &tracesFolderPath, unsigned long &extraEvaluationTime,
                        string &extraEvaluationProgram, bool &shouldVerboseDetailedResults, int argc, char** argv) {
    po::variables_map vm;

    // Check if the user wants to print help information
    if (!areValidCommandLineArguments(argc, argv, vm)) {
        return false;
    }

    updateRequiredParameterValues(logicQueriesFilepath, tracesFolderPath, extraEvaluationTime, vm);
    updateOptionalParameterValues(extraEvaluationProgram, shouldVerboseDetailedResults, vm);

    return true;
}

// Print the model checking initialisation messages
void printModelCheckingInitialisationMessages(const string &logicQueriesFilePath,
                                              const string &tracesFolderPath,
                                              unsigned long extraEvaluationTime) {
    ModelCheckingOutputWriter::printIntroductionMessage  ("Frequency", "None");
    ModelCheckingOutputWriter::printInitialisationMessage(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime);
}

// Run the model checking operations
void runModelCheckers(const string &logicQueriesFilePath, const string &tracesFolderPath,
                      unsigned long extraEvaluationTime, const string &extraEvaluationProgramPath,
                      bool shouldVerboseDetailedResults) {
    std::shared_ptr<FrequencyModelCheckerFactory> modelCheckerFactory = make_shared<FrequencyModelCheckerFactory>();

    ModelCheckingManager manager(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime);

    manager.setExtraEvaluationProgramPath(extraEvaluationProgramPath);
    manager.setShouldPrintDetailedEvaluation(shouldVerboseDetailedResults);

    manager.runModelCheckingTasks(modelCheckerFactory);
}

// Run the model checking operations
void runModelCheckers(int argc, char **argv) {
    string logicQueriesFilePath;
    string tracesFolderPath;

    unsigned long extraEvaluationTime;
    string        extraEvaluationProgramPath;

    bool shouldVerboseDetailedResults;

    if (areValidParameters(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime,
                           extraEvaluationProgramPath, shouldVerboseDetailedResults, argc, argv)) {
        printModelCheckingInitialisationMessages(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime);
        runModelCheckers(logicQueriesFilePath, tracesFolderPath, extraEvaluationTime,
                         extraEvaluationProgramPath, shouldVerboseDetailedResults);
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
