#include <multiscale/verification/spatial-temporal/attribute/TimeSeriesMeasureAttribute.hpp>

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const TimeSeriesMeasureType &timeSeriesMeasureType) {
    switch (timeSeriesMeasureType) {
        case TimeSeriesMeasureType::EnteringTime:
            out << "enteringTime";
            break;

        case TimeSeriesMeasureType::EnteringValue:
            out << "enteringValue";
            break;

        default:
            out << "undefined";
    }

    return out;
}
