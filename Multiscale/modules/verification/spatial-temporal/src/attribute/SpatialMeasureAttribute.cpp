#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

using namespace multiscale::verification;


SpatialMeasureType SpatialMeasureAttribute::evaluate() const {
    return spatialMeasure;
}

//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const SpatialMeasureType &spatialMeasureType) {
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
