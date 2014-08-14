#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const BinaryStatisticalQuantileMeasureType
                                     &binaryStatisticalQuantileMeasureType) {
    switch (binaryStatisticalQuantileMeasureType) {
        case BinaryStatisticalQuantileMeasureType::Percentile:
            out << "percentile";
            break;

        case BinaryStatisticalQuantileMeasureType::Quartile:
            out << "quartile";
            break;

        default:
            out << "undefined";
    }

    return out;
}
