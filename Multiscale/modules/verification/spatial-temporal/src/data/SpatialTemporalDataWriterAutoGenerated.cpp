/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataWriter.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <memory>

using namespace multiscale::verification;

namespace pt = boost::property_tree;


void SpatialTemporalDataWriter::addSpatialMeasuresValuesToTree(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                               pt::ptree &spatialEntityTree) {
    spatialEntityTree.put(
        "clusteredness",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::Clusteredness
        )
    );
    
    spatialEntityTree.put(
        "density",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::Density
        )
    );
    
    spatialEntityTree.put(
        "area",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::Area
        )
    );
    
    spatialEntityTree.put(
        "perimeter",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::Perimeter
        )
    );
    
    spatialEntityTree.put(
        "distanceFromOrigin",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::DistanceFromOrigin
        )
    );
    
    spatialEntityTree.put(
        "angle",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::Angle
        )
    );
    
    spatialEntityTree.put(
        "triangleMeasure",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::TriangleMeasure
        )
    );
    
    spatialEntityTree.put(
        "rectangleMeasure",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::RectangleMeasure
        )
    );
    
    spatialEntityTree.put(
        "circleMeasure",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::CircleMeasure
        )
    );
    
    spatialEntityTree.put(
        "centroidX",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::CentroidX
        )
    );
    
    spatialEntityTree.put(
        "centroidY",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::CentroidY
        )
    );
    
    
}