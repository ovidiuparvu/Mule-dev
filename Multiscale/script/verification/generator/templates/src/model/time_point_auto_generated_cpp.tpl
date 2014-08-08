/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "multiscale/exception/UnimplementedMethodException.hpp"
#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

using namespace multiscale;
using namespace multiscale::verification;


double TimePoint::avgDistanceBetweenCentroids(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
/*{% if is_centroid_x_spatial_measure and is_centroid_y_spatial_measure %}*/
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
/*{% else %}*/
    // This method is unimplemented because the currently generated custom model checker
    // is missing at least one of the required spatial measures (density, centroidX, centroidY)
    // from the SpatialEntity class
    MS_throw(UnimplementedMethodException, ERR_UNIMPLEMENTED_METHOD);
/*{% endif %}*/
}

double TimePoint::avgDensity(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
/*{% if is_density_spatial_measure %}*/
    double      densitySum          = 0;
    std::size_t nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity : spatialEntities) {
        densitySum += (*spatialEntity).getSpatialMeasureValue(SpatialMeasureType::Density);
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (densitySum / nrOfSpatialEntities);
/*{% else %}*/
    // This method is unimplemented because the currently generated custom model checker
    // is missing at least one of the required spatial measures (density, centroidX, centroidY)
    // from the SpatialEntity class
    MS_throw(UnimplementedMethodException, ERR_UNIMPLEMENTED_METHOD);
/*{% endif %}*/
}
