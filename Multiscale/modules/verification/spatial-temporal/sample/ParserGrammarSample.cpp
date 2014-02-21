#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;
using namespace std;


//  Main program
int main(int argc, char **argv) {
    string test;
    AbstractSyntaxTree result;

    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\tA multidimensional logical query parser...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";

    cout
        << "Please enter a multidimensional logical query (or \"q\" to exit):" << endl
        << endl;


    while (getline(cin, test)) {
        if (test.compare("q") == 0) {
            break;
        }

        Parser parser(test);

        try {
            if (parser.parse(result)) {
                cout << "-----------------------------------------------------" << endl;
                cout << " Parsing succeeded"
//                   << " and the AST evaluates to " << (result.evaluate() ? "true" : "false")
                     << "!" << endl;
                cout << "-----------------------------------------------------" << endl;
            } else {
                cout << "-----------------------------------------------------" << endl;
                cout << " Parsing failed!" << endl;
                cout << "-----------------------------------------------------" << endl;
            }
        } catch(const exception &e) {
            ExceptionHandler::printErrorMessage(e);

            return ERR_CODE;
        } catch(...) {
            cerr << "Exception of unknown type!" << endl;
        }
    }

    return -1;
}
