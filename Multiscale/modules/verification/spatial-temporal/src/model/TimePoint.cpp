#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <algorithm>
#include <iterator>

using namespace multiscale;
using namespace multiscale::verification;
using namespace multiscale::verification::subsetspecific;


TimePoint::TimePoint(double value) : value(value) {
    this->spatialEntities = std::vector<std::list<std::shared_ptr<SpatialEntity>>>(NR_SUBSET_SPECIFIC_TYPES);

    this->consideredSpatialEntityTypes.reset();
}

TimePoint::TimePoint(const TimePoint &timePoint)
    : value(timePoint.value), spatialEntities(timePoint.spatialEntities),
      numericStateVariables(timePoint.numericStateVariables),
      consideredSpatialEntityTypes(timePoint.consideredSpatialEntityTypes) {}

TimePoint::~TimePoint() {}

double
TimePoint::getValue() const {
    return value;
}

void
TimePoint::setValue(double value) {
    this->value = value;
}

std::bitset<NR_SUBSET_SPECIFIC_TYPES>
TimePoint::getConsideredSpatialEntityTypes() {
    return consideredSpatialEntityTypes;
}

void
TimePoint::setConsideredSpatialEntityType(const SubsetSpecificType &consideredSpatialEntityType) {
    validateSubsetSpecificType(consideredSpatialEntityType);

    consideredSpatialEntityTypes.reset();
    consideredSpatialEntityTypes.set(computeSubsetSpecificTypeIndex(consideredSpatialEntityType));
}

void
TimePoint::addConsideredSpatialEntityType(const SubsetSpecificType &consideredSpatialEntityType) {
    validateSubsetSpecificType(consideredSpatialEntityType);

    consideredSpatialEntityTypes.set(computeSubsetSpecificTypeIndex(consideredSpatialEntityType));
}

double
TimePoint::numberOfSpatialEntities() const {
    double nrOfSpatialEntities = 0;

    for (size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        if (consideredSpatialEntityTypes[i] == true) {
            nrOfSpatialEntities += static_cast<double>((spatialEntities[i]).size());
        }
    }

    return nrOfSpatialEntities;
}

void
TimePoint::addSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                            const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    std::size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    (spatialEntities[spatialEntityTypeIndex]).push_back(spatialEntity);
}

void
TimePoint::addSpatialEntityAndType(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                   const SubsetSpecificType &spatialEntityType) {
    addConsideredSpatialEntityType(spatialEntityType);
    addSpatialEntity(spatialEntity, spatialEntityType);
}

void
TimePoint::addNumericStateVariable(const NumericStateVariableId &id, double value) {
    numericStateVariables[id] = value;
}

bool
TimePoint::containsNumericStateVariable(const NumericStateVariableId &id) {
    return (numericStateVariables.find(id) != numericStateVariables.end());
}

bool
TimePoint::containsNumericStateVariable(const NumericStateVariableId &id) const {
    return (numericStateVariables.find(id) != numericStateVariables.end());
}

bool
TimePoint::containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                 const SubsetSpecificType &spatialEntityType) {
    // Compute the index corresponding to the spatial entity type
    std::size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    // Call the method which takes the spatial entity type index as input
    return (
        containsSpatialEntity(spatialEntity, spatialEntityTypeIndex)
    );
}

bool
TimePoint::containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                 const std::size_t &spatialEntityTypeIndex) {
    // Obtain references to begin and end spatial entities iterators
    auto spatialEntitiesBeginIterator   = spatialEntities[spatialEntityTypeIndex].begin();
    auto spatialEntitiesEndIterator     = spatialEntities[spatialEntityTypeIndex].end();

    // Check if there exists an equal valued spatial entity
    for (auto it = spatialEntitiesBeginIterator; it != spatialEntitiesEndIterator; it++) {
        // If the contents of the spatial entities is identical
        if ((*it)->operator==(*spatialEntity)) {
            return true;
        }
    }

    // If the spatial entity was not found then it is not contained by the time point
    return false;
}

bool
TimePoint::containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                 const SubsetSpecificType &spatialEntityType) const {
    // Compute the index corresponding to the spatial entity type
    std::size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    // Call the method which takes the spatial entity type index as input
    return (
        containsSpatialEntity(spatialEntity, spatialEntityTypeIndex)
    );
}

