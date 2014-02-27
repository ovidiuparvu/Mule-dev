#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

using namespace multiscale::verification;


SpatialTemporalTrace::SpatialTemporalTrace() {
    lastTimePointValue = -1;
}

SpatialTemporalTrace::~SpatialTemporalTrace() {
    timePoints.clear();
}

void SpatialTemporalTrace::addTimePoint(TimePoint &timePoint) {
    updateLastTimePointValue(timePoint);

    timePoints.push_back(timePoint);
}

TimePoint &SpatialTemporalTrace::getTimePoint(unsigned int index) {
    validateIndex(index);

    return timePoints.at(index);
}

unsigned int SpatialTemporalTrace::length() {
    return timePoints.size();
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::subTrace(unsigned int startIndex) {
    validateIndex(startIndex);

    return getSubTrace(startIndex);
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::subTrace(unsigned int startIndex, unsigned int endIndex) {
    validateIndex(startIndex);

    return getSubTrace(startIndex, endIndex);
}

void SpatialTemporalTrace::updateLastTimePointValue(TimePoint &timePoint) {
    double timePointValue = timePoint.getValue();

    validateTimePointValue(timePointValue);
    updateLastTimePointValue(timePoint, timePointValue);
}

void SpatialTemporalTrace::updateLastTimePointValue(TimePoint &timePoint, double timePointValue) {
    if (Numeric::almostEqual(timePointValue, -1)) {
        timePoint.setValue(++lastTimePointValue);
    } else {
        lastTimePointValue = timePointValue;
    }
}

void SpatialTemporalTrace::validateTimePointValue(double timePointValue) {
    if (Numeric::greaterOrEqual(timePointValue, 0)) {
        if (Numeric::lessOrEqual(timePointValue, lastTimePointValue)) {
            MS_throw_detailed(SpatialTemporalException,
                              ERR_TIMEPOINT_VALUE_INVALID_START,
                              StringManipulator::toString<double>(timePointValue) +
                              ERR_TIMEPOINT_VALUE_INVALID_MIDDLE +
                              StringManipulator::toString<double>(lastTimePointValue),
                              ERR_TIMEPOINT_VALUE_INVALID_END);
        }
    }
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::getSubTrace(unsigned int startIndex) {
    return SpatialTemporalTrace::Iterator(*this, startIndex, timePoints.size() - 1);
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::getSubTrace(unsigned int startIndex, unsigned int endIndex) {
    return SpatialTemporalTrace::Iterator(*this, startIndex, endIndex);
}

void SpatialTemporalTrace::validateIndices(unsigned int startIndex, unsigned int endIndex) {
    validateIndex(startIndex);
    validateIndex(endIndex);

    if (endIndex <= startIndex) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_END_START,
                          StringManipulator::toString<unsigned int>(endIndex) +
                          ERR_TIMEPOINT_END_MIDDLE +
                          StringManipulator::toString<unsigned int>(startIndex),
                          ERR_TIMEPOINT_END_END);
    }
}

void SpatialTemporalTrace::validateIndex(unsigned int index) {
    if (index >= timePoints.size()) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<unsigned int>(index), ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END);
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START = "The provided timepoint index (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END   = ") is out of bounds.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_START     = "The provided end timepoint index (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_MIDDLE    = ") should be greater or equal to the start timepoint index (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_END       = ").";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_START   = "The current timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_MIDDLE  = ") should be greater than the previously added timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_END     = ").";

const std::string SpatialTemporalTrace::ERR_ITERATOR_NEXT           = "There is no next timepoint which the iterator can"
                                                                      " return. Please use the hasNext() method before"
                                                                      " to ensure there are further timepoints available"
                                                                      " before calling the next() method.";


/////////////////////////////////////////////////////////////////////////////////////////
//
//
//  Inner class "Iterator"
//
//
/////////////////////////////////////////////////////////////////////////////////////////

SpatialTemporalTrace::Iterator::Iterator(const SpatialTemporalTrace &trace, unsigned int startIndex,
                                         unsigned int endIndex) {
    this->trace = trace;

    this->startTimePointIndex = startIndex;
    this->endTimePointIndex = endIndex;

    reset();
}

SpatialTemporalTrace::Iterator::~Iterator() {}

TimePoint &SpatialTemporalTrace::Iterator::next() {
    if (!hasNext()) {
        MS_throw(SpatialTemporalException, ERR_ITERATOR_NEXT);
    }

    return trace.timePoints[currentTimePointIndex++];
}

bool SpatialTemporalTrace::Iterator::hasNext() {
    return (currentTimePointIndex <= endTimePointIndex);
}

void SpatialTemporalTrace::Iterator::reset() {
    currentTimePointIndex = startTimePointIndex;
}
