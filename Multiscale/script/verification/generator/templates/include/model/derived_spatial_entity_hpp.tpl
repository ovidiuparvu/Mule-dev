#ifndef /*{{ spatial_entity_name|upper }}*/_HPP
#define /*{{ spatial_entity_name|upper }}*/_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a /*{{ spatial_entity_name }}*/
        class /*{{ spatial_entity_name|first_to_upper }}*/ : public SpatialEntity {};

    };

};


#endif