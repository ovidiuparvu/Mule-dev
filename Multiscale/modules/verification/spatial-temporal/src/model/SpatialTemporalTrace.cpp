#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

using namespace multiscale::verification;


SpatialTemporalTrace::SpatialTemporalTrace() {
    initialise();
}

SpatialTemporalTrace::SpatialTemporalTrace(const SpatialTemporalTrace &trace)
                                          : beginIndex(trace.beginIndex), timePoints(trace.timePoints),
                                            lastTimePointValue(trace.lastTimePointValue),
                                            isLastTimePointValueInitialised(trace.isLastTimePointValueInitialised) {}

SpatialTemporalTrace::~SpatialTemporalTrace() {}

void SpatialTemporalTrace::addTimePoint(const TimePoint &timePoint) {
    validateTimePointValue(timePoint);

    timePoints.push_back(timePoint);

    updateLastTimePointValue(timePoints.back());
}

void SpatialTemporalTrace::clear() {
    initialise();
}

TimePoint SpatialTemporalTrace::getTimePoint(unsigned int index) const {
    validateIndex(index);

    return timePoints[beginIndex + index];
}

unsigned int SpatialTemporalTrace::length() const {
    return (timePoints.size() - beginIndex);
}

SpatialTemporalTrace SpatialTemporalTrace::subTrace(unsigned int startIndex) const {
    SpatialTemporalTrace subTrace;

    validateIndex(startIndex);
    addTimePointsToSubTrace(subTrace, startIndex + beginIndex, timePoints.size() - 1);

    return subTrace;
}

void SpatialTemporalTrace::setSubTrace(unsigned long startValue) {
    validateValue(startValue);
    setSubTraceIndex(startValue);
}

void SpatialTemporalTrace::resetSubTraceStartIndex() {
    beginIndex = 0;
}

void SpatialTemporalTrace::initialise() {
    beginIndex = 0;

    timePoints.clear();

    lastTimePointValue = 0;
    isLastTimePointValueInitialised = false;
}

void SpatialTemporalTrace::updateLastTimePointValue(TimePoint &timePoint) {
    unsigned long timePointValue = timePoint.getValue();

    if (timePointValue == numeric_limits<unsigned long>::max()) {
        timePoint.setValue(++lastTimePointValue);
    } else {
        lastTimePointValue = timePointValue;
    }
}

void SpatialTemporalTrace::validateTimePointValue(const TimePoint &timePoint) {
    unsigned long timePointValue = timePoint.getValue();

    validateTimePointValue(timePointValue);
}

void SpatialTemporalTrace::validateTimePointValue(unsigned long timePointValue) {
    if (isLastTimePointValueInitialised) {
        if (timePointValue <= lastTimePointValue) {
            MS_throw_detailed(SpatialTemporalException,
                              ERR_TIMEPOINT_VALUE_INVALID_START,
                              StringManipulator::toString<unsigned long>(timePointValue) +
                              ERR_TIMEPOINT_VALUE_INVALID_MIDDLE +
                              StringManipulator::toString<unsigned long>(lastTimePointValue),
                              ERR_TIMEPOINT_VALUE_INVALID_END);
        }
    } else {
        isLastTimePointValueInitialised = true;
    }
}

void SpatialTemporalTrace::setSubTraceIndex(unsigned long startValue) {
    int startIndex = indexOfFirstTimePointGreaterOrEqualToValue(startValue);

    if (startIndex == TIMEPOINT_INDEX_NOT_FOUND) {
        beginIndex = timePoints.size();
    } else {
        beginIndex = startIndex;
    }
}

void SpatialTemporalTrace::addTimePointsToSubTrace(SpatialTemporalTrace &subTrace,
                                                   int startIndex, int endIndex) const {
    for (int i = startIndex; i <= endIndex; i++) {
        subTrace.addTimePoint(timePoints[i]);
    }
}

int SpatialTemporalTrace::indexOfFirstTimePointGreaterOrEqualToValue(unsigned long value) const {
    unsigned int  totalNrOfTimePoints = timePoints.size();
    unsigned long currentValue        = -1;

    for (unsigned int i = beginIndex; i < totalNrOfTimePoints; i++) {
        currentValue = timePoints[i].getValue();

        if (currentValue >= value) {
            return i;
        }
    }

    return TIMEPOINT_INDEX_NOT_FOUND;
}

void SpatialTemporalTrace::validateIndex(unsigned int index) const {
    if ((beginIndex + index) >= timePoints.size()) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<unsigned int>(index), ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END);
    }
}

void SpatialTemporalTrace::validateValue(unsigned long value) const {
    if (value > timePoints.back().getValue()) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<double>(value), ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END);
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START = "The provided timepoint index (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START = "The provided timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_START     = "The provided end timepoint (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_MIDDLE    = ") should be greater or equal to the start timepoint  (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_END       = ").";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_START   = "The current timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_MIDDLE  = ") should be greater than the previously added timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_END     = ").";

const std::string SpatialTemporalTrace::ERR_ITERATOR_NEXT   = "There is no next timepoint which the iterator can"
                                                              " return. Please use the hasNext() method before"
                                                              " to ensure there are further timepoints available"
                                                              " before calling the next() method.";

const int SpatialTemporalTrace::TIMEPOINT_INDEX_NOT_FOUND = -1;
