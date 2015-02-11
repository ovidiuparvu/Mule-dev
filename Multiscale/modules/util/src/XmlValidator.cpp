#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/XmlValidator.hpp"

XERCES_CPP_NAMESPACE_USE

using namespace multiscale;


bool XmlValidator::isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    std::string xmlErrorMessage;

    return isValidXmlFile(xmlFilepath, xmlSchemaPath, xmlErrorMessage);
}

bool XmlValidator::isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                  std::string &xmlErrorMessage) {
    XMLPlatformUtils::Initialize();

    bool isValid = isValidXmlPathAndFile(xmlFilepath, xmlSchemaPath, xmlErrorMessage);

    XMLPlatformUtils::Terminate();

    return isValid;
}

bool XmlValidator::isValidXmlPathAndFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                         std::string &xmlErrorMessage) {
    validateXmlFilepath(xmlFilepath);
    validateXmlSchemaPath(xmlSchemaPath);

    return verifyIfValidXmlFile(xmlFilepath, xmlSchemaPath, xmlErrorMessage);
}

bool XmlValidator::verifyIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                        std::string &xmlErrorMessage) {
    try {
        return checkIfValidXmlFile(xmlFilepath, xmlSchemaPath);
    } catch (const InvalidInputException &ex) {
        xmlErrorMessage = ex.rawMessage();
    }

    return false;
}

bool XmlValidator::checkIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    XercesDOMParser parser;

    loadParserSchema(xmlSchemaPath, parser);
    configureParser(parser);

    parser.parse(xmlFilepath.c_str());

    return (parser.getErrorCount() == 0);
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

void XmlValidator::loadParserSchema(const std::string &xmlSchemaPath, XercesDOMParser &parser) {
    if (parser.loadGrammar(xmlSchemaPath.c_str(), Grammar::SchemaGrammarType, true) == NULL) {
        MS_throw(InvalidInputException, ERR_SCHEMA_CONTENTS);
    }
}

void XmlValidator::configureParser(XercesDOMParser &parser) {
    XmlValidationErrorHandler errorHandler;

    parser.useCachedGrammarInParse(true);
    parser.setErrorHandler(&errorHandler);
    parser.setValidationScheme(XercesDOMParser::Val_Always);
    parser.setDoNamespaces(true);
    parser.setDoSchema(true);
    parser.setValidationConstraintFatal(true);
}

void XmlValidator::XmlValidationErrorHandler::warning(const SAXParseException &ex) {
    handleValidationException(ex);
}

void XmlValidator::XmlValidationErrorHandler::error(const SAXParseException &ex) {
    handleValidationException(ex);
}

void XmlValidator::XmlValidationErrorHandler::fatalError(const SAXParseException &ex) {
    handleValidationException(ex);
}

void XmlValidator::XmlValidationErrorHandler::resetErrors() {}

void XmlValidator::XmlValidationErrorHandler::handleValidationException(const SAXParseException &ex) {
    std::string exceptionMessage = constructExceptionMessage(ex);

    MS_throw(InvalidInputException, exceptionMessage);
}

std::string XmlValidator::XmlValidationErrorHandler::constructExceptionMessage(const SAXParseException &ex) {
    return (
        ERR_EXCEPTION_BEGIN_MSG +
        ERR_EXCEPTION_LINE_MSG +
        StringManipulator::toString(ex.getLineNumber()) +
        ERR_EXCEPTION_COLUMN_MSG +
        StringManipulator::toString(ex.getColumnNumber()) +
        ERR_EXCEPTION_MIDDLE_MSG +
        std::string(XMLString::transcode(ex.getMessage())) +
        ERR_EXCEPTION_END_MSG
    );
}

// Constants
const std::string XmlValidator::ERR_INVALID_XML_FILEPATH    = "The provided xml file path is invalid. Please change.";
const std::string XmlValidator::ERR_INVALID_SCHEMA_FILEPATH = "The provided xml schema file path is invalid. Please change.";

const std::string XmlValidator::ERR_SCHEMA_CONTENTS = "The provided xml schema is invalid. Please verify the xml schema contents.";

const std::string XmlValidator::XmlValidationErrorHandler::ERR_EXCEPTION_BEGIN_MSG  = "An error occurred at ";

const std::string XmlValidator::XmlValidationErrorHandler::ERR_EXCEPTION_LINE_MSG   = "line ";
const std::string XmlValidator::XmlValidationErrorHandler::ERR_EXCEPTION_COLUMN_MSG = ", column ";
const std::string XmlValidator::XmlValidationErrorHandler::ERR_EXCEPTION_MIDDLE_MSG = " and the error message is \"";

const std::string XmlValidator::XmlValidationErrorHandler::ERR_EXCEPTION_END_MSG = "\".";
