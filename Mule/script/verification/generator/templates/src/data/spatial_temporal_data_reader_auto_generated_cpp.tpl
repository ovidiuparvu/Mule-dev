/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/
 
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"
/*{% for spatial_entity in spatial_entities %}*/
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entity.name|first_to_upper }}*/.hpp"
/*{% endfor %}*/

#include <memory>

using namespace multiscale::verification;

namespace pt = boost::property_tree;


void SpatialTemporalDataReader::createDerivedSpatialEntity(const pt::ptree &spatialEntityTree,
                                                           std::shared_ptr<SpatialEntity> &spatialEntity,
                                                           SubsetSpecificType &spatialEntityType) {
    std::string spatialEntityTypeLabel = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_SPATIAL_TYPE);

    if (spatialEntityTypeLabel.compare("/*{{ spatial_entities[0].name }}*/") == 0) {
        spatialEntity       = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();
        spatialEntityType   = SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s;
    /*{% for spatial_entity in spatial_entities[1:] %}*/
    } else if (spatialEntityTypeLabel.compare("/*{{ spatial_entity.name }}*/") == 0) {
        spatialEntity       = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();
        spatialEntityType   = SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s;
    /*{% endfor %}*/
    } else {
        MS_throw(UnexpectedBehaviourException, ERR_UNDEFINED_SPATIAL_ENTITY_TYPE);
    }
}

void SpatialTemporalDataReader::setSpatialEntityMeasureValues(const pt::ptree &spatialEntityTree,
                                                              const std::shared_ptr<SpatialEntity> &spatialEntity) {
/*{% for spatial_measure in spatial_measures %}*/
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/,
                                          spatialEntityTree.get<double>("/*{{ spatial_measure.name }}*/"));
/*{% endfor %}*/
}
