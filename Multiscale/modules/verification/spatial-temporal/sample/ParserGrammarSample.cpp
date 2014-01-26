#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;
using namespace std;


//  Main program
int main(int argc, char **argv) {
    string test;
    string result;

    cin >> test;

    Parser parser(test);

    try {
        parser.parse(result);
    } catch(const exception &e) {
        ExceptionHandler::printErrorMessage(e);

        return ERR_CODE;
    } catch(...) {
        cerr << "Exception of unknown type!" << endl;
    }

    return -1;
}
