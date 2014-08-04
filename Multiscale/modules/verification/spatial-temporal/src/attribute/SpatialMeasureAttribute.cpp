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

double
multiscale::verification::spatialmeasure::getMinValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
        case SpatialMeasureType::Clusteredness:
            return 0;
            break;

        case SpatialMeasureType::Density:
            return 0;
            break;

        case SpatialMeasureType::Area:
            return 0;
            break;

        case SpatialMeasureType::Perimeter:
            return 0;
            break;

        case SpatialMeasureType::DistanceFromOrigin:
            return 0;
            break;

        case SpatialMeasureType::Angle:
            return 0;
            break;

        case SpatialMeasureType::TriangleMeasure:
            return 0;
            break;

        case SpatialMeasureType::RectangleMeasure:
            return 0;
            break;

        case SpatialMeasureType::CircleMeasure:
            return 0;
            break;

        case SpatialMeasureType::CentroidX:
            return 0;
            break;

        case SpatialMeasureType::CentroidY:
            return 0;
            break;

        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0.0;
}

double
multiscale::verification::spatialmeasure::getMaxValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
        case SpatialMeasureType::Clusteredness:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::Density:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::Area:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::Perimeter:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::DistanceFromOrigin:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::Angle:
            return 360.0;
            break;

        case SpatialMeasureType::TriangleMeasure:
            return 1.0;
            break;

        case SpatialMeasureType::RectangleMeasure:
            return 1.0;
            break;

        case SpatialMeasureType::CircleMeasure:
            return 1.0;
            break;

        case SpatialMeasureType::CentroidX:
            return std::numeric_limits<double>::max();
            break;

        case SpatialMeasureType::CentroidY:
            return std::numeric_limits<double>::max();
            break;

        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0.0;
}

//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
        case SpatialMeasureType::Clusteredness:
            out << "clusteredness";
            break;

        case SpatialMeasureType::Density:
            out << "density";
            break;

        case SpatialMeasureType::Area:
            out << "area";
            break;

        case SpatialMeasureType::Perimeter:
            out << "perimeter";
            break;

        case SpatialMeasureType::DistanceFromOrigin:
            out << "distanceFromOrigin";
            break;

        case SpatialMeasureType::Angle:
            out << "angle";
            break;

        case SpatialMeasureType::TriangleMeasure:
            out << "triangleMeasure";
            break;

        case SpatialMeasureType::RectangleMeasure:
            out << "rectangleMeasure";
            break;

        case SpatialMeasureType::CircleMeasure:
            out << "circleMeasure";
            break;

        case SpatialMeasureType::CentroidX:
            out << "centroidX";
            break;

        case SpatialMeasureType::CentroidY:
            out << "centroidY";
            break;

        default:
            out << "undefined";
    }

    return out;
}
