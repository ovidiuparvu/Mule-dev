#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"

#include <iostream>
#include <string>

using namespace multiscale;
using namespace multiscale::verification;


// Print the contents of the provided type semantics table
void printTypeSemanticsTableContents(const TypeSemanticsTable &typeSemanticsTable) {
    std::cout << "The contents of the type semantics table: " << std::endl << std::endl;

    for (auto it = typeSemanticsTable.getBeginIterator(); it != typeSemanticsTable.getEndIterator(); it++) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
}

// Read the type semantics table from the provided input file
void readTypeSemanticsTable(const std::string &inputFile, TypeSemanticsTable &typeSemanticsTable) {
    typeSemanticsTable.readTableFromFile(inputFile);
}

// Read the type semantics table from the provided input file
void readAndPrintTypeSemanticsTable(const std::string &inputFile) {
    try {
        TypeSemanticsTable typeSemanticsTable;

        readTypeSemanticsTable(inputFile, typeSemanticsTable);
        printTypeSemanticsTableContents(typeSemanticsTable);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: TypeSemanticsTableDataReaderSample <input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    readAndPrintTypeSemanticsTable(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
