#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/InvalidOutputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/data/MSTMLSubfilesMerger.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataWriter.hpp"

#include <cassert>
#include <fstream>

using namespace multiscale::verification;


MSTMLSubfilesMerger::MSTMLSubfilesMerger(const std::string &mstmlSubfilesFolderPath,
                                         const std::string &timepointsValuesFilePath)
                                         : timepointsValuesFilePath(timepointsValuesFilePath),
                                           traceReader(mstmlSubfilesFolderPath) {
    initialise();
}

MSTMLSubfilesMerger::~MSTMLSubfilesMerger() {}

void MSTMLSubfilesMerger::mergeMSTMLSubfiles() {
    addSubtracesToResultingTrace();
    updateResultingTraceTimepointsValues();
}

SpatialTemporalTrace MSTMLSubfilesMerger::getResultingMergedTrace() {
    return resultingTrace;
}

void MSTMLSubfilesMerger::outputResultingMSTMLFile(const std::string &mstmlFileOutputPath) {
    // If the number of timepoints in the resulting trace is greater than 0 output the trace to an xml file
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

void MSTMLSubfilesMerger::initialise() {
    readTimepointsValues();
}

void MSTMLSubfilesMerger::readTimepointsValues() {
    std::ifstream fin(timepointsValuesFilePath, std::ios::in);

    if (fin.is_open()) {
        readTimepointsValuesFromStream(fin);
    } else {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_TIMEPOINTS_VALUES_FILE_BEGIN +
            timepointsValuesFilePath +
            ERR_INVALID_TIMEPOINTS_VALUES_FILE_END
        );
    }

    fin.close();
}

void MSTMLSubfilesMerger::readTimepointsValuesFromStream(std::ifstream &fin) {
    unsigned long timepointValue;
    std::string line;

    // Skip the first header line (usually "Time")
    getline(fin, line);

    // Read the timepoints values
    while (getline(fin, line)) {
        // Convert the line to a timepoint value
        timepointValue = convertToTimepointValue(line);

        // Store the timepoint value
        timepointsValues.push_back(timepointValue);
    }
}

unsigned long MSTMLSubfilesMerger::convertToTimepointValue(const std::string &timepointValueAsString) {
    try {
        return StringManipulator::convert<unsigned long>(timepointValueAsString);
    } catch (const MultiscaleException &ex) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_FORMAT_TIMEPOINT_VALUE_BEGIN +
            timepointsValuesFilePath +
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
    validateSubtraceNumberOfTimepoints(subtrace, subtraceFilepath);
    validateSubtraceTimepointsValues(subtrace, subtraceFilepath);
}

void MSTMLSubfilesMerger::validateSubtraceNumberOfTimepoints(const SpatialTemporalTrace &subtrace,
                                                             const std::string &subtraceFilepath) {
    unsigned int nrOfTimepointsInSubtrace = subtrace.length();
    unsigned int expectedNrOfTimepoints = static_cast<unsigned int>(timepointsValues.size());

    if (nrOfTimepointsInSubtrace != expectedNrOfTimepoints) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_TIMEPOINTS_BEGIN +
            subtraceFilepath +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE1 +
            StringManipulator::toString<unsigned int>(nrOfTimepointsInSubtrace) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE2 +
            StringManipulator::toString<unsigned int>(expectedNrOfTimepoints) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE3 +
            timepointsValuesFilePath +
            ERR_INVALID_NR_TIMEPOINTS_END
        );
    }
}

void MSTMLSubfilesMerger::validateSubtraceTimepointsValues(const SpatialTemporalTrace &subtrace,
                                                           const std::string &subtraceFilepath) {
    // If the resulting trace is not empty i.e. this is not the first subtrace
    // which will be added to the resulting trace
    if (resultingTrace.length() > 0) {
        if (areMismatchingTimepointValues(subtrace)) {
            MS_throw(
                InvalidInputException,
                ERR_NON_MATCHING_TIMEPOINT_VALUE_BEGIN +
                subtraceFilepath +
                ERR_NON_MATCHING_TIMEPOINT_VALUE_END
            );
        }
    }
}

