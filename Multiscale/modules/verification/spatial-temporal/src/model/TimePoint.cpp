#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

using namespace multiscale;
using namespace multiscale::verification;


TimePoint::TimePoint(double value) {
    this->value = value;
    this->consideredSpatialEntityType = ConsideredSpatialEntityType::All;
}

TimePoint::~TimePoint() {
    clusters.clear();
    regions.clear();
    numericStateVariables.clear();
}

void TimePoint::addCluster(const Cluster &cluster) {
    this->clusters.push_back(cluster);
}

void TimePoint::addRegion(const Region &region) {
    this->regions.push_back(region);
}

void TimePoint::addNumericStateVariable(const std::string &name, double value) {
    numericStateVariables[name] = value;
}

bool TimePoint::existsNumericStateVariable(const std::string &name) {
    return (numericStateVariables.find(name) != numericStateVariables.end());
}

std::list<Cluster> TimePoint::getClusters() {
    return clusters;
}

std::list<Region> TimePoint::getRegions() {
    return regions;
}

double TimePoint::getNumericStateVariable(const std::string &name) {
    std::map<std::string, double>::iterator it = numericStateVariables.find(name);

    if (it == numericStateVariables.end()) {
        MS_throw(UnexpectedBehaviourException, ERR_GET_NUMERIC_STATE_VARIABLE);
    }

    return it->second;
}

void TimePoint::removeCluster(const std::list<Cluster>::iterator &position) {
    clusters.erase(position);
}

void TimePoint::removeRegion(const std::list<Region>::iterator &position) {
    regions.erase(position);
}

void TimePoint::setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType) {
    this->consideredSpatialEntityType = consideredSpatialEntityType;
}


// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE = "The numeric state variable identified by the given key does not exist.";
