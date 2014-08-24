#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const HomogeneousTimeseriesMeasureType &homogeneousTimeseriesMeasureType) {
    switch (homogeneousTimeseriesMeasureType) {
        case HomogeneousTimeseriesMeasureType::Duration:
            out << "duration";
            break;

        case HomogeneousTimeseriesMeasureType::Value:
            out << "value";
            break;

        default:
            out << "undefined";
    }

    return out;
}
