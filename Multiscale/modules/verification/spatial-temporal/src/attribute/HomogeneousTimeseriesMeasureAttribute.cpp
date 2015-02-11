#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const HomogeneousTimeseriesMeasureType &homogeneousTimeseriesMeasureType) {
    switch (homogeneousTimeseriesMeasureType) {
        case HomogeneousTimeseriesMeasureType::TimeSpan:
            out << "timeSpan";
            break;

        case HomogeneousTimeseriesMeasureType::Values:
            out << "values";
            break;

        default:
            out << "undefined";
    }

    return out;
}
