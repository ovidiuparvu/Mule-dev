#include "multiscale/verification/spatial-temporal/attribute/SubsetOperationAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out,
                                                   const SubsetOperationType &subsetOperationType) {
    switch (subsetOperationType) {
        case SubsetOperationType::Difference:
            out << "difference";
            break;

        case SubsetOperationType::Intersection:
            out << "intersection";
            break;

        case SubsetOperationType::Union:
            out << "union";
            break;

        default:
            out << "undefined";
    }

    return out;
}
