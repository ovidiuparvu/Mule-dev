#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const ComparatorType &comparatorType) {
    switch (comparatorType) {
        case ComparatorType::GreaterThan:
            out << ">";
            break;

        case ComparatorType::GreaterThanOrEqual:
            out << ">=";
            break;

        case ComparatorType::LessThan:
            out << "<";
            break;

        case ComparatorType::LessThanOrEqual:
            out << "<=";
            break;

        case ComparatorType::Equal:
            out << "=";
            break;

        default:
            out << "undefined";
    }

    return out;
}
