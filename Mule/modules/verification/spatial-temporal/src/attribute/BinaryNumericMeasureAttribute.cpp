#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const BinaryNumericMeasureType &binaryNumericMeasureType) {
    switch (binaryNumericMeasureType) {
        case BinaryNumericMeasureType::Add:
            out << "add";
            break;

        case BinaryNumericMeasureType::Div:
            out << "div";
            break;

        case BinaryNumericMeasureType::Log:
            out << "log";
            break;

        case BinaryNumericMeasureType::Mod:
            out << "mod";
            break;

        case BinaryNumericMeasureType::Multiply:
            out << "multiply";
            break;

        case BinaryNumericMeasureType::Power:
            out << "power";
            break;

        case BinaryNumericMeasureType::Subtract:
            out << "subtract";
            break;

        default:
            out << "undefined";
    }

    return out;
}
