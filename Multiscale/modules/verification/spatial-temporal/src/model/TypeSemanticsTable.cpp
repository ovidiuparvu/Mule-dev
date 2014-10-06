#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/XmlValidator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SemanticType.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"

using namespace multiscale::verification;


TypeSemanticsTable::TypeSemanticsTable() : nrOfDescribedSemanticCriteria(0) {}

TypeSemanticsTable::~TypeSemanticsTable() {}

void TypeSemanticsTable::readTableFromFile(const std::string &inputFilePath) {
    this->inputFilePath = inputFilePath;

    // Read the type semantics table from the input file
    read();
}

std::map<std::string, unsigned long>::const_iterator TypeSemanticsTable::getBeginIterator() const {
    return table.cbegin();
}

std::map<std::string, unsigned long>::const_iterator TypeSemanticsTable::getEndIterator() const {
    return table.cend();
}

unsigned long TypeSemanticsTable::getTypeOfSemanticCriteriaValues(const std::string
                                                                  &semanticCriteriaValues) const {
    if (existsEntryInTableForSemanticCriteriaValues(semanticCriteriaValues)) {
        return table.at(semanticCriteriaValues);
    } else if (areDefaultSemanticCriteriaValues(semanticCriteriaValues)) {
        return DEFAULT_TYPE_VALUE;
    } else {
        MS_throw(
            SpatialTemporalException,
            ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_BEGIN +
            semanticCriteriaValues +
            ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_END
        );
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0;
}

void TypeSemanticsTable::read() {
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

void TypeSemanticsTable::readFromValidFile() {
    std::string xmlErrorMessage;

    if (!XmlValidator::isValidXmlFile(inputFilePath, TYPE_SEMANTICS_TABLE_XSD_PATH, xmlErrorMessage)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN +
            inputFilePath +
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END +
            xmlErrorMessage
        );
    }

    return readFromValidXmlFile();
}

void TypeSemanticsTable::readFromValidXmlFile() {
    pt::ptree propertyTree;

    read_xml(inputFilePath, propertyTree, pt::xml_parser::trim_whitespace);

    return constructTypeSemanticsTable(propertyTree);
}

void TypeSemanticsTable::constructTypeSemanticsTable(const pt::ptree &propertyTree) {
    processSemanticCriteriaDescription(propertyTree);
    addSemanticTypesToTable(propertyTree);
}

void TypeSemanticsTable::processSemanticCriteriaDescription(const pt::ptree &propertyTree) {
    semanticCriteriaDescription     = propertyTree.get<std::string>(LABEL_SEMANTIC_CRITERIA_DESCRIPTION);
    nrOfDescribedSemanticCriteria   = StringManipulator::count(
                                          SEMANTIC_CRITERIA_SEPARATOR,
                                          semanticCriteriaDescription
                                      ) + 1;
}

void TypeSemanticsTable::addSemanticTypesToTable(const pt::ptree &propertyTree) {
    pt::ptree semanticTypesTree = propertyTree.get_child(LABEL_SEMANTIC_TYPES);

    // Process each type stored in the tree
    for (const auto &typeTreePair : semanticTypesTree) {
        addSemanticTypeToTable(typeTreePair.second);
    }
}

void TypeSemanticsTable::addSemanticTypeToTable(const pt::ptree &semanticTypeTree) {
    std::string     typeSemantics = semanticTypeTree.get<std::string>(LABEL_SEMANTIC_TYPE_SEMANTICS);
    unsigned long   typeValue     = semanticTypeTree.get<unsigned long>(LABEL_SEMANTIC_TYPE_VALUE);

    if (isNoUndefinedSemanticCriteriaValue(typeSemantics)) {
        addTableEntry(typeSemantics, typeValue);
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

void TypeSemanticsTable::addTableEntry(const std::string &semanticCriteriaValues,
                                       unsigned long type) {
    table[semanticCriteriaValues] = type;
}

bool TypeSemanticsTable::isNoUndefinedSemanticCriteriaValue(const std::string &semanticCriteriaValues) {
    unsigned long nrOfSemanticCriteria = StringManipulator::count(
                                             SEMANTIC_CRITERIA_SEPARATOR, semanticCriteriaValues
                                         ) + 1;

    return (nrOfSemanticCriteria <= nrOfDescribedSemanticCriteria);
}

bool TypeSemanticsTable::existsEntryInTableForSemanticCriteriaValues(const std::string
                                                                     &semanticCriteriaValues) const {
    return (
        table.find(semanticCriteriaValues) != table.end()
    );
}

bool TypeSemanticsTable::areDefaultSemanticCriteriaValues(const std::string
                                                          &semanticCriteriaValues) const {
    return (
        semanticCriteriaValues.compare(SemanticType::DEFAULT_VALUE) == 0
    );
}


// Constants
const unsigned long TypeSemanticsTable::DEFAULT_TYPE_VALUE  = 0;

const std::string TypeSemanticsTable::LABEL_TYPE_SEMANTICS_TABLE          = "typeSemanticsTable";
const std::string TypeSemanticsTable::LABEL_SEMANTIC_CRITERIA_DESCRIPTION = LABEL_TYPE_SEMANTICS_TABLE + ".semanticCriteria.<xmlattr>.description";
const std::string TypeSemanticsTable::LABEL_SEMANTIC_TYPES                = LABEL_TYPE_SEMANTICS_TABLE + ".semanticTypes";

const std::string TypeSemanticsTable::LABEL_SEMANTIC_TYPE             = "type";
const std::string TypeSemanticsTable::LABEL_SEMANTIC_TYPE_SEMANTICS   = "<xmlattr>.semantics";
const std::string TypeSemanticsTable::LABEL_SEMANTIC_TYPE_VALUE       = "<xmlattr>.value";

const char TypeSemanticsTable::SEMANTIC_CRITERIA_SEPARATOR = '.';

const std::string TypeSemanticsTable::TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION = ".xml";
const std::string TypeSemanticsTable::TYPE_SEMANTICS_TABLE_XSD_PATH             = "/usr/local/share/mule/config/verification/spatial-temporal/schema/type_semantics_table.xsd";

const std::string TypeSemanticsTable::ERR_INVALID_INPUT_FILE_PATH_BEGIN   = "The provided input file path (";
const std::string TypeSemanticsTable::ERR_INVALID_INPUT_FILE_PATH_END     = ") does not point to a regular file with the required extension (" + TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION + "). Please change.";

const std::string TypeSemanticsTable::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN    = "The provided xml input file (";
const std::string TypeSemanticsTable::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END      = ") is invalid relative to the xsd file (" + TYPE_SEMANTICS_TABLE_XSD_PATH + "). ";

const std::string TypeSemanticsTable::ERR_UNDEFINED_SEMANTIC_CRITERIA_BEGIN   = "The number of semantic criteria provided in the semantic description (";
const std::string TypeSemanticsTable::ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE1 = ") of input file (" ;
const std::string TypeSemanticsTable::ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE2 = ") is smaller than the number of semantic criteria considered in one of the semantic types definitions (" ;
const std::string TypeSemanticsTable::ERR_UNDEFINED_SEMANTIC_CRITERIA_END     = "). Please extend the semantic criteria description accordingly.";

const std::string   TypeSemanticsTable::ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_BEGIN   = "There is no type semantics table entry for the provided semantic criteria values (";
const std::string   TypeSemanticsTable::ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_END     = "). Please change.";