bool MSTMLSubfilesMerger::areMismatchingTimepointValues(const SpatialTemporalTrace &subtrace) {
    // This condition should have been checked by a previously called method
    assert(subtrace.length() == resultingTrace.length());

    // Compute the number of timepoints
    std::size_t nrOfTimepoints = timepointsValues.size();

    for (std::size_t i = 0; i < nrOfTimepoints; i++) {
        unsigned long resultingTraceTimepointValue = resultingTrace.getTimePointReference(i).getValue();
        unsigned long subtraceTimepointValue = subtrace.getTimePointReference(i).getValue();

        // If there exists a mismatching pair of timepoint values
        if (resultingTraceTimepointValue != subtraceTimepointValue) {
            return true;
        }
    }

    // All timepoints values are matching
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
    std::size_t nrOfTimepoints = timepointsValues.size();

    // Add each timepoint from the subtrace to the resulting trace
    for (std::size_t i = 0; i < nrOfTimepoints; i++) {
        resultingTrace.addTimePoint(
            subtrace.getTimePoint(i)
        );
    }
}

void MSTMLSubfilesMerger::addSubtraceStateVariablesToNonEmptyResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                            const std::string &subtraceFilepath) {
    std::size_t nrOfTimepoints = timepointsValues.size();

    // Add timepoint state variables from subtrace to resulting trace
    for (std::size_t i = 0; i < nrOfTimepoints; i++) {
        const TimePoint &subtraceTimepoint = subtrace.getTimePointReference(i);
        TimePoint &resultingTraceTimepoint = resultingTrace.getTimePointReference(i);

        addNumericStateVariablesToResultingTraceTimepoint(
            subtraceTimepoint, resultingTraceTimepoint, subtraceFilepath
        );
        addSpatialEntitiesToResultingTraceTimepoint(
            subtraceTimepoint, resultingTraceTimepoint, subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addNumericStateVariablesToResultingTraceTimepoint(const TimePoint &subtraceTimepoint,
                                                                            TimePoint &resultingTraceTimepoint,
                                                                            const std::string &subtraceFilepath) {
    auto beginIterator  = subtraceTimepoint.getNumericStateVariablesBeginIterator();
    auto endIterator    = subtraceTimepoint.getNumericStateVariablesEndIterator();

    // Add each numeric state variable in the subtrace timepoint
    for (auto it = beginIterator; it != endIterator; it++) {
        NumericStateVariableId subtraceNumericStateVariableId = it->first;
        double subtraceNumericStateVariableValue = it->second;

        addNumericStateVariableToTimepoint(
            subtraceNumericStateVariableId,
            subtraceNumericStateVariableValue,
            resultingTraceTimepoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addNumericStateVariableToTimepoint(const NumericStateVariableId &numericStateVariableId,
                                                             double numericStateVariableValue,
                                                             TimePoint &timepoint,
                                                             const std::string &subtraceFilepath) {
    // If timepoint already contains a numeric state variable with this id throw exception
    if (timepoint.containsNumericStateVariable(numericStateVariableId)) {
        MS_throw(
            InvalidInputException,
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_BEGIN +
            numericStateVariableId.toString() +
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_MIDDLE +
            subtraceFilepath +
            ERR_NUMERIC_STATE_VARIABLE_EXISTS_END
        );
    // Otherwise add numeric state variable to timepoint
    } else {
        timepoint.addNumericStateVariable(numericStateVariableId, numericStateVariableValue);
    }
}

void MSTMLSubfilesMerger::addSpatialEntitiesToResultingTraceTimepoint(const TimePoint &subtraceTimepoint,
                                                                      TimePoint &resultingTraceTimepoint,
                                                                      const std::string &subtraceFilepath) {
    // Add spatial entities to resulting trace timepoint considering each spatial entity type
    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        SubsetSpecificType spatialEntityType = subsetspecific::computeSubsetSpecificType(i);

        addSpatialEntitiesToResultingTraceTimepoint(
            spatialEntityType,
            subtraceTimepoint,
            resultingTraceTimepoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addSpatialEntitiesToResultingTraceTimepoint(const SubsetSpecificType &spatialEntityType,
                                                                      const TimePoint &subtraceTimepoint,
                                                                      TimePoint &resultingTraceTimepoint,
                                                                      const std::string &subtraceFilepath) {
    auto spatialEntitiesBeginIterator   = subtraceTimepoint.getSpatialEntitiesBeginIterator(spatialEntityType);
    auto spatialEntitiesEndIterator     = subtraceTimepoint.getSpatialEntitiesEndIterator(spatialEntityType);

    // Add each spatial entity in the subtrace timepoint
    for (auto it = spatialEntitiesBeginIterator; it != spatialEntitiesEndIterator; it++) {
        addSpatialEntityToTimepoint(
            (*it),
            spatialEntityType,
            resultingTraceTimepoint,
            subtraceFilepath
        );
    }
}

void MSTMLSubfilesMerger::addSpatialEntityToTimepoint(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                      const SubsetSpecificType &spatialEntityType,
                                                      TimePoint &timepoint,
                                                      const std::string &subtraceFilepath) {
    // If the timepoint contains an equal valued spatial entity throw an exception
    if (timepoint.containsSpatialEntity(spatialEntity, spatialEntityType)) {
        MS_throw(
            InvalidInputException,
            ERR_SPATIAL_ENTITY_EXISTS_BEGIN +
            spatialEntity->toString() +
            ERR_SPATIAL_ENTITY_EXISTS_MIDDLE +
            subtraceFilepath +
            ERR_SPATIAL_ENTITY_EXISTS_END
        );
    // Otherwise add the spatial entity to the timepoint
    } else {
        timepoint.addSpatialEntityAndType(spatialEntity, spatialEntityType);
    }
}

void MSTMLSubfilesMerger::updateResultingTraceTimepointsValues() {
    validateNumberOfTimepointsInResultingTrace();

    // Compute the number of timepoints in the timepoints values file
    std::size_t nrOfTimepoints = timepointsValues.size();

    // Set the resulting trace timepoints values
    for (std::size_t i = 0; i < nrOfTimepoints; i++) {
        TimePoint       &timepoint      = resultingTrace.getTimePointReference(i);
        unsigned long   timepointValue  = timepointsValues[i];

        timepoint.setValue(timepointValue);
    }
}

void MSTMLSubfilesMerger::validateNumberOfTimepointsInResultingTrace() {
    std::size_t nrOfTimepointsInTimepointsValues = timepointsValues.size();
    std::size_t nrOfTimepointsInResultingTrace = static_cast<std::size_t>(resultingTrace.length());

    // If the number of timepoints differs throw an exception
    if (nrOfTimepointsInResultingTrace != nrOfTimepointsInTimepointsValues) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_TIMEPOINTS_RESULTING_TRACE_BEGIN +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE1 +
            StringManipulator::toString(nrOfTimepointsInResultingTrace) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE2 +
            StringManipulator::toString(nrOfTimepointsInTimepointsValues) +
            ERR_INVALID_NR_TIMEPOINTS_MIDDLE3 +
            timepointsValuesFilePath +
            ERR_INVALID_NR_TIMEPOINTS_END
        );
    }
}


// Constants
const std::string MSTMLSubfilesMerger::ERR_INVALID_TIMEPOINTS_VALUES_FILE_BEGIN = "The provided timepoints' values input file (";
const std::string MSTMLSubfilesMerger::ERR_INVALID_TIMEPOINTS_VALUES_FILE_END   = ") could not be opened. Please make sure that the file path is valid and the file accessible.";

const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_RESULTING_TRACE_BEGIN  = "The resulting MSTML trace";

const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_BEGIN      = "The MSTML subfile ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE1    = " contains ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE2    = " timepoints instead of the expected number of timepoints (";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_MIDDLE3    = ") specified in the timepoints values file ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_NR_TIMEPOINTS_END        = ". Please change.";

const std::string MSTMLSubfilesMerger::ERR_INVALID_FORMAT_TIMEPOINT_VALUE_BEGIN = "The provided timepoints values input file ";
const std::string MSTMLSubfilesMerger::ERR_INVALID_FORMAT_TIMEPOINT_VALUE_END   = " contains incorrectly formatted timepoint values. ";

const std::string MSTMLSubfilesMerger::ERR_NON_MATCHING_TIMEPOINT_VALUE_BEGIN   = "The MSTML subfile ";
const std::string MSTMLSubfilesMerger::ERR_NON_MATCHING_TIMEPOINT_VALUE_END     = ")  which does not match the corresponding timepoint value from the resulting trace. Please change.";

const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_BEGIN  = "The resulting trace contains a numeric state variable which has the same id ";
const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_MIDDLE = " as one of the numeric state variables in the subtrace ";
const std::string MSTMLSubfilesMerger::ERR_NUMERIC_STATE_VARIABLE_EXISTS_END    = ". Please update the subtrace such that the numeric state variable id is unique among all subtraces.";

const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_BEGIN  = "The resulting trace contains a spatial entity which has the same values (";
const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_MIDDLE = ") as one of the spatial entities in the subtrace ";
const std::string MSTMLSubfilesMerger::ERR_SPATIAL_ENTITY_EXISTS_END    = ". Please update the subtrace such that each spatial entity is unique among all subtraces.";

const std::string MSTMLSubfilesMerger::ERR_EMPTY_RESULTING_MSTML_FILE   = "The resulting trace should contain at least one timepoint but it does not. Please update the MSTML subfiles such that the resulting trace contains at least one timepoint.";
