#include <stdio.h>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/validators/common/Grammar.hpp>

// TODO: Remove

XERCES_CPP_NAMESPACE_USE

void ValidateSchema(const char* schemaFilePath, const char* xmlFilePath)
{
    XercesDOMParser domParser;
    if (domParser.loadGrammar(schemaFilePath, Grammar::SchemaGrammarType) == NULL)
    {
        fprintf(stderr, "couldn't load schema\n");
        return;
    }

    domParser.setValidationScheme(XercesDOMParser::Val_Auto);
    domParser.setDoNamespaces(true);
    domParser.setDoSchema(true);
    domParser.setValidationConstraintFatal(true);

    domParser.parse(xmlFilePath);
    if (domParser.getErrorCount() == 0)
        printf("XML file validated against the schema successfully\n");
    else
        printf("XML file doesn't conform to the schema\n");
}

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf("SchemaValidator <schema file> <xml file>\n");
        return 0;
    }

    XMLPlatformUtils::Initialize();

    ValidateSchema(argv[1], argv[2]);

    XMLPlatformUtils::Terminate();

    return 0;
}
