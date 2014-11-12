/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/
 
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataWriter.hpp"
/*{% for spatial_entity in spatial_entities %}*/
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entity.name|first_to_upper }}*/.hpp"
/*{% endfor %}*/

#include <memory>

using namespace multiscale::verification;

namespace pt = boost::property_tree;


void SpatialTemporalDataWriter::addSpatialMeasuresValuesToTree(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                               pt::ptree &spatialEntityTree) {
/*{% for spatial_measure in spatial_measures %}*/
    spatialEntityTree.put(
        "/*{{ spatial_measure.name }}*/",
        spatialEntity->getSpatialMeasureValue(
            SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/
        )
    );
    
/*{% endfor %}*/    
}