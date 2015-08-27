#include <multiscale/verification/spatial-temporal/attribute/HeterogeneousTimeSeriesComponentAttribute.hpp>

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const HeterogeneousTimeSeriesComponentType
                                     &heterogeneousTimeSeriesComponentType) {
    switch (heterogeneousTimeSeriesComponentType) {
        case HeterogeneousTimeSeriesComponentType::Peak:
            out << "peak";
            break;

        case HeterogeneousTimeSeriesComponentType::Valley:
            out << "valley";
            break;

        default:
            out << "undefined";
    }

    return out;
}
