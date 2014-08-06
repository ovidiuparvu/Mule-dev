#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <memory>

using namespace multiscale::verification;

namespace pt = boost::property_tree;


void SpatialTemporalDataReader::createDerivedSpatialEntity(const pt::ptree &spatialEntityTree,
                                                           std::shared_ptr<SpatialEntity> &spatialEntity,
                                                           SubsetSpecificType &spatialEntityType) {
    std::string spatialEntityTypeLabel = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE);

    if (spatialEntityTypeLabel.compare("cluster") == 0) {
        spatialEntity       = std::make_shared<Cluster>();
        spatialEntityType   = SubsetSpecificType::Clusters;
    } else if (spatialEntityTypeLabel.compare("region") == 0) {
        spatialEntity       = std::make_shared<Region>();
        spatialEntityType   = SubsetSpecificType::Regions;
    } else {
        MS_throw(UnexpectedBehaviourException, ERR_UNDEFINED_SPATIAL_ENTITY_TYPE);
    }
}

void SpatialTemporalDataReader::setSpatialEntityValues(const pt::ptree &spatialEntityTree,
                                                       const std::shared_ptr<SpatialEntity> &spatialEntity) {
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Clusteredness,
                                          spatialEntityTree.get<double>("pseudo3D.clusteredness"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Density,
                                          spatialEntityTree.get<double>("pseudo3D.density"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Area,
                                          spatialEntityTree.get<double>("pseudo3D.area"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Perimeter,
                                          spatialEntityTree.get<double>("pseudo3D.perimeter"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin,
                                          spatialEntityTree.get<double>("pseudo3D.distanceFromOrigin"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Angle,
                                          spatialEntityTree.get<double>("pseudo3D.angle"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.triangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.rectangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.circleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidX,
                                          spatialEntityTree.get<double>("pseudo3D.centroid.x"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidY,
                                          spatialEntityTree.get<double>("pseudo3D.centroid.y"));
}
