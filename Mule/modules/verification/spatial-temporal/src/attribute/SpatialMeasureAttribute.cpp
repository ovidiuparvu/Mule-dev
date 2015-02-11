#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

#include <limits>

using namespace multiscale::verification;
using namespace multiscale::verification::spatialmeasure;


void
multiscale::verification::spatialmeasure::validateSpatialMeasureType(const SpatialMeasureType &spatialMeasureType) {
    if (spatialMeasureType == SpatialMeasureType::NrOfSpatialMeasureTypeEntries) {
        MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }
}

void
multiscale::verification::spatialmeasure::validateSpatialMeasureTypeIndex(const std::size_t &spatialMeasureTypeIndex) {
    if (spatialMeasureTypeIndex >= NR_SPATIAL_MEASURE_TYPES) {
        MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }
}

size_t
multiscale::verification::spatialmeasure::computeSpatialMeasureTypeIndex(const SpatialMeasureType &spatialMeasureType) {
    validateSpatialMeasureType(spatialMeasureType);

    return static_cast<size_t>(spatialMeasureType);
}

SpatialMeasureType
multiscale::verification::spatialmeasure::computeSpatialMeasureType(const std::size_t &spatialMeasureTypeIndex) {
    validateSpatialMeasureTypeIndex(spatialMeasureTypeIndex);

    return static_cast<SpatialMeasureType>(spatialMeasureTypeIndex);
}
