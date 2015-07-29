#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ScaleAndSubsystemEvaluator.hpp"

using namespace multiscale::verification;


void ScaleAndSubsystemEvaluator::validateScaleAndSubsystem(const std::string &scaleAndSubsystem,
                                                           const MultiscaleArchitectureGraph
                                                               &multiscaleArchitectureGraph) {
    // If the scale and subsystem exists in the multiscale architecture graph
    // or has the default value
    if ((scaleAndSubsystem.compare(ScaleAndSubsystem::DEFAULT_VALUE) == 0) ||
        (multiscaleArchitectureGraph.existsScaleAndSubsystem(scaleAndSubsystem))) {
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

bool ScaleAndSubsystemEvaluator::areEqualScalesAndSubsystems(const std::string &lhsScaleAndSubsystem,
                                                             const std::string &rhsScaleAndSubsystem) {
    return (
        lhsScaleAndSubsystem.compare(rhsScaleAndSubsystem) == 0
    );
}


// Constants
const std::string ScaleAndSubsystemEvaluator::ERR_INVALID_SCALE_AND_SUBSYSTEM_BEGIN = "The scale and subsystem (";
const std::string ScaleAndSubsystemEvaluator::ERR_INVALID_SCALE_AND_SUBSYSTEM_END   = ") specified in the logic statement does not exist in the multiscale architecture graph.";
