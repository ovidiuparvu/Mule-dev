#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/util/XmlValidator.hpp"

#include <iostream>

using namespace multiscale;


// Check if the given xml file is valid according to the xml schema
void checkIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaFilepath) {
    std::cout << "The xml file is valid according to the given schema: "
              << (((XmlValidator::isValidXmlFile(xmlFilepath, xmlSchemaFilepath)) == true)
                  ? "true" : "false")
              << std::endl;
}

// Validate xml file considering the provided arguments
void validateXmlFile(int argc, char **argv) {
    try {
        std::string xmlFilePath     = std::string(argv[1]);
        std::string xmlSchemaPath   = std::string(argv[2]);

        checkIfValidXmlFile(xmlFilePath, xmlSchemaPath);
    } catch (const std::exception &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Main function
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: XmlValidatorSample <path-to-xml> <path-to-xml-schema>" << std::endl;

        return 1;
    } else {
        validateXmlFile(argc, argv);

        return EXEC_SUCCESS_CODE;
    }
}
