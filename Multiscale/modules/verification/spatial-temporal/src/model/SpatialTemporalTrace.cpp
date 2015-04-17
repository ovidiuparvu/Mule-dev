#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <limits>

using namespace multiscale::verification;


SpatialTemporalTrace::SpatialTemporalTrace() {
    initialize();
}

SpatialTemporalTrace::SpatialTemporalTrace(const SpatialTemporalTrace &trace)
                                          : beginIndex(trace.beginIndex), timePoints(trace.timePoints),
                                            lastTimePointValue(trace.lastTimePointValue),
                                            isLastTimePointValueInitialized(trace.isLastTimePointValueInitialized) {}

SpatialTemporalTrace::~SpatialTemporalTrace() {}

void SpatialTemporalTrace::addTimePoint(const TimePoint &timePoint) {
    validateTimePointValue(timePoint);

    timePoints.push_back(timePoint);

    updateLastTimePointValue(timePoints.back());
}

void SpatialTemporalTrace::clear() {
    initialize();
}

TimePoint SpatialTemporalTrace::getTimePoint(unsigned int index) const {
    validateIndexRelativeToBeginIndex(index);

    return timePoints[beginIndex + index];
}

TimePoint& SpatialTemporalTrace::getTimePointReference(unsigned int index) {
    validateIndexRelativeToBeginIndex(index);

    return timePoints[beginIndex + index];
}

const TimePoint& SpatialTemporalTrace::getTimePointReference(unsigned int index) const {
    validateIndexRelativeToBeginIndex(index);

    return timePoints[beginIndex + index];
}

unsigned int SpatialTemporalTrace::length() const {
    return (timePoints.size() - beginIndex);
}

unsigned long SpatialTemporalTrace::nextTimePointValue() const {
    if (beginIndex == (static_cast<unsigned long>(timePoints.size()) - 1)) {
        return nextTimePointValueForLastTimePoint();
    } else {
        return (timePoints[beginIndex + 1].getValue());
    }
}

void SpatialTemporalTrace::setSubTraceWithTimepointsValuesGreaterOrEqualTo(unsigned long startValue) {
    validateValue(startValue);
    setSubTraceIndex(startValue);
}

void SpatialTemporalTrace::advanceTraceBeginIndex(unsigned long advanceValue) {
    // Check if the new begin index value is valid
    validateIndexRelativeToBeginIndex(advanceValue);

    // Update the begin index value
    beginIndex = beginIndex + advanceValue;
}

void SpatialTemporalTrace::setTraceBeginIndex(unsigned int newBeginIndex) {
    // Check if the provided begin index value is valid
    validateAbsoluteIndex(newBeginIndex);

    // Update the begin index value
    beginIndex = newBeginIndex;
}

void SpatialTemporalTrace::storeSubTraceBeginIndex() {
    // Add the current value of beginIndex to the stack
    beginIndices.push_back(beginIndex);
}

unsigned int SpatialTemporalTrace::getMostRecentlyStoredSubTraceBeginIndex() {
    if (beginIndices.size() > 0) {
        return beginIndices.back();
    } else {
        return 0;
    }
}

void SpatialTemporalTrace::restoreSubTraceBeginIndex() {
    if (beginIndices.size() > 0) {
        // Update the value of beginIndex according to the top stack value
        beginIndex = beginIndices.back();

        // Remove the top value from the beginIndices stack
        beginIndices.pop_back();
    } else {
        beginIndex = 0;
    }
}

bool SpatialTemporalTrace::operator==(const SpatialTemporalTrace &rhsSpatialTemporalTrace) {
    // Compute the number of timepoints in this and the right hand side trace
    std::size_t lhsNrOfTimepoints = timePoints.size();
    std::size_t rhsNrOfTimepoints = rhsSpatialTemporalTrace.timePoints.size();

    // If the number of timepoints in the traces differ then return false
    if (lhsNrOfTimepoints != rhsNrOfTimepoints) {
        return false;
    // Otherwise check if each timepoint from this trace is equal to its corresponding timepoint
    // from the right hand side trace
    } else {
        for (std::size_t i = 0; i < lhsNrOfTimepoints; i++) {
            // If the timepoints are different return false
            if (timePoints[i] != rhsSpatialTemporalTrace.timePoints[i]) {
                return false;
            }
        }

        // Otherwise return true
        return true;
    }
}

