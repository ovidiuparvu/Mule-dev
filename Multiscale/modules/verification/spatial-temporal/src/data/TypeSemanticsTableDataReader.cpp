#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/data/TypeSemanticsTableDataReader.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

using namespace multiscale::verification;


TypeSemanticsTableDataReader::TypeSemanticsTableDataReader() : nrOfDescribedSemanticCriteria(0) {}

TypeSemanticsTable TypeSemanticsTableDataReader::read(const std::string &inputFilePath) {
    this->inputFilePath = inputFilePath;

    return read();
}

TypeSemanticsTable TypeSemanticsTableDataReader::read() {
    if (!Filesystem::isValidFilePath(inputFilePath, TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_INPUT_FILE_PATH_BEGIN +
            inputFilePath +
            ERR_INVALID_INPUT_FILE_PATH_END
        );
    }

    return readFromValidFile();
}

TypeSemanticsTable TypeSemanticsTableDataReader::readFromValidFile() {
    if (!XmlValidator::isValidXmlFile(inputFilePath, TYPE_SEMANTICS_TABLE_XSD_PATH)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN +
            inputFilePath +
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END
        );
    }

    return readFromValidXmlFile();
}

TypeSemanticsTable TypeSemanticsTableDataReader::readFromValidXmlFile() {
    pt::ptree propertyTree;

    read_xml(inputFilePath, propertyTree, pt::xml_parser::trim_whitespace);

    return constructTypeSemanticsTable(propertyTree);
}

TypeSemanticsTable TypeSemanticsTableDataReader::constructTypeSemanticsTable(const pt::ptree &propertyTree) {
    TypeSemanticsTable typeSemanticsTable;

    processSemanticCriteriaDescription(propertyTree);
    addSemanticTypesToTable(propertyTree, typeSemanticsTable);

    return typeSemanticsTable;
}

void TypeSemanticsTableDataReader::processSemanticCriteriaDescription(const pt::ptree &propertyTree) {
    semanticCriteriaDescription     = propertyTree.get<std::string>(LABEL_SEMANTIC_CRITERIA_DESCRIPTION);
    nrOfDescribedSemanticCriteria   = StringManipulator::count(
                                          SEMANTIC_CRITERIA_SEPARATOR,
                                          semanticCriteriaDescription
                                      ) + 1;
}

void TypeSemanticsTableDataReader::addSemanticTypesToTable(const pt::ptree &propertyTree,
                                                           TypeSemanticsTable &typeSemanticsTable) {
    pt::ptree semanticTypesTree = propertyTree.get_child(LABEL_SEMANTIC_TYPES);

    // Process each type stored in the tree
    for (const auto &typeTreePair : semanticTypesTree) {
        addSemanticTypeToTable(typeTreePair.second, typeSemanticsTable);
    }
}

void TypeSemanticsTableDataReader::addSemanticTypeToTable(const pt::ptree &semanticTypeTree,
                                                          TypeSemanticsTable &typeSemanticsTable) {
    std::string     typeSemantics = semanticTypeTree.get<std::string>(LABEL_SEMANTIC_TYPE_SEMANTICS);
    unsigned long   typeValue     = semanticTypeTree.get<unsigned long>(LABEL_SEMANTIC_TYPE_VALUE);

    if (isNoUndefinedSemanticCriteriaValue(typeSemantics)) {
        typeSemanticsTable.addMappingFromSemanticCriteriaValuesToType(typeSemantics, typeValue);
    } else {
        MS_throw(
            SpatialTemporalException,
            ERR_UNDEFINED_SEMANTIC_CRITERIA_BEGIN +
            semanticCriteriaDescription +
            ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE1 +
            inputFilePath +
            ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE2 +
            typeSemantics +
            ERR_UNDEFINED_SEMANTIC_CRITERIA_END
        );
    }
}

bool TypeSemanticsTableDataReader::isNoUndefinedSemanticCriteriaValue(const std::string &semanticCriteriaValues) {
    unsigned long nrOfSemanticCriteria = StringManipulator::count(
                                             SEMANTIC_CRITERIA_SEPARATOR, semanticCriteriaValues
                                         ) + 1;

    return (nrOfSemanticCriteria <= nrOfDescribedSemanticCriteria);
}


// Constants
const std::string TypeSemanticsTableDataReader::LABEL_TYPE_SEMANTICS_TABLE          = "typeSemanticsTable";
const std::string TypeSemanticsTableDataReader::LABEL_SEMANTIC_CRITERIA_DESCRIPTION = LABEL_TYPE_SEMANTICS_TABLE + ".semanticCriteria.<xmlattr>.description";
const std::string TypeSemanticsTableDataReader::LABEL_SEMANTIC_TYPES                = LABEL_TYPE_SEMANTICS_TABLE + ".semanticTypes";

const std::string TypeSemanticsTableDataReader::LABEL_SEMANTIC_TYPE             = "type";
const std::string TypeSemanticsTableDataReader::LABEL_SEMANTIC_TYPE_SEMANTICS   = "<xmlattr>.semantics";
const std::string TypeSemanticsTableDataReader::LABEL_SEMANTIC_TYPE_VALUE       = "<xmlattr>.value";

const char TypeSemanticsTableDataReader::SEMANTIC_CRITERIA_SEPARATOR = '.';

const std::string TypeSemanticsTableDataReader::TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION = ".xml";
const std::string TypeSemanticsTableDataReader::TYPE_SEMANTICS_TABLE_XSD_PATH             = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/verification/spatial-temporal/schema/type_semantics_table.xsd";

const std::string TypeSemanticsTableDataReader::ERR_INVALID_INPUT_FILE_PATH_BEGIN   = "The provided input file path (";
const std::string TypeSemanticsTableDataReader::ERR_INVALID_INPUT_FILE_PATH_END     = ") does not point to a regular file with the required extension (" + TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION + "). Please change.";

const std::string TypeSemanticsTableDataReader::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN    = "The provided xml input file (";
const std::string TypeSemanticsTableDataReader::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END      = ") is invalid relative to the xsd file (" + TYPE_SEMANTICS_TABLE_XSD_PATH + ").";

const std::string TypeSemanticsTableDataReader::ERR_UNDEFINED_SEMANTIC_CRITERIA_BEGIN   = "The number of semantic criteria provided in the semantic description (";
const std::string TypeSemanticsTableDataReader::ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE1 = ") of input file (" ;
const std::string TypeSemanticsTableDataReader::ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE2 = ") is smaller than the number of semantic criteria considered in one of the semantic types definitions (" ;
const std::string TypeSemanticsTableDataReader::ERR_UNDEFINED_SEMANTIC_CRITERIA_END     = "). Please extend the semantic criteria description accordingly.";
