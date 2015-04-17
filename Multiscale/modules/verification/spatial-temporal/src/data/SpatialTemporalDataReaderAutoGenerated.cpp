/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
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
    std::string spatialEntityTypeLabel = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_SPATIAL_TYPE);

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

void SpatialTemporalDataReader::setSpatialEntityMeasureValues(const pt::ptree &spatialEntityTree,
                                                              const std::shared_ptr<SpatialEntity> &spatialEntity) {
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Clusteredness,
                                          spatialEntityTree.get<double>("clusteredness"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Density,
                                          spatialEntityTree.get<double>("density"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Area,
                                          spatialEntityTree.get<double>("area"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Perimeter,
                                          spatialEntityTree.get<double>("perimeter"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin,
                                          spatialEntityTree.get<double>("distanceFromOrigin"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Angle,
                                          spatialEntityTree.get<double>("angle"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure,
                                          spatialEntityTree.get<double>("triangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure,
                                          spatialEntityTree.get<double>("rectangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure,
                                          spatialEntityTree.get<double>("circleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidX,
                                          spatialEntityTree.get<double>("centroidX"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidY,
                                          spatialEntityTree.get<double>("centroidY"));
}