/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

#include <limits>

using namespace multiscale::verification;
using namespace multiscale::verification::spatialmeasure;


double
multiscale::verification::spatialmeasure::getMinValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
    /*{% for spatial_measure in spatial_measures %}*/
        case SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/:
            return /*{{ spatial_measure.min_value }}*/;
            break;
            
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0.0;
}

double
multiscale::verification::spatialmeasure::getMaxValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
    /*{% for spatial_measure in spatial_measures %}*/
        case SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/:
            return /*{{ spatial_measure.max_value }}*/;
            break;
            
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0.0;
}

std::string
multiscale::verification::spatialmeasure::toString(const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
   /*{% for spatial_measure in spatial_measures %}*/
        case SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/:
            return "/*{{ spatial_measure.name }}*/";
            
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}

std::string
multiscale::verification::spatialmeasure::toString(const std::size_t &spatialMeasureTypeIndex) {
    switch (spatialMeasureTypeIndex) {
   /*{% for spatial_measure in spatial_measures %}*/
        case /*{{ loop.index0 }}*/:
            return "/*{{ spatial_measure.name }}*/";
            
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}

//! Overload the output stream operator for the SpatialMeasureType enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const SpatialMeasureType &spatialMeasureType) {
    switch (spatialMeasureType) {
   /*{% for spatial_measure in spatial_measures %}*/
        case SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/:
            out << "/*{{ spatial_measure.name }}*/";
            break;
            
    /*{% endfor %}*/
        default:
            out << "undefined";
    }

    return out;
}