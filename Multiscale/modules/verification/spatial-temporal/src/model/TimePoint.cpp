#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

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

double TimePoint::getNumericStateVariable(const std::string &name) const {
    std::map<std::string, double>::const_iterator it = numericStateVariables.find(name);

    if (it == numericStateVariables.end()) {
        MS_throw_detailed(SpatialTemporalException, ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX,
                          name, ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX);
    }

    return it->second;
}

void TimePoint::removeCluster(const std::set<Cluster>::iterator &position) {
    clusters.erase(position);
}

void TimePoint::removeRegion(const std::set<Region>::iterator &position) {
    regions.erase(position);
}

void TimePoint::setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType) {
    this->consideredSpatialEntityType = consideredSpatialEntityType;
}


// Constants
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX = "The numeric state variable identified by the given name (";
const std::string TimePoint::ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX = ") does not exist.";
