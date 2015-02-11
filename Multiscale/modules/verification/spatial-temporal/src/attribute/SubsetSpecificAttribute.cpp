#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

using namespace multiscale::verification;
using namespace multiscale::verification::subsetspecific;


void
multiscale::verification::subsetspecific::validateSubsetSpecificType(const SubsetSpecificType &spatialEntityType) {
    if (spatialEntityType == SubsetSpecificType::NrOfSubsetSpecificTypeEntries) {
        MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }
}

void
multiscale::verification::subsetspecific::validateSubsetSpecificTypeIndex(const std::size_t &spatialEntityTypeIndex) {
    if (spatialEntityTypeIndex >= NR_SUBSET_SPECIFIC_TYPES) {
        MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
    }
}

size_t
multiscale::verification::subsetspecific::computeSubsetSpecificTypeIndex(const SubsetSpecificType &subsetSpecificType) {
    validateSubsetSpecificType(subsetSpecificType);

    return static_cast<size_t>(subsetSpecificType);
}

SubsetSpecificType
multiscale::verification::subsetspecific::computeSubsetSpecificType(const std::size_t &subsetSpecificTypeIndex) {
    validateSubsetSpecificTypeIndex(subsetSpecificTypeIndex);

    return static_cast<SubsetSpecificType>(subsetSpecificTypeIndex);
}
