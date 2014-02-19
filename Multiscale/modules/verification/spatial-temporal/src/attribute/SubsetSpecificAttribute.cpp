#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const SubsetSpecificType &subsetSpecificType) {
    switch (subsetSpecificType) {
        case SubsetSpecificType::Clusters:
            out << "clusters";
            break;

        case SubsetSpecificType::Regions:
            out << "regions";
            break;

        default:
            out << "undefined";
    }

    return out;
}
