/******************************************************************************
{% for line in auto_generated_warning %}
 {{ line }}
{% endfor %}
 *****************************************************************************/

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the SubsetSpecificType enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const SubsetSpecificType &subsetSpecificType) {
    switch (subsetSpecificType) {
    {% for spatial_entity in spatial_entities %}
        case SubsetSpecificType::{{ spatial_entity.name|first_to_upper }}s:
            out << "{{ spatial_entity.name }}s";
            break;
    {% endfor %}

        default:
            out << "undefined";
    }

    return out;
}
