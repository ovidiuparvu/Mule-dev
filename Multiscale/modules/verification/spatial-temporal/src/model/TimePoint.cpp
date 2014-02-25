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

double TimePoint::getNumericStateVariable(const std::string &name) const {
    std::map<std::string, double>::const_iterator it = numericStateVariables.find(name);

    if (it == numericStateVariables.end()) {
        MS_throw(UnexpectedBehaviourException, constructErrorMessage(name));
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

std::string TimePoint::constructErrorMessage(const std::string &errorString) const {
    return (ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX + errorString + ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX);
}

// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX = "The numeric state variable identified by the given name (";
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX = ") does not exist.";
