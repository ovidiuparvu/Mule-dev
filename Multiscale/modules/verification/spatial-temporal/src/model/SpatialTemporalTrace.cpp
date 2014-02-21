#include "multiscale/exception/IndexOutOfBoundsException.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

using namespace multiscale::verification;


SpatialTemporalTrace::SpatialTemporalTrace() {}

SpatialTemporalTrace::~SpatialTemporalTrace() {
    timePoints.clear();
}

void SpatialTemporalTrace::addTimePoint(const TimePoint &timePoint) {
    timePoints.push_back(timePoint);
}

TimePoint &SpatialTemporalTrace::getTimePoint(unsigned int index) {
    validateIndex(index);

    return timePoints.at(index);
}

unsigned int SpatialTemporalTrace::length() {
    return timePoints.size();
}

SpatialTemporalTrace SpatialTemporalTrace::subTrace(unsigned int startIndex) {
    validateIndex(startIndex);

    return getSubTrace(startIndex);
}

SpatialTemporalTrace SpatialTemporalTrace::getSubTrace(unsigned int startIndex) {
    SpatialTemporalTrace subTrace;

    unsigned int nrOfTimePoints = timePoints.size();

    for (unsigned int i = startIndex; i < nrOfTimePoints; i++) {
        subTrace.addTimePoint(timePoints[i]);
    }

    return subTrace;
}

void SpatialTemporalTrace::validateIndex(unsigned int index) {
    if (index >= timePoints.size()) {
        MS_throw(IndexOutOfBoundsException, ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS);
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS = "The provided timepoint index is out of bounds.";