void SpatialTemporalTrace::initialize() {
    beginIndex = 0;

    timePoints.clear();

    lastTimePointValue = 0;
    isLastTimePointValueInitialized = false;
}

void SpatialTemporalTrace::updateLastTimePointValue(TimePoint &timePoint) {
    unsigned long timePointValue = timePoint.getValue();

    if (timePointValue == std::numeric_limits<unsigned long>::max()) {
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
    if (isLastTimePointValueInitialized) {
        if (timePointValue <= lastTimePointValue) {
            MS_throw_detailed(
                SpatialTemporalException,
                ERR_TIMEPOINT_VALUE_INVALID_START,
                StringManipulator::toString<unsigned long>(timePointValue) +
                ERR_TIMEPOINT_VALUE_INVALID_MIDDLE +
                StringManipulator::toString<unsigned long>(lastTimePointValue),
                ERR_TIMEPOINT_VALUE_INVALID_END
            );
        }
    } else {
        isLastTimePointValueInitialized = true;
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

unsigned long SpatialTemporalTrace::nextTimePointValueForLastTimePoint() const {
    if (timePoints.back().getValue() == std::numeric_limits<unsigned long>::max()) {
        MS_throw(SpatialTemporalException, ERR_NEXT_TIMEPOINT_VALUE_NOT_EXISTS);
    }

    return std::numeric_limits<unsigned long>::max();
}

void SpatialTemporalTrace::addTimePointsToSubTrace(SpatialTemporalTrace &subTrace,
                                                   int startIndex, int endIndex) const {
    for (int i = startIndex; i <= endIndex; i++) {
        subTrace.addTimePoint(timePoints[i]);
    }
}

int SpatialTemporalTrace::indexOfFirstTimePointGreaterOrEqualToValue(unsigned long value) const {
    std::size_t   totalNrOfTimePoints = timePoints.size();
    unsigned long currentValue        = -1;

    for (std::size_t i = beginIndex; i < totalNrOfTimePoints; i++) {
        currentValue = timePoints[i].getValue();

        if (currentValue >= value) {
            return i;
        }
    }

    return TIMEPOINT_INDEX_NOT_FOUND;
}

void SpatialTemporalTrace::validateIndexRelativeToBeginIndex(unsigned int index) const {
    if ((beginIndex + index) >= timePoints.size()) {
        MS_throw(
            SpatialTemporalException,
            ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START +
            StringManipulator::toString(beginIndex) +
            ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_MIDDLE +
            StringManipulator::toString(index) +
            ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END
        );
    }
}

void SpatialTemporalTrace::validateAbsoluteIndex(unsigned int index) const {
    if (index >= timePoints.size()) {
        MS_throw_detailed(
            SpatialTemporalException,
            ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START,
            StringManipulator::toString(index),
            ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END
        );
    }
}

void SpatialTemporalTrace::validateValue(unsigned long value) const {
    if ((timePoints.size() == 0) || (value > timePoints.back().getValue())) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<double>(value), ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END);
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START    = "Relative to the begin index (";
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_MIDDLE   = ") the provided timepoint index (";
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END      = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START = "The provided timepoint index (";
const std::string SpatialTemporalTrace::ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START = "The provided timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_START     = "The provided end timepoint (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_MIDDLE    = ") should be greater or equal to the start timepoint  (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_END       = ").";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_START   = "The current timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_MIDDLE  = ") should be greater than the previously added timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_END     = ").";

const std::string SpatialTemporalTrace::ERR_NEXT_TIMEPOINT_VALUE_NOT_EXISTS = "The value of the last timepoint is the maximum value which can be represented by an unsigned long. Therefore a next timepoint value, which is greater than the value of the last timepoint, does not exist.";

const std::string SpatialTemporalTrace::ERR_ITERATOR_NEXT   = "There is no next timepoint which the iterator can"
                                                              " return. Please use the hasNext() method before"
                                                              " to ensure there are further timepoints available"
                                                              " before calling the next() method.";

const int SpatialTemporalTrace::TIMEPOINT_INDEX_NOT_FOUND = -1;
