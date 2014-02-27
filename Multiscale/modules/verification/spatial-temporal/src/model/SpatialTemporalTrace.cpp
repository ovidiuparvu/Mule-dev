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

unsigned int SpatialTemporalTrace::length() const {
    return timePoints.size();
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::subTrace(unsigned int startIndex) {
    validateIndex(startIndex);

    return getSubTrace(startIndex);
}

SpatialTemporalTrace::Iterator SpatialTemporalTrace::subTrace(unsigned int startIndex, unsigned int endIndex) {
    validateIndices(startIndex, endIndex);

    return getSubTrace(startIndex, endIndex);
}

SpatialTemporalTrace SpatialTemporalTrace::subTrace(unsigned long startValue, unsigned long endValue) {
    SpatialTemporalTrace subTrace;

    validateValues(startValue, endValue);
    getSubTrace(subTrace, startValue, endValue);

    return subTrace;
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

int SpatialTemporalTrace::indexOfFirstTimePointGreaterOrEqualToValue(unsigned long value) {
    unsigned int nrOfTimePoints = timePoints.size();
    double currentValue = -1;

    for (int i = 0; i < nrOfTimePoints; i++) {
        currentValue = timePoints[i].getValue();

        if (Numeric::greaterOrEqual(currentValue, value)) {
            return i;
        }
    }

    return TIMEPOINT_INDEX_NOT_FOUND;
}

int SpatialTemporalTrace::indexOfLastTimePointLessOrEqualToValue(unsigned long value) {
    unsigned int nrOfTimePoints = timePoints.size();
    double currentValue = -1;

    for (int i = (nrOfTimePoints - 1); i >= 0; i--) {
        currentValue = timePoints[i].getValue();

        if (Numeric::lessOrEqual(currentValue, value)) {
            return i;
        }
    }

    return TIMEPOINT_INDEX_NOT_FOUND;
}

void SpatialTemporalTrace::getSubTrace(SpatialTemporalTrace &subTrace, unsigned long startValue, unsigned long endValue) {
    int startIndex = indexOfFirstTimePointGreaterOrEqualToValue(startValue);
    int endIndex = indexOfLastTimePointLessOrEqualToValue(endValue);

    if (startIndex == TIMEPOINT_INDEX_NOT_FOUND) {
        // Do not add any timepoints to subTrace
    } else {
        if (endIndex == TIMEPOINT_INDEX_NOT_FOUND) {
            addTimePointsToSubTrace(subTrace, startIndex, timePoints.size() - 1);
        } else {
            addTimePointsToSubTrace(subTrace, startIndex, endIndex);
        }
    }
}

void SpatialTemporalTrace::addTimePointsToSubTrace(SpatialTemporalTrace &subTrace, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; i++) {
        subTrace.addTimePoint(timePoints[i]);
    }
}

void SpatialTemporalTrace::validateIndices(unsigned int startIndex, unsigned int endIndex) {
    validateIndex(startIndex);
    validateIndex(endIndex);

    if (endIndex < startIndex) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_END_START,
                          StringManipulator::toString<unsigned int>(endIndex) +
                          ERR_TIMEPOINT_END_MIDDLE +
                          StringManipulator::toString<unsigned int>(startIndex),
                          ERR_TIMEPOINT_END_END);
    }
}

void SpatialTemporalTrace::validateValues(unsigned long startValue, unsigned long endValue) {
    validateIndex(startValue);
    validateIndex(endValue);

    if (endValue < startValue) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_END_START,
                          StringManipulator::toString<double>(endValue) +
                          ERR_TIMEPOINT_END_MIDDLE +
                          StringManipulator::toString<double>(startValue),
                          ERR_TIMEPOINT_END_END);
    }
}

void SpatialTemporalTrace::validateIndex(unsigned int index) {
    if (index >= timePoints.size()) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<unsigned int>(index), ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END);
    }
}

void SpatialTemporalTrace::validateValue(unsigned long value) {
    if (Numeric::greaterOrEqual(value, timePoints[timePoints.size() - 1].getValue())) {
        MS_throw_detailed(SpatialTemporalException, ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START,
                          StringManipulator::toString<double>(value), ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END);
    }
}


// Constants
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START = "The provided timepoint (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END   = ") is out of bounds.";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_START     = "The provided end timepoint (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_MIDDLE    = ") should be greater or equal to the start timepoint  (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_END_END       = ").";

const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_START   = "The current timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_MIDDLE  = ") should be greater than the previously added timepoint value (";
const std::string SpatialTemporalTrace::ERR_TIMEPOINT_VALUE_INVALID_END     = ").";

const std::string SpatialTemporalTrace::ERR_ITERATOR_NEXT           = "There is no next timepoint which the iterator can"
                                                                      " return. Please use the hasNext() method before"
                                                                      " to ensure there are further timepoints available"
                                                                      " before calling the next() method.";

const int SpatialTemporalTrace::TIMEPOINT_INDEX_NOT_FOUND = -1;


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
