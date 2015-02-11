/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

using namespace multiscale::verification;


std::string
multiscale::verification::subsetspecific::toString(const SubsetSpecificType &subsetSpecificType) {
    switch (subsetSpecificType) {
    /*{% for spatial_entity in spatial_entities %}*/
        case SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s:
            return "/*{{ spatial_entity.name }}*/";
             
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}

std::string
multiscale::verification::subsetspecific::toString(const std::size_t &subsetSpecificTypeIndex) {
    switch (subsetSpecificTypeIndex) {
    /*{% for spatial_entity in spatial_entities %}*/
        case /*{{ loop.index0 }}*/:
            return "/*{{ spatial_entity.name }}*/";
             
    /*{% endfor %}*/
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}
 
//! Overload the output stream operator for the SubsetSpecificType enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const SubsetSpecificType &subsetSpecificType) {
    switch (subsetSpecificType) {
    /*{% for spatial_entity in spatial_entities %}*/
        case SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s:
            out << "/*{{ spatial_entity.name }}*/s";
            break;
    /*{% endfor %}*/

        default:
            out << "undefined";
    }

    return out;
}
