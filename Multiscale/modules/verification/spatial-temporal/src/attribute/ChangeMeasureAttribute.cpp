#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const ChangeMeasureType &changeMeasureType) {
    switch (changeMeasureType) {
        case ChangeMeasureType::Derivative:
            out << "derivative";
            break;

        case ChangeMeasureType::Ratio:
            out << "ratio";
            break;

        default:
            out << "undefined";
    }

    return out;
}

