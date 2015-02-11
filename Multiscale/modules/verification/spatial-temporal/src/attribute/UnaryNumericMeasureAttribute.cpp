#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const UnaryNumericMeasureType &unaryNumericMeasureType) {
    switch (unaryNumericMeasureType) {
        case UnaryNumericMeasureType::Abs:
            out << "abs";
            break;

        case UnaryNumericMeasureType::Ceil:
            out << "ceil";
            break;

        case UnaryNumericMeasureType::Floor:
            out << "floor";
            break;

        case UnaryNumericMeasureType::Round:
            out << "round";
            break;

        case UnaryNumericMeasureType::Sign:
            out << "sign";
            break;

        case UnaryNumericMeasureType::Sqrt:
            out << "sqrt";
            break;

        case UnaryNumericMeasureType::Trunc:
            out << "trunc";
            break;

        default:
            out << "undefined";
    }

    return out;
}
