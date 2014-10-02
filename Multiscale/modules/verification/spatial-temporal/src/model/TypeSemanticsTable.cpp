#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"

using namespace multiscale::verification;


TypeSemanticsTable::TypeSemanticsTable() {}

TypeSemanticsTable::~TypeSemanticsTable() {}

void TypeSemanticsTable::addMappingFromSemanticCriteriaValuesToType(const std::string &semanticCriteriaValues,
                                                                    unsigned long type) {
    table[semanticCriteriaValues] = type;
}

std::map<std::string, unsigned long>::const_iterator TypeSemanticsTable::getBeginIterator() const {
    return table.cbegin();
}

std::map<std::string, unsigned long>::const_iterator TypeSemanticsTable::getEndIterator() const {
    return table.cend();
}

unsigned long TypeSemanticsTable::getTypeOfSemanticCriteriaValues(const std::string &semanticCriteriaValues) {
    if (existsEntryInTableForSemanticCriteriaValues(semanticCriteriaValues)) {
        return table[semanticCriteriaValues];
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

bool TypeSemanticsTable::existsEntryInTableForSemanticCriteriaValues(const std::string &semanticCriteriaValues) {
    return (
        table.find(semanticCriteriaValues) != table.end()
    );
}

bool TypeSemanticsTable::areDefaultSemanticCriteriaValues(const std::string &semanticCriteriaValues) {
    return (
        semanticCriteriaValues.compare(DEFAULT_SEMANTIC_CRITERIA_VALUE) == 0
    );
}


// Constants
const std::string   TypeSemanticsTable::DEFAULT_SEMANTIC_CRITERIA_VALUE = "0";
const unsigned long TypeSemanticsTable::DEFAULT_TYPE_VALUE              = 0;

const std::string   TypeSemanticsTable::ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_BEGIN   = "There is no type semantics table entry for the provided semantic criteria values (";
const std::string   TypeSemanticsTable::ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_END     = "). Please change.";
