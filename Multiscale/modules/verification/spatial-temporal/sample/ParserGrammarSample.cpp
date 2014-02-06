#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;
using namespace std;


//  Main program
int main(int argc, char **argv) {
    string test;
    ConstraintAttribute result;

    cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tA logical query parser...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";

	cout
		<< "Give me a logical query of the form :" << endl
		<< "\t{subset} OR {filteredSubset}" << endl
		<< endl;

	getline(cin, test);

    Parser parser(test);

    try {
        if (parser.parse(result)) {
			cout << "-----------------------------------------------------" << endl;
			cout << " Parsing succeeded and the AST evaluates to "
	             << (result.evaluate() ? "true" : "false") << "!" << endl;
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

    return -1;
}
