#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ScaleAndSubsystemEvaluator.hpp"

using namespace multiscale::verification;


void ScaleAndSubsystemEvaluator::validate(const std::string &scaleAndSubsystem,
                                          const TypeSemanticsTable &typeSemanticsTable) {
    // If the scale and subsystem exists in the type semantics table
    // or has the default value
    if ((typeSemanticsTable.existsSemanticType(scaleAndSubsystem)) ||
        (scaleAndSubsystem.compare(ScaleAndSubsystem::DEFAULT_VALUE) == 0)) {
        // Do nothing
    } else {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_SCALE_AND_SUBSYSTEM_BEGIN +
            scaleAndSubsystem +
            ERR_INVALID_SCALE_AND_SUBSYSTEM_END
        );
    }
}


// Constants
const std::string ScaleAndSubsystemEvaluator::ERR_INVALID_SCALE_AND_SUBSYSTEM_BEGIN = "The scale and subsystem (";
const std::string ScaleAndSubsystemEvaluator::ERR_INVALID_SCALE_AND_SUBSYSTEM_END   = ") specified in the logic statement does not exist in the type semantics table.";
