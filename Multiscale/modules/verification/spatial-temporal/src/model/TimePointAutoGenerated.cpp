/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/

#include "multiscale/exception/UnimplementedMethodException.hpp"
#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

using namespace multiscale;
using namespace multiscale::verification;


double TimePoint::avgDistanceBetweenCentroids(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
    double      distanceSum         = 0;
    std::size_t nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity1 : spatialEntities) {
        for (const auto &spatialEntity2 : spatialEntities) {
            distanceSum += Geometry2D::distanceBtwPoints((*spatialEntity1).getSpatialMeasureValue(SpatialMeasureType::CentroidX),
                                                         (*spatialEntity1).getSpatialMeasureValue(SpatialMeasureType::CentroidY),
                                                         (*spatialEntity2).getSpatialMeasureValue(SpatialMeasureType::CentroidX),
                                                         (*spatialEntity2).getSpatialMeasureValue(SpatialMeasureType::CentroidY));
        }
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (distanceSum / (nrOfSpatialEntities * nrOfSpatialEntities));
}

double TimePoint::avgDensity(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
    double      densitySum          = 0;
    std::size_t nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity : spatialEntities) {
        densitySum += (*spatialEntity).getSpatialMeasureValue(SpatialMeasureType::Density);
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (densitySum / nrOfSpatialEntities);
}