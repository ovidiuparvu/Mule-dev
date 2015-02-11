#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const BinaryStatisticalMeasureType &binaryStatisticalMeasureType) {
    switch (binaryStatisticalMeasureType) {
        case BinaryStatisticalMeasureType::Covar:
            out << "covar";
            break;

        default:
            out << "undefined";
    }

    return out;
}
