#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <algorithm>
#include <iterator>

using namespace multiscale;
using namespace multiscale::verification;


TimePoint::TimePoint(unsigned long value) {
    this->value = value;
    this->consideredSpatialEntityType = ConsideredSpatialEntityType::All;
}

TimePoint::TimePoint(const TimePoint &timePoint) {
    this->value                         = timePoint.value;
    this->clusters                      = timePoint.clusters;
    this->regions                       = timePoint.regions;
    this->numericStateVariables         = timePoint.numericStateVariables;
    this->consideredSpatialEntityType   = timePoint.consideredSpatialEntityType;
}

TimePoint::~TimePoint() {
    clusters.clear();
    regions.clear();
    numericStateVariables.clear();
}

unsigned long TimePoint::getValue() const {
    return value;
}

void TimePoint::setValue(unsigned long value) {
    this->value = value;
}

ConsideredSpatialEntityType TimePoint::getConsideredSpatialEntityType() {
    return consideredSpatialEntityType;
}

void TimePoint::setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType) {
    this->consideredSpatialEntityType = consideredSpatialEntityType;
}

double TimePoint::numberOfSpatialEntities() const {
    switch(consideredSpatialEntityType) {
        case ConsideredSpatialEntityType::All:
            return (static_cast<double>(clusters.size()) + static_cast<double>(regions.size()));

        case ConsideredSpatialEntityType::Clusters:
            return (static_cast<double>(clusters.size()));

        case ConsideredSpatialEntityType::Regions:
            return (static_cast<double>(regions.size()));
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0.0;
}

double TimePoint::avgClusteredness() const {
    std::vector<SpatialEntity> consideredSpatialEntities;

    return avgDistanceBetweenCentroids(consideredSpatialEntities);
}

double TimePoint::avgDensity() const {
    std::vector<SpatialEntity> consideredSpatialEntities;

    double averageDensity  = avgDensity(consideredSpatialEntities);
    double averageDistance = avgDistanceBetweenCentroids(consideredSpatialEntities);

    return (averageDensity == 0) ? 0
                                 : (averageDensity / averageDistance);
}

void TimePoint::addCluster(const Cluster &cluster) {
    this->clusters.insert(cluster);
}

void TimePoint::addRegion(const Region &region) {
    this->regions.insert(region);
}

void TimePoint::addNumericStateVariable(const std::string &name, double value) {
    numericStateVariables[name] = value;
}

bool TimePoint::existsNumericStateVariable(const std::string &name) {
    return (numericStateVariables.find(name) != numericStateVariables.end());
}

std::set<Cluster> TimePoint::getClusters() const {
    return clusters;
}

std::set<Region> TimePoint::getRegions() const {
    return regions;
}

std::vector<SpatialEntity> TimePoint::getConsideredSpatialEntities() const {
    std::vector<SpatialEntity> consideredSpatialEntities;

    switch (consideredSpatialEntityType) {
        case ConsideredSpatialEntityType::All:
            consideredSpatialEntities.insert(consideredSpatialEntities.begin(), clusters.begin(), clusters.end());
            consideredSpatialEntities.insert(consideredSpatialEntities.begin(), regions.begin(), regions.end());
            break;

        case ConsideredSpatialEntityType::Clusters:
            consideredSpatialEntities.insert(consideredSpatialEntities.begin(), clusters.begin(), clusters.end());
            break;

        case ConsideredSpatialEntityType::Regions:
            consideredSpatialEntities.insert(consideredSpatialEntities.begin(), regions.begin(), regions.end());
            break;
    }

    return consideredSpatialEntities;
}

double TimePoint::getNumericStateVariable(const std::string &name) const {
    std::map<std::string, double>::const_iterator it = numericStateVariables.find(name);

    if (it == numericStateVariables.end()) {
        MS_throw_detailed(SpatialTemporalException, ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX,
                          name, ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX);
    }

    return it->second;
}

void TimePoint::timePointDifference(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SetOperationType::Difference);
}

void TimePoint::timePointIntersection(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SetOperationType::Intersection);
}

