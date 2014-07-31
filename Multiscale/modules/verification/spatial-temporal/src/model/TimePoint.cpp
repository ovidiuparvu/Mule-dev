#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <algorithm>
#include <iterator>

using namespace multiscale;
using namespace multiscale::verification;
using namespace multiscale::verification::subsetspecific;


TimePoint::TimePoint(unsigned long value) {
    this->value             = value;
    this->spatialEntities   = std::vector<std::list<shared_ptr<SpatialEntity>>>(NR_SUBSET_SPECIFIC_TYPES);

    this->consideredSpatialEntityTypes.reset();
}

TimePoint::TimePoint(const TimePoint &timePoint) : value(timePoint.value), spatialEntities(timePoint.spatialEntities),
                                                   numericStateVariables(timePoint.numericStateVariables),
                                                   consideredSpatialEntityTypes(timePoint.consideredSpatialEntityTypes) {}

TimePoint::~TimePoint() {}

unsigned long TimePoint::getValue() const {
    return value;
}

void TimePoint::setValue(unsigned long value) {
    this->value = value;
}

std::bitset<NR_SUBSET_SPECIFIC_TYPES> TimePoint::getConsideredSpatialEntityTypes() {
    return consideredSpatialEntityTypes;
}

void TimePoint::setConsideredSpatialEntityType(const SubsetSpecificType &consideredSpatialEntityType) {
    validateSubsetSpecificType(consideredSpatialEntityType);

    consideredSpatialEntityTypes.reset();
    consideredSpatialEntityTypes.set(computeSubsetSpecificTypeIndex(consideredSpatialEntityType));
}

double TimePoint::numberOfSpatialEntities() const {
    double nrOfSpatialEntities = 0;

    for (size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        if (consideredSpatialEntityTypes[i] == true) {
            nrOfSpatialEntities += static_cast<double>((spatialEntities[i]).size());
        }
    }

    return nrOfSpatialEntities;
}

double TimePoint::avgClusteredness() const {
    std::vector<std::shared_ptr<SpatialEntity>> consideredSpatialEntities = getConsideredSpatialEntities();

    return avgDistanceBetweenCentroids(consideredSpatialEntities);
}

double TimePoint::avgDensity() const {
    std::vector<std::shared_ptr<SpatialEntity>> consideredSpatialEntities = getConsideredSpatialEntities();

    double averageDensity  = avgDensity(consideredSpatialEntities);
    double averageDistance = avgDistanceBetweenCentroids(consideredSpatialEntities);

    return (averageDistance == 0) ? averageDensity
                                  : (averageDensity / averageDistance);
}

void TimePoint::addSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                 const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    std::size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    (spatialEntities[spatialEntityTypeIndex]).push_back(spatialEntity);
}

void TimePoint::addNumericStateVariable(const std::string &name, double value) {
    numericStateVariables[name] = value;
}

bool TimePoint::existsNumericStateVariable(const std::string &name) {
    return (numericStateVariables.find(name) != numericStateVariables.end());
}

