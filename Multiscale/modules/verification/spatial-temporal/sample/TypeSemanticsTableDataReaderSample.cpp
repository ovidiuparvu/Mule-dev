#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/data/TypeSemanticsTableDataReader.hpp"

#include <iostream>
#include <string>

using namespace multiscale;
using namespace multiscale::verification;


// Print the contents of the provided type semantics table
void printTypeSemanticsTableContents(const TypeSemanticsTable &table) {
    std::cout << "The contents of the type semantics table: " << std::endl << std::endl;

    for (auto it = table.getBeginIterator(); it != table.getEndIterator(); it++) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
}

// Read the type semantics table from the provided input file
void readTypeSemanticsTable(const std::string &inputFile, TypeSemanticsTable &table) {
    try {
        table = TypeSemanticsTableDataReader().read(inputFile);

        printTypeSemanticsTableContents(table);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Read the type semantics table from the provided input file
void readTypeSemanticsTable(const std::string &inputFile) {
    TypeSemanticsTable typeSemanticsTable;

    readTypeSemanticsTable(inputFile, typeSemanticsTable);
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: TypeSemanticsTableDataReaderSample <input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    readTypeSemanticsTable(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
