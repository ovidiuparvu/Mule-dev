#include "multiscale/verification/spatial-temporal/attribute/TimeseriesMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const TimeseriesMeasureType &timeseriesMeasureType) {
    switch (timeseriesMeasureType) {
        case TimeseriesMeasureType::EnteringTime:
            out << "enteringTime";
            break;

        case TimeseriesMeasureType::EnteringValue:
            out << "enteringValue";
            break;

        default:
            out << "undefined";
    }

    return out;
}
