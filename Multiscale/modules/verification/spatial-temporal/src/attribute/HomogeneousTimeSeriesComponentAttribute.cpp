#include <multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesComponentAttribute.hpp>

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const HomogeneousTimeSeriesComponentType &homogeneousTimeSeriesComponentType) {
    switch (homogeneousTimeSeriesComponentType) {
        case HomogeneousTimeSeriesComponentType::Ascent:
            out << "ascent";
            break;

        case HomogeneousTimeSeriesComponentType::Descent:
            out << "descent";
            break;

        case HomogeneousTimeSeriesComponentType::Plateau:
            out << "plateau";
            break;

        case HomogeneousTimeSeriesComponentType::UniformAscent:
            out << "uniformAscent";
            break;

        case HomogeneousTimeSeriesComponentType::UniformDescent:
            out << "uniformDescent";
            break;

        default:
            out << "undefined";
    }

    return out;
}