void TimePoint::timePointUnion(const TimePoint &timePoint) {
    timePointSetOperation(timePoint, SetOperationType::Union);
}

void TimePoint::removeCluster(const std::set<Cluster>::iterator &position) {
    clusters.erase(position);
}

void TimePoint::removeRegion(const std::set<Region>::iterator &position) {
    regions.erase(position);
}

double TimePoint::avgDistanceBetweenCentroids(const std::vector<SpatialEntity> &spatialEntities) const {
    double distanceSum = 0;
    int nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity1 : spatialEntities) {
        for (const auto &spatialEntity2 : spatialEntities) {
            distanceSum += Geometry2D::distanceBtwPoints(spatialEntity1.getCentroidX(), spatialEntity1.getCentroidY(),
                                                         spatialEntity2.getCentroidX(), spatialEntity2.getCentroidY());
        }
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      : (distanceSum / (nrOfSpatialEntities * nrOfSpatialEntities));
}

double TimePoint::avgDensity(const std::vector<SpatialEntity> &spatialEntities) const {
    double densitySum = 0;
    int nrOfSpatialEntities = spatialEntities.size();

    for (const auto &spatialEntity : spatialEntities) {
        densitySum += spatialEntity.getDensity();
    }

    return (nrOfSpatialEntities == 0) ? 0
                                      :(densitySum / nrOfSpatialEntities);
}

void TimePoint::timePointSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    switch (consideredSpatialEntityType) {
        case ConsideredSpatialEntityType::All:
            timePointSetOperationAll(timePoint, setOperationType);
            break;

        case ConsideredSpatialEntityType::Clusters:
            timePointSetOperationClusters(timePoint, setOperationType);
            break;

        case ConsideredSpatialEntityType::Regions:
            timePointSetOperationRegions(timePoint, setOperationType);
            break;
    }
}

void TimePoint::timePointSetOperationAll(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    clusters = clustersSetOperation(timePoint, setOperationType);
    regions  = regionsSetOperation(timePoint, setOperationType);
}

void TimePoint::timePointSetOperationClusters(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    clusters = clustersSetOperation(timePoint, setOperationType);
}

void TimePoint::timePointSetOperationRegions(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    regions  = regionsSetOperation(timePoint, setOperationType);
}

std::set<Cluster> TimePoint::clustersSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    std::set<Cluster> newClusters;
    std::set<Cluster> timePointClusters = timePoint.getClusters();

    switch(setOperationType) {
        case SetOperationType::Difference:
            std::set_difference(clusters.begin(), clusters.end(), timePointClusters.begin(),
                                timePointClusters.end(), std::inserter(newClusters, newClusters.begin()));
            break;

        case SetOperationType::Intersection:
            std::set_intersection(clusters.begin(), clusters.end(), timePointClusters.begin(),
                                  timePointClusters.end(), std::inserter(newClusters, newClusters.begin()));
            break;

        case SetOperationType::Union:
            std::set_union(clusters.begin(), clusters.end(), timePointClusters.begin(),
                           timePointClusters.end(), std::inserter(newClusters, newClusters.begin()));
            break;
    }

    return newClusters;
}

std::set<Region> TimePoint::regionsSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType) {
    std::set<Region> newRegions;
    std::set<Region> timePointRegions = timePoint.getRegions();

    switch(setOperationType) {
        case SetOperationType::Difference:
            std::set_difference(regions.begin(), regions.end(), timePointRegions.begin(),
                                timePointRegions.end(), std::inserter(newRegions, newRegions.begin()));
            break;

        case SetOperationType::Intersection:
            std::set_intersection(regions.begin(), regions.end(), timePointRegions.begin(),
                                  timePointRegions.end(), std::inserter(newRegions, newRegions.begin()));
            break;

        case SetOperationType::Union:
            std::set_union(regions.begin(), regions.end(), timePointRegions.begin(),
                           timePointRegions.end(), std::inserter(newRegions, newRegions.begin()));
            break;
    }

    return newRegions;
}


// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX = "The numeric state variable identified by the given name (";
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX = ") does not exist.";