bool
TimePoint::containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                 const std::size_t &spatialEntityTypeIndex) const {
    // Obtain references to begin and end spatial entities iterators
    auto spatialEntitiesBeginIterator   = spatialEntities[spatialEntityTypeIndex].begin();
    auto spatialEntitiesEndIterator     = spatialEntities[spatialEntityTypeIndex].end();

    // Check if there exists an equal valued spatial entity
    for (auto it = spatialEntitiesBeginIterator; it != spatialEntitiesEndIterator; it++) {
        // If the contents of the spatial entities is identical
        if ((*(*it)) == (*spatialEntity)) {
            return true;
        }
    }

    // If the spatial entity was not found then it is not contained by the time point
    return false;
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::getSpatialEntitiesBeginIterator(const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return getSpatialEntitiesBeginIterator(spatialEntityTypeIndex);
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::getSpatialEntitiesBeginIterator(const std::size_t &spatialEntityTypeIndex) {
    validateSubsetSpecificTypeIndex(spatialEntityTypeIndex);

    if (consideredSpatialEntityTypes[spatialEntityTypeIndex] == true) {
        return (spatialEntities[spatialEntityTypeIndex]).begin();
    } else {
        return (spatialEntities[spatialEntityTypeIndex]).end();
    }
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator
TimePoint::getSpatialEntitiesBeginIterator(const SubsetSpecificType &spatialEntityType) const {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return getSpatialEntitiesBeginIterator(spatialEntityTypeIndex);
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator
TimePoint::getSpatialEntitiesBeginIterator(const std::size_t &spatialEntityTypeIndex) const {
    validateSubsetSpecificTypeIndex(spatialEntityTypeIndex);

    if (consideredSpatialEntityTypes[spatialEntityTypeIndex] == true) {
        return (spatialEntities[spatialEntityTypeIndex]).begin();
    } else {
        return (spatialEntities[spatialEntityTypeIndex]).end();
    }
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::getSpatialEntitiesEndIterator(const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return getSpatialEntitiesEndIterator(spatialEntityTypeIndex);
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::getSpatialEntitiesEndIterator(const std::size_t &spatialEntityTypeIndex) {
    validateSubsetSpecificTypeIndex(spatialEntityTypeIndex);

    return (spatialEntities[spatialEntityTypeIndex]).end();
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator
TimePoint::getSpatialEntitiesEndIterator(const SubsetSpecificType &spatialEntityType) const {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return getSpatialEntitiesEndIterator(spatialEntityTypeIndex);
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator
TimePoint::getSpatialEntitiesEndIterator(const std::size_t &spatialEntityTypeIndex) const {
    validateSubsetSpecificTypeIndex(spatialEntityTypeIndex);

    return (spatialEntities[spatialEntityTypeIndex]).end();
}

std::vector<std::shared_ptr<SpatialEntity>>
TimePoint::getConsideredSpatialEntities() const {
    std::vector<std::shared_ptr<SpatialEntity>> consideredSpatialEntities;

    for (size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        if (consideredSpatialEntityTypes[i] == true) {
            consideredSpatialEntities.insert(
                consideredSpatialEntities.begin(),
                (spatialEntities[i]).begin(),
                (spatialEntities[i]).end()
            );
        }
    }

    return consideredSpatialEntities;
}

double
TimePoint::getNumericStateVariableValue(const NumericStateVariableId &id) const {
    auto it = numericStateVariables.find(id);

    if (it == numericStateVariables.end()) {
        MS_throw_detailed(SpatialTemporalException, ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX,
                          id.toString(), ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX);
    }

    return it->second;
}

std::unordered_map<NumericStateVariableId, double>::iterator
TimePoint::getNumericStateVariablesBeginIterator() {
    return numericStateVariables.begin();
}

std::unordered_map<NumericStateVariableId, double>::const_iterator
TimePoint::getNumericStateVariablesBeginIterator() const {
    return numericStateVariables.begin();
}

std::unordered_map<NumericStateVariableId, double>::iterator
TimePoint::getNumericStateVariablesEndIterator() {
    return numericStateVariables.end();
}

std::unordered_map<NumericStateVariableId, double>::const_iterator
TimePoint::getNumericStateVariablesEndIterator() const {
    return numericStateVariables.end();
}

void
TimePoint::timePointDifference(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Difference);
}

void
TimePoint::timePointIntersection(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Intersection);
}

void
TimePoint::timePointUnion(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Union);
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::removeSpatialEntity(std::list<std::shared_ptr<SpatialEntity>>::iterator &position,
                               const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    return spatialEntities[computeSubsetSpecificTypeIndex(spatialEntityType)].erase(position);
}

bool
TimePoint::operator==(const TimePoint &rhsTimePoint) {
    // If the time points values are equal then check if the numeric state variables and spatial entities are equal
    if (Numeric::almostEqual(value, rhsTimePoint.value)) {
        return (
            areEqualNumericStateVariables(rhsTimePoint) &&
            areEqualSpatialEntities(rhsTimePoint)
        );
    }

    // Otherwise return false
    return false;
}

bool
TimePoint::operator!=(const TimePoint &rhsTimePoint) {
    // The time points are different if they are not equal
    return !(
        this->operator==(rhsTimePoint)
    );
}

void
TimePoint::timePointSetOperation(const TimePoint &timePoint, const SubsetOperationType &setOperationType) {
    updateSpatialEntities(timePoint, setOperationType);
    updateConsideredSpatialEntityTypes(timePoint.consideredSpatialEntityTypes, setOperationType);
}

void
TimePoint::updateSpatialEntities(const TimePoint &timePoint, const SubsetOperationType &setOperationType) {
    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        SubsetSpecificType subsetSpecificType = computeSubsetSpecificType(i);

        spatialEntities[i] = spatialEntitiesSetOperation(timePoint, setOperationType, subsetSpecificType);
    }
}

std::list<std::shared_ptr<SpatialEntity>>
TimePoint::spatialEntitiesSetOperation(const TimePoint &timePoint, const SubsetOperationType &setOperationType,
                                       const SubsetSpecificType &spatialEntitiesType) {
    std::list<std::shared_ptr<SpatialEntity>> newSpatialEntities;

    switch(setOperationType) {
        case SubsetOperationType::Difference:
            std::set_difference(getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                getSpatialEntitiesEndIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesEndIterator(spatialEntitiesType),
                                std::inserter(newSpatialEntities, newSpatialEntities.begin()));
            break;

        case SubsetOperationType::Intersection:
            std::set_intersection(getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                  getSpatialEntitiesEndIterator(spatialEntitiesType),
                                  timePoint.getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                  timePoint.getSpatialEntitiesEndIterator(spatialEntitiesType),
                                  std::inserter(newSpatialEntities, newSpatialEntities.begin()));
            break;

        case SubsetOperationType::Union:
            std::set_union(getSpatialEntitiesBeginIterator(spatialEntitiesType),
                           getSpatialEntitiesEndIterator(spatialEntitiesType),
                           timePoint.getSpatialEntitiesBeginIterator(spatialEntitiesType),
                           timePoint.getSpatialEntitiesEndIterator(spatialEntitiesType),
                           std::inserter(newSpatialEntities, newSpatialEntities.begin()));
            break;
    }

    return newSpatialEntities;
}

void
TimePoint::updateConsideredSpatialEntityTypes(const std::bitset<NR_SUBSET_SPECIFIC_TYPES>
                                              &consideredSpatialEntityTypes,
                                              const SubsetOperationType &setOperationType) {
    switch(setOperationType) {
        case SubsetOperationType::Difference:
            // No changes required
            break;

        case SubsetOperationType::Intersection:
            this->consideredSpatialEntityTypes &= consideredSpatialEntityTypes;
            break;

        case SubsetOperationType::Union:
            this->consideredSpatialEntityTypes |= consideredSpatialEntityTypes;
            break;
    }
}

bool
TimePoint::areEqualNumericStateVariables(const TimePoint &rhsTimePoint) {
    // If the number of spatial entities is different return false
    if (numericStateVariables.size() != rhsTimePoint.numericStateVariables.size()) {
        return false;
    // Otherwise check if all numeric state variables of this instance are contained by the right hand side time point
    } else {
        for (auto it = numericStateVariables.begin(); it != numericStateVariables.end(); it++) {
            NumericStateVariableId numericStateVariableId = it->first;

            // If the right hand side time point does not contain the numeric state variable return false
            if (!rhsTimePoint.containsNumericStateVariable(numericStateVariableId)) {
                return false;
            }
        }

        // Return true if all numeric state variables of this instance are contained by the right hand side time point
        return true;
    }
}

bool
TimePoint::areEqualSpatialEntities(const TimePoint &rhsTimePoint) {
    // Check if all spatial entities of all types are contained by the right hand side time point
    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        // If the spatial entities of a specific type are not contained by the right hand side time point return false
        if (!areEqualSpatialEntitiesOfSpecificType(rhsTimePoint, i)) {
            return false;
        }
    }

    // Return true if all spatial entities of all types are contained by the right hand side time point
    return true;
}

bool
TimePoint::areEqualSpatialEntitiesOfSpecificType(const TimePoint &rhsTimePoint,
                                                 const std::size_t &spatialEntityTypeIndex) {
    // If the number of spatial entities of the given type differs then return false
    if (spatialEntities[spatialEntityTypeIndex].size() !=
        rhsTimePoint.spatialEntities[spatialEntityTypeIndex].size()
    ) {
        return false;
    } else {
        // Obtain references to the begin and end iterators for spatial entities of the given type
        auto beginIt    = spatialEntities[spatialEntityTypeIndex].begin();
        auto endIt      = spatialEntities[spatialEntityTypeIndex].end();

        // Check if all spatial entities of a specific type are contained by the right hand side time point
        for (auto it = beginIt; it != endIt; it++) {
            // If the right hand side time point does not contain the spatial entity return false
            if (!rhsTimePoint.containsSpatialEntity(
                    (*it),                  // The spatial entity
                    spatialEntityTypeIndex
                )
            ) {
                return false;
            }
        }

        // Return true if all spatial entities of a specific type are contained by the right hand side time point
        return true;
    }
}


// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX  = "The numeric state variable with the given id ";
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX  = " does not exist.";
