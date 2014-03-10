#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/XmlValidator.hpp"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE

using namespace multiscale;


bool XmlValidator::isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath) {
    XercesDOMParser domParser;

    if (domParser.loadGrammar(xmlSchemaPath.c_str(), Grammar::SchemaGrammarType) == NULL) {
        MS_throw(InvalidInputException, ERR_OPEN_SCHEMA_FILE);
    }

    domParser.setValidationScheme(XercesDOMParser::Val_Auto);
    domParser.setDoNamespaces(true);
    domParser.setDoSchema(true);
    domParser.setValidationConstraintFatal(true);

    domParser.parse(xmlFilepath.c_str());

    return (domParser.getErrorCount() == 0);
}


// Constants
const std::string XmlValidator::ERR_OPEN_SCHEMA_FILE = "The provided xml schema is invalid. Please verify the xml schema contents and/or file path.";
