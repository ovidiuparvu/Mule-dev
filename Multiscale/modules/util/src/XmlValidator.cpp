#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/XmlValidator.hpp"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE

using namespace multiscale;


bool XmlValidator::isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    XMLPlatformUtils::Initialize();

    bool isValue = verifyIfValidXmlFile(xmlFilepath, xmlSchemaPath);

    XMLPlatformUtils::Terminate();

    return isValue;
}

bool XmlValidator::verifyIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    validateXmlFilepath(xmlFilepath);
    validateXmlSchemaPath(xmlSchemaPath);

    return checkIfValidXmlFile(xmlFilepath, xmlSchemaPath);
}

bool XmlValidator::checkIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    XercesDOMParser domParser;

    if (domParser.loadGrammar(xmlSchemaPath.c_str(), Grammar::SchemaGrammarType) == NULL) {
        MS_throw(InvalidInputException, ERR_SCHEMA_CONTENTS);
    }

    domParser.setValidationScheme(XercesDOMParser::Val_Auto);
    domParser.setDoNamespaces(true);
    domParser.setDoSchema(true);
    domParser.setValidationConstraintFatal(true);

    domParser.parse(xmlFilepath.c_str());

    return (domParser.getErrorCount() == 0);
}

void XmlValidator::validateXmlFilepath(const std::string &xmlFilepath) {
    if (!Filesystem::isValidFilePath(xmlFilepath)) {
        MS_throw(InvalidInputException, ERR_INVALID_XML_FILEPATH);
    }
}

void XmlValidator::validateXmlSchemaPath(const std::string &xmlSchemaPath) {
    if (!Filesystem::isValidFilePath(xmlSchemaPath)) {
        MS_throw(InvalidInputException, ERR_INVALID_SCHEMA_FILEPATH);
    }
}


// Constants
const std::string XmlValidator::ERR_INVALID_XML_FILEPATH    = "The provided xml file path is invalid. Please change.";
const std::string XmlValidator::ERR_INVALID_SCHEMA_FILEPATH = "The provided xml schema file path is invalid. Please change.";

const std::string XmlValidator::ERR_SCHEMA_CONTENTS = "The provided xml schema is invalid. Please verify the xml schema contents.";
