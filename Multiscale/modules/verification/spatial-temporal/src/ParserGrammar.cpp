#include "multiscale/verification/spatial-temporal/ParserGrammar.hpp"

#include <iostream>

using namespace std;
using namespace multiscale::verification;
using boost::spirit::ascii::space;


///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    string test;
    string result;

    std::cin >> test;

    ParserGrammar<std::string::const_iterator> grammar;

    std::string::const_iterator iter = test.begin();
    std::string::const_iterator end = test.end();

    bool r = phrase_parse(iter, end, grammar, space, result);

    std::cout << result;

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        std::cout << result << endl;

        return 0;
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
        return 1;
    }
}
