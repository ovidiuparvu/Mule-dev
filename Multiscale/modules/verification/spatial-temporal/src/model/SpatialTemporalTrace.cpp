#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <limits>

using namespace multiscale::verification;


SpatialTemporalTrace::SpatialTemporalTrace() {
    initialize();
}

SpatialTemporalTrace::SpatialTemporalTrace(std::size_t nrOfTimePoints) {
    initialize();

    // Reserve enough memory to hold at least nrOfTimePoints time points
    timePoints.reserve(nrOfTimePoints);
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

double SpatialTemporalTrace::nextTimePointValue() const {
    if ((beginIndex + 1) == (static_cast<unsigned int>(timePoints.size()))) {
        return nextTimePointValueForLastTimePoint();
    } else {
        return (timePoints[beginIndex + 1].getValue());
    }
}

void SpatialTemporalTrace::setSubTraceWithTimePointsValuesGreaterOrEqualTo(double startValue) {
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
    // Compute the number of time points in this and the right hand side trace
    std::size_t lhsNrOfTimePoints = timePoints.size();
    std::size_t rhsNrOfTimePoints = rhsSpatialTemporalTrace.timePoints.size();

    // If the number of time points in the traces differ then return false
    if (lhsNrOfTimePoints != rhsNrOfTimePoints) {
        return false;
    // Otherwise check if each time point from this trace is equal to its corresponding time point
    // from the right hand side trace
    } else {
        for (std::size_t i = 0; i < lhsNrOfTimePoints; i++) {
            // If the time points are different return false
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
    double timePointValue = timePoint.getValue();

    // If the time point value is not explicitly given then set it to
    // (last time point value + 1) and increment last time point value
    if (Numeric::almostEqual(timePointValue, std::numeric_limits<double>::max())) {
        timePoint.setValue(++lastTimePointValue);
    // Otherwise update the last time point value
    } else {
        lastTimePointValue = timePointValue;
    }
}

void SpatialTemporalTrace::validateTimePointValue(const TimePoint &timePoint) {
    double timePointValue = timePoint.getValue();

    validateTimePointValue(timePointValue);
}

void SpatialTemporalTrace::validateTimePointValue(double timePointValue) {
    if (isLastTimePointValueInitialized) {
        if (Numeric::lessOrEqual(timePointValue, lastTimePointValue)) {
            MS_throw_detailed(
                SpatialTemporalException,
                ERR_TIMEPOINT_VALUE_INVALID_START,
                StringManipulator::toString<double>(timePointValue) +
                ERR_TIMEPOINT_VALUE_INVALID_MIDDLE +
                StringManipulator::toString<double>(lastTimePointValue),
                ERR_TIMEPOINT_VALUE_INVALID_END
            );
        }
    } else {
        isLastTimePointValueInitialized = true;
    }
}

void SpatialTemporalTrace::setSubTraceIndex(double startValue) {
    int startIndex = indexOfFirstTimePointGreaterOrEqualToValue(startValue);

    if (startIndex == TIMEPOINT_INDEX_NOT_FOUND) {
        beginIndex = timePoints.size();
    } else {
        beginIndex = startIndex;
    }
}

double SpatialTemporalTrace::nextTimePointValueForLastTimePoint() const {
    if (Numeric::almostEqual(timePoints.back().getValue(), std::numeric_limits<double>::max())) {
        MS_throw(SpatialTemporalException, ERR_NEXT_TIMEPOINT_VALUE_NOT_EXISTS);
    }

    return std::numeric_limits<double>::max();
}

void SpatialTemporalTrace::addTimePointsToSubTrace(SpatialTemporalTrace &subTrace,
                                                   int startIndex, int endIndex) const {
    for (int i = startIndex; i <= endIndex; i++) {
        subTrace.addTimePoint(timePoints[i]);
    }
}

int SpatialTemporalTrace::indexOfFirstTimePointGreaterOrEqualToValue(double value) const {
    std::size_t totalNrOfTimePoints = timePoints.size();
    double      currentValue        = -1;

    for (std::size_t i = beginIndex; i < totalNrOfTimePoints; i++) {
        currentValue = timePoints[i].getValue();

        if (Numeric::greaterOrEqual(currentValue, value)) {
            return (static_cast<int>(i));
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

void SpatialTemporalTrace::validateValue(double value) const {
    if ((timePoints.size() == 0) || (value > timePoints.back().getValue())) {
        MS_throw_detailed(
            SpatialTemporalException,
            ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START,
            StringManipulator::toString<double>(value),
            ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END
        );
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START    = "Relative to the begin index (";
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_MIDDLE   = ") the provided time point index (";
const std::string SpatialTemporalTrace::ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END      = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START = "The provided time point index (";
const std::string SpatialTemporalTrace::ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START = "The provided time point value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END   = ") is out of bounds for the given spatial temporal trace.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_START     = "The provided end time point (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_MIDDLE    = ") should be greater or equal to the start time point  (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_END       = ").";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_START   = "The current time point value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_MIDDLE  = ") should be greater than the previously added time point value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_END     = ").";

const std::string SpatialTemporalTrace::ERR_NEXT_TIMEPOINT_VALUE_NOT_EXISTS = "The value of the last time point is the maximum value which can be represented by a double. Therefore a next time point value, which is greater than the value of the last time point, does not exist.";

const std::string SpatialTemporalTrace::ERR_ITERATOR_NEXT   = "There is no next time point which the iterator can"
                                                              " return. Please use the hasNext() method before"
                                                              " to ensure there are further time points available"
                                                              " before calling the next() method.";

const int SpatialTemporalTrace::TIMEPOINT_INDEX_NOT_FOUND = -1;
