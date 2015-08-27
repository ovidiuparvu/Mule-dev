#include <multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesMeasureAttribute.hpp>

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const HomogeneousTimeSeriesMeasureType &homogeneousTimeSeriesMeasureType) {
    switch (homogeneousTimeSeriesMeasureType) {
        case HomogeneousTimeSeriesMeasureType::TimeSpan:
            out << "timeSpan";
            break;

        case HomogeneousTimeSeriesMeasureType::Values:
            out << "values";
            break;

        default:
            out << "undefined";
    }

    return out;
}
