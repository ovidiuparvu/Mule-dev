#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale;
using namespace multiscale::verification;
using namespace multiscale::verification::spatialmeasure;


SpatialEntity::SpatialEntity() {
    scaleAndSubsystem         = ScaleAndSubsystem::DEFAULT_VALUE;
    spatialMeasureValues = std::vector<double>(NR_SPATIAL_MEASURE_TYPES, 0);
}

SpatialEntity::~SpatialEntity() {}

double SpatialEntity::getSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) const {
    std::size_t spatialMeasureTypeIndex = computeSpatialMeasureTypeIndex(spatialMeasureType);

    return spatialMeasureValues[spatialMeasureTypeIndex];
}

void SpatialEntity::setSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType,
                                           double spatialMeasureValue) {
    validateSpatialMeasureValue(spatialMeasureValue, spatialMeasureType);

    std::size_t spatialMeasureTypeIndex = computeSpatialMeasureTypeIndex(spatialMeasureType);

    spatialMeasureValues[spatialMeasureTypeIndex] = spatialMeasureValue;
}

bool SpatialEntity::operator<(const SpatialEntity &rhsSpatialEntity) {
    // Call the const version of the operator
    return (
        (static_cast<const SpatialEntity&>(*this)).operator<(rhsSpatialEntity)
    );
}

bool SpatialEntity::operator<(const SpatialEntity &rhsSpatialEntity) const {
    if (this->scaleAndSubsystem.compare(rhsSpatialEntity.scaleAndSubsystem) == -1) {
        return true;
    }

    // Return true if lhs.spatialMeasureValue < rhs.spatialMeasureValue
    for (std::size_t i = 0; i < NR_SPATIAL_MEASURE_TYPES; i++) {
        if (this->spatialMeasureValues[i] < rhsSpatialEntity.spatialMeasureValues[i]) {
            return true;
        }
    }

    // Otherwise, return false
    return false;
}

bool SpatialEntity::operator==(const SpatialEntity &rhsSpatialEntity) {
    // Call the const version of the operator
    return (
        (static_cast<const SpatialEntity&>(*this)).operator==(rhsSpatialEntity)
    );
}

bool SpatialEntity::operator==(const SpatialEntity &rhsSpatialEntity) const {
    if (this->scaleAndSubsystem.compare(rhsSpatialEntity.scaleAndSubsystem) != 0) {
        return false;
    }

    // Return false if at least once lhs.spatialMeasureValue != rhs.spatialMeasureValue
    for (std::size_t i = 0; i < NR_SPATIAL_MEASURE_TYPES; i++) {
        if (!Numeric::almostEqual(
                this->spatialMeasureValues[i],
                rhsSpatialEntity.spatialMeasureValues[i]
            )
        ) {
            return false;
        }
    }

    // Otherwise, return true
    return true;
}

bool SpatialEntity::operator!=(const SpatialEntity &rhsSpatialEntity) {
    // Call the const version of the operator
    return (
        (static_cast<const SpatialEntity&>(*this)).operator!=(rhsSpatialEntity)
    );
}

bool SpatialEntity::operator!=(const SpatialEntity &rhsSpatialEntity) const {
    // Return the negation of (this == rhsSpatialEntity)
    return (
        !(this->operator==(rhsSpatialEntity))
    );
}

std::string SpatialEntity::toString() const {
    std::string outputString = scaleAndSubsystem;

    // Add all spatial measure values to the output string
    for (std::size_t i = 0; i < NR_SPATIAL_MEASURE_TYPES; i++) {
        outputString += (OUTPUT_SPATIAL_MEASURE_VALUE_SEPARATOR +
                         StringManipulator::toString<double>(spatialMeasureValues[i]));
    }

    return outputString;
}

void SpatialEntity::validateSpatialMeasureValue(double spatialMeasureValue,
                                                const SpatialMeasureType &spatialMeasureType) {
    spatialmeasure::validateSpatialMeasureType(spatialMeasureType);

    if ((spatialMeasureValue < spatialmeasure::getMinValidSpatialMeasureValue(spatialMeasureType)) ||
        (spatialMeasureValue > spatialmeasure::getMaxValidSpatialMeasureValue(spatialMeasureType))) {
        MS_throw(SpatialTemporalException,
                 ERR_INVALID_SPATIAL_MEASURE_BEGIN +
                 StringManipulator::toString<double>(spatialMeasureValue) +
                 ERR_INVALID_SPATIAL_MEASURE_MIDDLE +
                 StringManipulator::toString<SpatialMeasureType>(spatialMeasureType) +
                 ERR_INVALID_SPATIAL_MEASURE_END
        );
    }
}


// Constants
const std::string SpatialEntity::OUTPUT_SPATIAL_MEASURE_VALUE_SEPARATOR = ", ";

const std::string SpatialEntity::ERR_INVALID_SPATIAL_MEASURE_BEGIN  = "The provided spatial measure value (";
const std::string SpatialEntity::ERR_INVALID_SPATIAL_MEASURE_MIDDLE = ") is invalid for the given spatial measure type (";
const std::string SpatialEntity::ERR_INVALID_SPATIAL_MEASURE_END    = "). Please change.";
