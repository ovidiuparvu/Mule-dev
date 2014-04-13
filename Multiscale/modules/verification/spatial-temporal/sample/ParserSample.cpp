#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


//  Main program
int main(int argc, char **argv) {
    std::string test;
    SpatialTemporalTrace trace;
    AbstractSyntaxTree result;

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\tA multidimensional logical query parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Please enter a multidimensional logical query (or \"q\" to exit):" << std::endl
        << std::endl;


    while (getline(std::cin, test)) {
        if (test.compare("q") == 0) {
            break;
        }

        Parser parser(test);

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
            ExceptionHandler::printErrorMessage(e);

            return EXEC_ERR_CODE;
        } catch(...) {
            cerr << "Exception of unknown type!" << std::endl;
        }
    }

    return -1;
}
