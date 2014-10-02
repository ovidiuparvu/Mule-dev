#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Analyse patterns considering timeseries data provided in the input file
int analysePatterns(const std::string &inputFilePath) {
    std::string logicStatement;
    AbstractSyntaxTree result;
    TemporalDataReader reader;

    SpatialTemporalTrace trace = reader.read(inputFilePath);

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\tA pattern analysis logic property evaluator...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Please enter a multidimensional multiscale logical query (or \"q\" to exit):" << std::endl
        << std::endl;

    while (getline(std::cin, logicStatement)) {
        if (logicStatement.compare("q") == 0) {
            break;
        }

        Parser parser(logicStatement);

        try {
            if (parser.parse(result)) {
                std::cout << "-----------------------------------------------------" << std::endl;
                std::cout << " Parsing succeeded"
                          << " and the AST evaluates to " << (result.evaluate(trace) ? "true" : "false")
                          << "!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            } else {
                std::cout << "-----------------------------------------------------" << std::endl;
                std::cout << " Parsing failed!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            }
        } catch(const exception &e) {
            ExceptionHandler::printDetailedErrorMessage(e);

            return EXEC_ERR_CODE;
        } catch(...) {
            cerr << "Exception of unknown type!" << std::endl;

            return EXEC_ERR_CODE;
        }
    }

    return EXEC_ERR_CODE;
}

// Main program
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: PatternAnalysisSample <timeseries-input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    try {
        return analysePatterns(std::string(argv[1]));
    } catch(const exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);
    } catch(...) {
        cerr << "Exception of unknown type!" << std::endl;
    }

    return EXEC_ERR_CODE;
}
