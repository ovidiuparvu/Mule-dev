#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace multiscale;
using namespace multiscale::verification;


// Print the parsing result
void printParsingResult(Parser &parser, AbstractSyntaxTree &parsingResult) {
    try {
        std::cout << std::endl
                  << "is syntactically correct: "
                  << (parser.parse(parsingResult) ? "true" : "false")
                  << "."
                  << std::endl << std::endl;
    } catch (const InvalidInputException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Print the provided queries
void printQueries(const std::vector<std::string> &queries) {
    Parser parser("");
    AbstractSyntaxTree parsingResult;

    for (const auto &query : queries) {
        parser.setLogicalQuery(query);

        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "\t New query" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;

        std::cout << query << std::endl;

        printParsingResult(parser, parsingResult);
    }
}

// Read logic queries from the provided file
void readQueriesFromFile(const std::string &path) {
    try {
        LogicPropertyDataReader reader;

        std::vector<std::string> queries = reader.readLogicPropertiesFromFile(path);

        printQueries(queries);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: LogicPropertyDataReader <input-file>" << std::endl;

        return 1;
    }

    readQueriesFromFile(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
