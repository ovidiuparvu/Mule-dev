#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetMeasureAttribute.hpp"

using namespace multiscale::verification;


TernarySubsetMeasureType TernarySubsetMeasureAttribute::evaluate() const {
    return ternarySubsetMeasureType;
}

//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const TernarySubsetMeasureType &ternarySubsetMeasureType) {
    switch (ternarySubsetMeasureType) {
        case TernarySubsetMeasureType::Percentile:
            out << "percentile";
            break;

        case TernarySubsetMeasureType::Quartile:
            out << "quartile";
            break;

        default:
            out << "undefined";
    }

    return out;
}
