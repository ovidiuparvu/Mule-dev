#ifndef MSTMLSUBFILESMERGER_HPP
#define MSTMLSUBFILESMERGER_HPP

#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscale {

    namespace verification {

        //! Class for merging MSTML subfiles
        class MSTMLSubfilesMerger {

            private:

                std::string
                    timepointsValuesFilePath;   /*!< The path to the file containing the considered
                                                     timepoints' values */

                SpatialTemporalDataReader
                    traceReader;                /*!< The reader used to input spatial temporal traces from
                                                     the MSTML subfiles */

                std::vector<unsigned long>
                    timepointsValues;           /*!< The considered timepoints' values */

                SpatialTemporalTrace
                    resultingTrace;             /*!< The trace obtained after merging all subtraces
                                                     corresponding to MSTML subfiles */

            public:

                MSTMLSubfilesMerger(const std::string &mstmlSubfilesFolderPath,
                                    const std::string &timepointsValuesFilePath);
                ~MSTMLSubfilesMerger();

                //! Merge the MSTML sufiles from the provided folder considering the given timepoints values
                void mergeMSTMLSubfiles();

                //! Get the resulting merged spatial temporal trace
                SpatialTemporalTrace getResultingMergedTrace();

                //! Output the resulting MSTML file to the file having the provided output path
                /*! If the number of timepoints in the trace is greater than zero output the trace
                 *  to an xml file. Otherwise throw an exception.
                 *
                 * \param mstmlFileOutputPath   The path to the resulting (merged) MSTML file
                 */
                void outputResultingMSTMLFile(const std::string &mstmlFileOutputPath);

            private:

                //! Initialisation function
                void initialise();

                //! Read timepoints' values
                void readTimepointsValues();

                //! Read timepoints' values from the provided input stream
                /*! The format of the timepoints values input file is:
                 *  Line (L) 1: Header (usually "Time")
                 *  L2:         Timepoint value 1
                 *  L3:         Timepoint value 2
                 *  ...         ...
                 *  Ln:         Timepoint value n-1
                 *
                 * \param fin   Input stream of timepoints' values
                 */
                void readTimepointsValuesFromStream(std::ifstream &fin);

                //! Convert the provided string to a timepoint value (i.e. unsigned long)
                /*! If the provided string cannot be converted to an unsigned long an error is thrown.
                 *
                 * \param timepointValueAsString    The timepoint value represented as a string
                 */
                unsigned long convertToTimepointValue(const std::string &timepointValueAsString);

                //! Add the subtraces corresponding to the MSTML subfiles to the resulting trace
                void addSubtracesToResultingTrace();

                //! Add the provided spatial temporal subtrace to the resulting trace
                /*!
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void addSubtraceToResultingTrace(const SpatialTemporalTrace &subtrace,
                                                 const std::string &subtraceFilepath);

                //! Validate the provided subtrace
                /*! A subtrace is valid if:
                 *      1. The number of timepoints it contains is equal to the number
                 *         of timepoint values read from the provided timepointsValuesFilePath file;
                 *      2. The timepoints values of the subtrace match the timepoints values in the
                 *         resulting trace.
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtrace(const SpatialTemporalTrace &subtrace,
                                      const std::string &subtraceFilepath);

                //! Check if the provided subtrace contains the correct number of timepoints
                /*! A subtrace is valid if the number of timepoints it contains is equal to the number
                 *  of timepoint values read from the provided timepointsValuesFilePath file;
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtraceNumberOfTimepoints(const SpatialTemporalTrace &subtrace,
                                                        const std::string &subtraceFilepath);

                //! Check if the provided subtrace timepoints values are valid
                /*! A subtrace is valid if the timepoints values of the subtrace match the
                 * timepoints values in the resulting trace
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtraceTimepointsValues(const SpatialTemporalTrace &subtrace,
                                                      const std::string &subtraceFilepath);

                //! Check if there are any mismatching timepoint values in the provided and resulting trace
                /*!
                 * \param subtrace  The provided spatial temporal subtrace
                 */
                bool areMismatchingTimepointValues(const SpatialTemporalTrace &subtrace);

                //! Add the state variables from the provided to the resulting trace
                /*!
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void addSubtraceStateVariablesToResultingTrace(const SpatialTemporalTrace &subtrace,
                                                               const std::string &subtraceFilepath);

                //! Add the state variables from the provided to the empty resulting trace
                /*!
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void addSubtraceStateVariablesToEmptyResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                    const std::string &subtraceFilepath);

                //! Add the state variables from the provided to the non-empty resulting trace
                /*!
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void addSubtraceStateVariablesToNonEmptyResultingTrace(const SpatialTemporalTrace &subtrace,
                                                                       const std::string &subtraceFilepath);

                //! Add numeric state variables from the provided subtrace to the resulting trace timepoint
                /*!
                 * \param subtraceTimepoint         The provided subtrace timepoint
                 * \param resultingTraceTimepoint   The resulting trace timepoint
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addNumericStateVariablesToResultingTraceTimepoint(const TimePoint &subtraceTimepoint,
                                                                       TimePoint &resultingTraceTimepoint,
                                                                       const std::string &subtraceFilepath);

                //! Add numeric state variable to timepoint
                /*! If an equal value numeric state variable already exists in the timepoint throw an exception.
                 *
                 * \param numericStateVariableId    The id of the numeric state variable
                 * \param numericStateVariableValue The value of the numeric state variable
                 * \param timepoint                 The timepoint to which the numeric state variable is added
                 * \param subtraceFilepath          The path to the subtrace to which the numeric state variable
                 *                                  belongs
                 */
                void addNumericStateVariableToTimepoint(const NumericStateVariableId &numericStateVariableId,
                                                        double numericStateVariableValue,
                                                        TimePoint &timepoint,
                                                        const std::string &subtraceFilepath);

                //! Add spatial entities from the provided subtrace to the resulting trace timepoint
                /*!
                 * \param subtraceTimepoint         The provided subtrace timepoint
                 * \param resultingTraceTimepoint   The resulting trace timepoint
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addSpatialEntitiesToResultingTraceTimepoint(const TimePoint &subtraceTimepoint,
                                                                 TimePoint &resultingTraceTimepoint,
                                                                 const std::string &subtraceFilepath);

                //! Add spatial entities of the given type from the provided subtrace to the resulting trace timepoint
                /*!
                 * \param spatialEntityType         The considered spatial entity type
                 * \param subtraceTimepoint         The provided subtrace timepoint
                 * \param resultingTraceTimepoint   The resulting trace timepoint
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addSpatialEntitiesToResultingTraceTimepoint(const SubsetSpecificType &spatialEntityType,
                                                                 const TimePoint &subtraceTimepoint,
                                                                 TimePoint &resultingTraceTimepoint,
                                                                 const std::string &subtraceFilepath);

                //! Add spatial entity to timepoint
                /*! If an equal value spatial entity already exists in the timepoint throw an exception.
                 *
                 * \param spatialEntity     The considered spatial entity
                 * \param spatialEntityType The considered spatial entity type
                 * \param timepoint         The timepoint to which the spatial entity is added
                 * \param subtraceFilepath  The path to the subtrace to which the spatial entity belongs
                 */
                void addSpatialEntityToTimepoint(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                 const SubsetSpecificType &spatialEntityType,
                                                 TimePoint &timepoint,
                                                 const std::string &subtraceFilepath);

                //! Replace the resulting trace timepoints values with the timepoints values read from file
                /*! If the number of timepoints in the timepoints values input file and the resulting trace
                 *  differ throw an exception.
                 */
                void updateResultingTraceTimepointsValues();

                //! Check if the number of timepoints is equal in the resulting trace and the timepoints values file
                void validateNumberOfTimepointsInResultingTrace();


                // Constants
                static const std::string ERR_INVALID_TIMEPOINTS_VALUES_FILE_BEGIN;
                static const std::string ERR_INVALID_TIMEPOINTS_VALUES_FILE_END;

                static const std::string ERR_INVALID_NR_TIMEPOINTS_RESULTING_TRACE_BEGIN;

                static const std::string ERR_INVALID_NR_TIMEPOINTS_BEGIN;
                static const std::string ERR_INVALID_NR_TIMEPOINTS_MIDDLE1;
                static const std::string ERR_INVALID_NR_TIMEPOINTS_MIDDLE2;
                static const std::string ERR_INVALID_NR_TIMEPOINTS_MIDDLE3;
                static const std::string ERR_INVALID_NR_TIMEPOINTS_END;

                static const std::string ERR_INVALID_FORMAT_TIMEPOINT_VALUE_BEGIN;
                static const std::string ERR_INVALID_FORMAT_TIMEPOINT_VALUE_END;

                static const std::string ERR_NON_MATCHING_TIMEPOINT_VALUE_BEGIN;
                static const std::string ERR_NON_MATCHING_TIMEPOINT_VALUE_END;

                static const std::string ERR_NUMERIC_STATE_VARIABLE_EXISTS_BEGIN;
                static const std::string ERR_NUMERIC_STATE_VARIABLE_EXISTS_MIDDLE;
                static const std::string ERR_NUMERIC_STATE_VARIABLE_EXISTS_END;

                static const std::string ERR_SPATIAL_ENTITY_EXISTS_BEGIN;
                static const std::string ERR_SPATIAL_ENTITY_EXISTS_MIDDLE;
                static const std::string ERR_SPATIAL_ENTITY_EXISTS_END;

                static const std::string ERR_EMPTY_RESULTING_MSTML_FILE;

        };

    };

};


#endif
