#include "multiscale/verification/spatial-temporal/attribute/HeterogeneousTimeseriesComponentAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const HeterogeneousTimeseriesComponentType
                                     &heterogeneousTimeseriesComponentType) {
    switch (heterogeneousTimeseriesComponentType) {
        case HeterogeneousTimeseriesComponentType::Peak:
            out << "peak";
            break;

        case HeterogeneousTimeseriesComponentType::Valley:
            out << "valley";
            break;

        default:
            out << "undefined";
    }

    return out;
}
