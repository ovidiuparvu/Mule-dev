#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/InvalidOutputException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/data/MSTMLSubfilesMerger.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataWriter.hpp"

#include <cassert>
#include <fstream>

using namespace multiscale::verification;


MSTMLSubfilesMerger::MSTMLSubfilesMerger(const std::string &mstmlSubfilesFolderPath,
                                         const std::string &timePointsValuesFilePath)
                                         : timePointsValuesFilePath(timePointsValuesFilePath),
                                           traceReader(mstmlSubfilesFolderPath) {
    initialize();
}

MSTMLSubfilesMerger::~MSTMLSubfilesMerger() {}

void MSTMLSubfilesMerger::mergeMSTMLSubfiles() {
    addSubtracesToResultingTrace();
    updateResultingTraceTimePointsValues();
}

SpatialTemporalTrace MSTMLSubfilesMerger::getResultingMergedTrace() {
    return resultingTrace;
}

void MSTMLSubfilesMerger::outputResultingMSTMLFile(const std::string &mstmlFileOutputPath) {
    // If the number of time points in the resulting trace is greater than 0 output the trace to an xml file
    if (resultingTrace.length() > 0) {
        SpatialTemporalDataWriter::outputTraceInXmlFormatToFile(
            resultingTrace,
            mstmlFileOutputPath
        );
    // Otherwise throw an exception
    } else {
        MS_throw(
            InvalidOutputException,
            ERR_EMPTY_RESULTING_MSTML_FILE
        );
    }
}

void MSTMLSubfilesMerger::initialize() {
    readTimePointsValues();
}

void MSTMLSubfilesMerger::readTimePointsValues() {
    std::ifstream fin(timePointsValuesFilePath, std::ios::in);

    if (fin.is_open()) {
        readTimePointsValuesFromStream(fin);
    } else {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_TIMEPOINTS_VALUES_FILE_BEGIN +
            timePointsValuesFilePath +
            ERR_INVALID_TIMEPOINTS_VALUES_FILE_END
        );
    }

    fin.close();
}

void MSTMLSubfilesMerger::readTimePointsValuesFromStream(std::ifstream &fin) {
    double      timePointValue;
    std::string line;

    // Skip the first header line (usually "Time")
    getline(fin, line);

    // Read the time points values
    while (getline(fin, line)) {
        // Convert the line to a time point value
        timePointValue = convertToTimePointValue(line);

        // Store the time point value
        timePointsValues.push_back(timePointValue);
    }
}

double MSTMLSubfilesMerger::convertToTimePointValue(const std::string &timePointValueAsString) {
    try {
        return StringManipulator::convert<double>(timePointValueAsString);
    } catch (const MultiscaleException &ex) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_FORMAT_TIMEPOINT_VALUE_BEGIN +
            timePointsValuesFilePath +
            ERR_INVALID_FORMAT_TIMEPOINT_VALUE_END
        );
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0;
}

void MSTMLSubfilesMerger::addSubtracesToResultingTrace() {
    SpatialTemporalTrace subtrace;
    std::string subtraceFilepath;

    // While there are subtraces available
    while (traceReader.hasNext()) {
        // Get the next spatial temporal subtrace
        subtrace = traceReader.getNextSpatialTemporalTrace(subtraceFilepath);

        addSubtraceToResultingTrace(subtrace, subtraceFilepath);
    }
}

void MSTMLSubfilesMerger::addSubtraceToResultingTrace(const SpatialTemporalTrace &subtrace,
                                                      const std::string &subtraceFilepath) {
    validateSubtrace(subtrace, subtraceFilepath);

    addSubtraceStateVariablesToResultingTrace(subtrace, subtraceFilepath);
}

void MSTMLSubfilesMerger::validateSubtrace(const SpatialTemporalTrace &subtrace,
                                           const std::string &subtraceFilepath) {
    validateSubtraceNumberOfTimePoints(subtrace, subtraceFilepath);
    validateSubtraceTimePointsValues(subtrace, subtraceFilepath);
}

void MSTMLSubfilesMerger::validateSubtraceNumberOfTimePoints(const SpatialTemporalTrace &subtrace,
                                                             const std::string &subtraceFilepath) {
    unsigned int nrOfTimePointsInSubtrace = subtrace.length();
    unsigned int expectedNrOfTimePoints   = static_cast<unsigned int>(timePointsValues.size());

    if (nrOfTimePointsInSubtrace != expectedNrOfTimePoints) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_TIMEPOINTS_BEGIN +
            subtraceFilepath +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE1 +
            StringManipulator::toString<unsigned int>(nrOfTimePointsInSubtrace) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE2 +
            StringManipulator::toString<unsigned int>(expectedNrOfTimePoints) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE3 +
            timePointsValuesFilePath +
            ERR_INVALID_NR_TIMEPOINTS_END
        );
    }
}

