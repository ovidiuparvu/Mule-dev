#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesComponentAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const HomogeneousTimeseriesComponentType &homogeneousTimeseriesComponentType) {
    switch (homogeneousTimeseriesComponentType) {
        case HomogeneousTimeseriesComponentType::Ascent:
            out << "ascent";
            break;

        case HomogeneousTimeseriesComponentType::Descent:
            out << "descent";
            break;

        case HomogeneousTimeseriesComponentType::Plateau:
            out << "plateau";
            break;

        case HomogeneousTimeseriesComponentType::UniformAscent:
            out << "uniformAscent";
            break;

        case HomogeneousTimeseriesComponentType::UniformDescent:
            out << "uniformDescent";
            break;

        default:
            out << "undefined";
    }

    return out;
}
