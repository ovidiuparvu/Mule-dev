/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

using namespace multiscale::verification;


std::string
multiscale::verification::subsetspecific::toString(const SubsetSpecificType &subsetSpecificType) {
    switch (subsetSpecificType) {
        case SubsetSpecificType::Clusters:
            return "cluster";
             
        case SubsetSpecificType::Regions:
            return "region";
             
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}

std::string
multiscale::verification::subsetspecific::toString(const std::size_t &subsetSpecificTypeIndex) {
    switch (subsetSpecificTypeIndex) {
        case 0:
            return "cluster";
             
        case 1:
            return "region";
             
        default:
            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return std::string();
}
 
//! Overload the output stream operator for the SubsetSpecificType enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out, const SubsetSpecificType &subsetSpecificType) {
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