void MSTMLSubfilesMerger::validateSubtraceTimePointsValues(const SpatialTemporalTrace &subtrace,
                                                           const std::string &subtraceFilepath) {
    // If the resulting trace is not empty i.e. this is not the first subtrace
    // which will be added to the resulting trace
    if (resultingTrace.length() > 0) {
        if (areMismatchingTimePointValues(subtrace)) {
            MS_throw(
                InvalidInputException,
                ERR_NON_MATCHING_TIMEPOINT_VALUE_BEGIN +
                subtraceFilepath +
                ERR_NON_MATCHING_TIMEPOINT_VALUE_END
            );
        }
    }
}

bool MSTMLSubfilesMerger::areMismatchingTimePointValues(const SpatialTemporalTrace &subtrace) {
    // This condition should have been checked by a previously called method
    assert(subtrace.length() == resultingTrace.length());

    // Compute the number of time points
    std::size_t nrOfTimePoints = timePointsValues.size();

    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        double resultingTraceTimePointValue = resultingTrace.getTimePointReference(i).getValue();
        double subtraceTimePointValue       = subtrace.getTimePointReference(i).getValue();

        // If there exists a mismatching pair of time point values
        if (!Numeric::almostEqual(resultingTraceTimePointValue, subtraceTimePointValue)) {
            return true;
        }
    }

    // All time points values are matching
    return false;
}

void MSTMLSubfilesMerger::addSubtraceStateVariablesToResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                    const std::string &subtraceFilepath) {
    // If the resulting trace is empty
    if (resultingTrace.length() == 0) {
        addSubtraceStateVariablesToEmptyResultingTrace(subtrace, subtraceFilepath);
    } else {
        addSubtraceStateVariablesToNonEmptyResultingTrace(subtrace, subtraceFilepath);
    }
}

void MSTMLSubfilesMerger::addSubtraceStateVariablesToEmptyResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                         const std::string &subtraceFilepath) {
    std::size_t nrOfTimePoints = timePointsValues.size();

    // Add each time point from the subtrace to the resulting trace
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        resultingTrace.addTimePoint(
            subtrace.getTimePoint(i)
        );
    }
}

