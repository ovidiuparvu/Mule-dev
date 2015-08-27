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
                    timePointsValuesFilePath;   /*!< The path to the file containing the considered
                                                     time points' values */

                SpatialTemporalDataReader
                    traceReader;                /*!< The reader used to input spatial temporal traces from
                                                     the MSTML subfiles */

                std::vector<double>
                    timePointsValues;           /*!< The considered time points' values */

                SpatialTemporalTrace
                    resultingTrace;             /*!< The trace obtained after merging all subtraces
                                                     corresponding to MSTML subfiles */

            public:

                MSTMLSubfilesMerger(const std::string &mstmlSubfilesFolderPath,
                                    const std::string &timePointsValuesFilePath);
                ~MSTMLSubfilesMerger();

                //! Merge the MSTML sufiles from the provided folder considering the given time points values
                void mergeMSTMLSubfiles();

                //! Get the resulting merged spatial temporal trace
                SpatialTemporalTrace getResultingMergedTrace();

                //! Output the resulting MSTML file to the file having the provided output path
                /*! If the number of time points in the trace is greater than zero output the trace
                 *  to an xml file. Otherwise throw an exception.
                 *
                 * \param mstmlFileOutputPath   The path to the resulting (merged) MSTML file
                 */
                void outputResultingMSTMLFile(const std::string &mstmlFileOutputPath);

            private:

                //! Initialisation function
                void initialize();

                //! Read time points' values
                void readTimePointsValues();

                //! Read time points' values from the provided input stream
                /*! The format of the time points values input file is:
                 *  Line (L) 1: Header (usually "Time")
                 *  L2:         Time point value 1
                 *  L3:         Time point value 2
                 *  ...         ...
                 *  Ln:         Time point value n-1
                 *
                 * \param fin   Input stream of time points' values
                 */
                void readTimePointsValuesFromStream(std::ifstream &fin);

                //! Convert the provided string to a time point value (i.e. double)
                /*! If the provided string cannot be converted to a double an error is thrown.
                 *
                 * \param timePointValueAsString    The time point value represented as a string
                 */
                double convertToTimePointValue(const std::string &timePointValueAsString);

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
                 *      1. The number of time points it contains is equal to the number
                 *         of time point values read from the provided timePointsValuesFilePath file;
                 *      2. The time points values of the subtrace match the time points values in the
                 *         resulting trace.
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtrace(const SpatialTemporalTrace &subtrace,
                                      const std::string &subtraceFilepath);

                //! Check if the provided subtrace contains the correct number of time points
                /*! A subtrace is valid if the number of time points it contains is equal to the number
                 *  of time point values read from the provided timePointsValuesFilePath file;
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtraceNumberOfTimePoints(const SpatialTemporalTrace &subtrace,
                                                        const std::string &subtraceFilepath);

                //! Check if the provided subtrace time points values are valid
                /*! A subtrace is valid if the time points values of the subtrace match the
                 * time points values in the resulting trace
                 *
                 * \param subtrace          The provided spatial temporal subtrace
                 * \param subtraceFilepath  The path to the file containing the subtrace related information
                 */
                void validateSubtraceTimePointsValues(const SpatialTemporalTrace &subtrace,
                                                      const std::string &subtraceFilepath);

                //! Check if there are any mismatching time point values in the provided and resulting trace
                /*!
                 * \param subtrace  The provided spatial temporal subtrace
                 */
                bool areMismatchingTimePointValues(const SpatialTemporalTrace &subtrace);

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

                //! Add numeric state variables from the provided subtrace to the resulting trace time point
                /*!
                 * \param subtraceTimePoint         The provided subtrace time point
                 * \param resultingTraceTimePoint   The resulting trace time point
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addNumericStateVariablesToResultingTraceTimePoint(const TimePoint &subtraceTimePoint,
                                                                       TimePoint &resultingTraceTimePoint,
                                                                       const std::string &subtraceFilepath);

                //! Add numeric state variable to time point
                /*! If an equal value numeric state variable already exists in the time point throw an exception.
                 *
                 * \param numericStateVariableId    The id of the numeric state variable
                 * \param numericStateVariableValue The value of the numeric state variable
                 * \param timePoint                 The time point to which the numeric state variable is added
                 * \param subtraceFilepath          The path to the subtrace to which the numeric state variable
                 *                                  belongs
                 */
                void addNumericStateVariableToTimePoint(const NumericStateVariableId &numericStateVariableId,
                                                        double numericStateVariableValue,
                                                        TimePoint &timePoint,
                                                        const std::string &subtraceFilepath);

                //! Add spatial entities from the provided subtrace to the resulting trace time point
                /*!
                 * \param subtraceTimePoint         The provided subtrace time point
                 * \param resultingTraceTimePoint   The resulting trace time point
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addSpatialEntitiesToResultingTraceTimePoint(const TimePoint &subtraceTimePoint,
                                                                 TimePoint &resultingTraceTimePoint,
                                                                 const std::string &subtraceFilepath);

                //! Add spatial entities of the given type from the provided subtrace to the resulting trace time point
                /*!
                 * \param spatialEntityType         The considered spatial entity type
                 * \param subtraceTimePoint         The provided subtrace time point
                 * \param resultingTraceTimePoint   The resulting trace time point
                 * \param subtraceFilepath          The path to the file containing the subtrace related information
                 */
                void addSpatialEntitiesToResultingTraceTimePoint(const SubsetSpecificType &spatialEntityType,
                                                                 const TimePoint &subtraceTimePoint,
                                                                 TimePoint &resultingTraceTimePoint,
                                                                 const std::string &subtraceFilepath);

                //! Add spatial entity to time point
                /*! If an equal value spatial entity already exists in the time point throw an exception.
                 *
                 * \param spatialEntity     The considered spatial entity
                 * \param spatialEntityType The considered spatial entity type
                 * \param timePoint         The time point to which the spatial entity is added
                 * \param subtraceFilepath  The path to the subtrace to which the spatial entity belongs
                 */
                void addSpatialEntityToTimePoint(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                 const SubsetSpecificType &spatialEntityType,
                                                 TimePoint &timePoint,
                                                 const std::string &subtraceFilepath);

                //! Replace the resulting trace time points values with the time points values read from file
                /*! If the number of time points in the time points values input file and the resulting trace
                 *  differ throw an exception.
                 */
                void updateResultingTraceTimePointsValues();

                //! Check if the number of time points is equal in the resulting trace and the time points values file
                void validateNumberOfTimePointsInResultingTrace();


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