std::list<std::shared_ptr<SpatialEntity>>::iterator TimePoint::getSpatialEntitiesBeginIterator(
                                                        const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    if (consideredSpatialEntityTypes[spatialEntityTypeIndex] == true) {
        return (spatialEntities[spatialEntityTypeIndex]).begin();
    } else {
        return (spatialEntities[spatialEntityTypeIndex]).end();
    }
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator TimePoint::getSpatialEntitiesBeginIterator(
                                                              const SubsetSpecificType &spatialEntityType) const {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    if (consideredSpatialEntityTypes[spatialEntityTypeIndex] == true) {
        return (spatialEntities[spatialEntityTypeIndex]).begin();
    } else {
        return (spatialEntities[spatialEntityTypeIndex]).end();
    }
}

std::list<std::shared_ptr<SpatialEntity>>::iterator TimePoint::getSpatialEntitiesEndIterator(
                                                        const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return (spatialEntities[spatialEntityTypeIndex]).end();
}

std::list<std::shared_ptr<SpatialEntity>>::const_iterator TimePoint::getSpatialEntitiesEndIterator(
                                                             const SubsetSpecificType &spatialEntityType) const {
    validateSubsetSpecificType(spatialEntityType);

    size_t spatialEntityTypeIndex = computeSubsetSpecificTypeIndex(spatialEntityType);

    return (spatialEntities[spatialEntityTypeIndex]).end();
}

std::vector<std::shared_ptr<SpatialEntity>> TimePoint::getConsideredSpatialEntities() const {
    std::vector<std::shared_ptr<SpatialEntity>> consideredSpatialEntities;

    for (size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        if (consideredSpatialEntityTypes[i] == true) {
            consideredSpatialEntities.insert(consideredSpatialEntities.begin(), (spatialEntities[i]).begin(),
                                             (spatialEntities[i]).end());
        }
    }

    return consideredSpatialEntities;
}

double TimePoint::getNumericStateVariable(const std::string &name) const {
    auto it = numericStateVariables.find(name);

    if (it == numericStateVariables.end()) {
        MS_throw_detailed(SpatialTemporalException, ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX,
                          name, ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX);
    }

    return it->second;
}

void TimePoint::timePointDifference(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Difference);
}

void TimePoint::timePointIntersection(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Intersection);
}

void TimePoint::timePointUnion(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SubsetOperationType::Union);
}

std::list<std::shared_ptr<SpatialEntity>>::iterator
TimePoint::removeSpatialEntity(std::list<std::shared_ptr<SpatialEntity>>::iterator &position,
                               const SubsetSpecificType &spatialEntityType) {
    validateSubsetSpecificType(spatialEntityType);

    return spatialEntities[computeSubsetSpecificTypeIndex(spatialEntityType)].erase(position);
}

double TimePoint::avgDistanceBetweenCentroids(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
    double      distanceSum         = 0;
    std::size_t nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity1 : spatialEntities) {
        for (const auto &spatialEntity2 : spatialEntities) {
            distanceSum += Geometry2D::distanceBtwPoints((*spatialEntity1).getCentroidX(), (*spatialEntity1).getCentroidY(),
                                                         (*spatialEntity2).getCentroidX(), (*spatialEntity2).getCentroidY());
        }
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (distanceSum / (nrOfSpatialEntities * nrOfSpatialEntities));
}

double TimePoint::avgDensity(const std::vector<std::shared_ptr<SpatialEntity>> &spatialEntities) const {
    double      densitySum          = 0;
    std::size_t nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity : spatialEntities) {
        densitySum += (*spatialEntity).getDensity();
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (densitySum / nrOfSpatialEntities);
}

void TimePoint::timePointSetOperation(const TimePoint &timePoint, const SubsetOperationType &setOperationType) {
    updateSpatialEntities(timePoint, setOperationType);
    updateConsideredSpatialEntityTypes(timePoint.consideredSpatialEntityTypes, setOperationType);
}

void TimePoint::updateSpatialEntities(const TimePoint &timePoint, const SubsetOperationType &setOperationType) {
    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        SubsetSpecificType subsetSpecificType = computeSubsetSpecificType(i);

        spatialEntitiesSetOperation(timePoint, setOperationType, subsetSpecificType);
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
            std::set_difference(getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                getSpatialEntitiesEndIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesEndIterator(spatialEntitiesType),
                                std::inserter(newSpatialEntities, newSpatialEntities.begin()));
            break;

        case SubsetOperationType::Union:
            std::set_difference(getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                getSpatialEntitiesEndIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesBeginIterator(spatialEntitiesType),
                                timePoint.getSpatialEntitiesEndIterator(spatialEntitiesType),
                                std::inserter(newSpatialEntities, newSpatialEntities.begin()));
            break;
    }

    return newSpatialEntities;
}

void TimePoint::updateConsideredSpatialEntityTypes(const std::bitset<NR_SUBSET_SPECIFIC_TYPES> &consideredSpatialEntityTypes,
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


// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX      = "The numeric state variable identified by the given name (";
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX      = ") does not exist.";
