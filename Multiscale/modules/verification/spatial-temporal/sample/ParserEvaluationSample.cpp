#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Initialise the provided trace
void initialiseTrace(SpatialTemporalTrace &trace) {
    std::vector<TimePoint> timePoints;

    for (int i = 0; i <= 11; i++) {
        timePoints.push_back(TimePoint(i));
        timePoints[i].addNumericStateVariable("B", 3);
    }

    timePoints[0].addNumericStateVariable("A", 4);
    timePoints[1].addNumericStateVariable("A", 5);
    timePoints[2].addNumericStateVariable("A", 6);
    timePoints[3].addNumericStateVariable("A", 10);
    timePoints[4].addNumericStateVariable("A", 8);
    timePoints[5].addNumericStateVariable("A", 6);
    timePoints[6].addNumericStateVariable("A", 4);
    timePoints[7].addNumericStateVariable("A", 1);
    timePoints[8].addNumericStateVariable("A", 5);
    timePoints[9].addNumericStateVariable("A", 7);
    timePoints[10].addNumericStateVariable("A", 9);
    timePoints[11].addNumericStateVariable("A", 12);

    for (TimePoint &timePoint : timePoints) {
        trace.addTimePoint(timePoint);
    }
}

//  Main program
int main(int argc, char **argv) {
    std::string test;
    SpatialTemporalTrace trace;
    AbstractSyntaxTree result;

    initialiseTrace(trace);

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\tA multidimensional logical query parser and evaluator...\n\n";
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
