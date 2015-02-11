#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SemanticType.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SemanticTypeEvaluator.hpp"

using namespace multiscale::verification;


void SemanticTypeEvaluator::validate(const std::string &semanticType,
                                     const TypeSemanticsTable &typeSemanticsTable) {
    // If the semantic type exists in the type semantics table
    // or has the default value
    if ((typeSemanticsTable.existsSemanticType(semanticType)) ||
        (semanticType.compare(SemanticType::DEFAULT_VALUE) == 0)) {
        // Do nothing
    } else {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_SEMANTIC_TYPE_BEGIN +
            semanticType +
            ERR_INVALID_SEMANTIC_TYPE_END
        );
    }
}


// Constants
const std::string SemanticTypeEvaluator::ERR_INVALID_SEMANTIC_TYPE_BEGIN = "The semantic type (";
const std::string SemanticTypeEvaluator::ERR_INVALID_SEMANTIC_TYPE_END   = ") specified in the logic statement does not exist in the type semantics table.";