void MSTMLSubfilesMerger::addSubtraceStateVariablesToNonEmptyResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                            const std::string &subtraceFilepath) {
    std::size_t nrOfTimePoints = timePointsValues.size();

    // Add time point state variables from subtrace to resulting trace
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        const TimePoint &subtraceTimePoint = subtrace.getTimePointReference(i);
        TimePoint &resultingTraceTimePoint = resultingTrace.getTimePointReference(i);

        addNumericStateVariablesToResultingTraceTimePoint(
            subtraceTimePoint, resultingTraceTimePoint, subtraceFilepath
        );
        addSpatialEntitiesToResultingTraceTimePoint(
            subtraceTimePoint, resultingTraceTimePoint, subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addNumericStateVariablesToResultingTraceTimePoint(const TimePoint &subtraceTimePoint,
                                                                            TimePoint &resultingTraceTimePoint,
                                                                            const std::string &subtraceFilepath) {
    auto beginIterator  = subtraceTimePoint.getNumericStateVariablesBeginIterator();
    auto endIterator    = subtraceTimePoint.getNumericStateVariablesEndIterator();

    // Add each numeric state variable in the subtrace time point
    for (auto it = beginIterator; it != endIterator; it++) {
        NumericStateVariableId subtraceNumericStateVariableId = it->first;
        double subtraceNumericStateVariableValue = it->second;

        addNumericStateVariableToTimePoint(
            subtraceNumericStateVariableId,
            subtraceNumericStateVariableValue,
            resultingTraceTimePoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addNumericStateVariableToTimePoint(const NumericStateVariableId &numericStateVariableId,
                                                             double numericStateVariableValue,
                                                             TimePoint &timePoint,
                                                             const std::string &subtraceFilepath) {
    // If time point already contains a numeric state variable with this id throw exception
    if (timePoint.containsNumericStateVariable(numericStateVariableId)) {
        MS_throw(
            InvalidInputException,
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_BEGIN +
            numericStateVariableId.toString() +
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_MIDDLE +
            subtraceFilepath +
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_END
        );
    // Otherwise add numeric state variable to time point
    } else {
        timePoint.addNumericStateVariable(
            numericStateVariableId,
            numericStateVariableValue
        );
    }
}

void MSTMLSubfilesMerger::addSpatialEntitiesToResultingTraceTimePoint(const TimePoint &subtraceTimePoint,
                                                                      TimePoint &resultingTraceTimePoint,
                                                                      const std::string &subtraceFilepath) {
    // Add spatial entities to resulting trace time point considering each spatial entity type
    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        SubsetSpecificType spatialEntityType = subsetspecific::computeSubsetSpecificType(i);

        addSpatialEntitiesToResultingTraceTimePoint(
            spatialEntityType,
            subtraceTimePoint,
            resultingTraceTimePoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addSpatialEntitiesToResultingTraceTimePoint(const SubsetSpecificType &spatialEntityType,
                                                                      const TimePoint &subtraceTimePoint,
                                                                      TimePoint &resultingTraceTimePoint,
                                                                      const std::string &subtraceFilepath) {
    auto spatialEntitiesBeginIterator   = subtraceTimePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
    auto spatialEntitiesEndIterator     = subtraceTimePoint.getSpatialEntitiesEndIterator(spatialEntityType);

    // Add each spatial entity in the subtrace time point
    for (auto it = spatialEntitiesBeginIterator; it != spatialEntitiesEndIterator; it++) {
        addSpatialEntityToTimePoint(
            (*it),
            spatialEntityType,
            resultingTraceTimePoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addSpatialEntityToTimePoint(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                      const SubsetSpecificType &spatialEntityType,
                                                      TimePoint &timePoint,
                                                      const std::string &subtraceFilepath) {
    // If the time point contains an equal valued spatial entity throw an exception
    if (timePoint.containsSpatialEntity(spatialEntity, spatialEntityType)) {
        MS_throw(
            InvalidInputException,
            ERR_SPATIAL_ENTITY_EXISTS_BEGIN +
            spatialEntity->toString() +
            ERR_SPATIAL_ENTITY_EXISTS_MIDDLE +
            subtraceFilepath +
            ERR_SPATIAL_ENTITY_EXISTS_END
        );
    // Otherwise add the spatial entity to the time point
    } else {
        timePoint.addSpatialEntityAndType(
            spatialEntity,
            spatialEntityType
        );
    }
}

void MSTMLSubfilesMerger::updateResultingTraceTimePointsValues() {
    validateNumberOfTimePointsInResultingTrace();

    // Compute the number of time points in the time points values file
    std::size_t nrOfTimePoints = timePointsValues.size();

    // Set the resulting trace time points values
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        TimePoint   &timePoint      = resultingTrace.getTimePointReference(i);
        double      timePointValue  = timePointsValues[i];

        timePoint.setValue(timePointValue);
    }
}

void MSTMLSubfilesMerger::validateNumberOfTimePointsInResultingTrace() {
    std::size_t nrOfTimePointsInTimePointsValues = timePointsValues.size();
    std::size_t nrOfTimePointsInResultingTrace   = static_cast<std::size_t>(resultingTrace.length());

    // If the number of time points differs throw an exception
    if (nrOfTimePointsInResultingTrace != nrOfTimePointsInTimePointsValues) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_TIMEPOINTS_RESULTING_TRACE_BEGIN +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE1 +
            StringManipulator::toString(nrOfTimePointsInResultingTrace) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE2 +
            StringManipulator::toString(nrOfTimePointsInTimePointsValues) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE3 +
            timePointsValuesFilePath +
            ERR_INVALID_NR_TIMEPOINTS_END
        );
    }
}


// Constants
const std::string MSTMLSubfilesMerger::ERR_INVALID_TIMEPOINTS_VALUES_FILE_BEGIN = "The provided time points' values input file (";
const std::string MSTMLSubfilesMerger::ERR_INVALID_TIMEPOINTS_VALUES_FILE_END   = ") could not be opened. Please make sure that the file path is valid and the file accessible.";

const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_RESULTING_TRACE_BEGIN  = "The resulting MSTML trace";

const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_BEGIN      = "The MSTML subfile ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE1    = " contains ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE2    = " time points instead of the expected number of time points (";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE3    = ") specified in the time points values file ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_END        = ". Please change.";

const std::string MSTMLSubfilesMerger::ERR_INVALID_FORMAT_TIMEPOINT_VALUE_BEGIN = "The provided time points values input file ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_FORMAT_TIMEPOINT_VALUE_END   = " contains incorrectly formatted time point values. ";

const std::string MSTMLSubfilesMerger::ERR_NON_MATCHING_TIMEPOINT_VALUE_BEGIN   = "The MSTML subfile ";
const std::string MSTMLSubfilesMerger::ERR_NON_MATCHING_TIMEPOINT_VALUE_END     = ")  which does not match the corresponding time point value from the resulting trace. Please change.";

const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_BEGIN  = "The resulting trace contains a numeric state variable which has the same id ";
const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_MIDDLE = " as one of the numeric state variables in the subtrace ";
const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_END    = ". Please update the subtrace such that the numeric state variable id is unique among all subtraces.";

const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_BEGIN  = "The resulting trace contains a spatial entity which has the same values (";
const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_MIDDLE = ") as one of the spatial entities in the subtrace ";
const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_END    = ". Please update the subtrace such that each spatial entity is unique among all subtraces.";

const std::string MSTMLSubfilesMerger::ERR_EMPTY_RESULTING_MSTML_FILE   = "The resulting trace should contain at least one time point but it does not. Please update the MSTML subfiles such that the resulting trace contains at least one time point.";
