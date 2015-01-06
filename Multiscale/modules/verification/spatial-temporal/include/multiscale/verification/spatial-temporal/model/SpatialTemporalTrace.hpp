#ifndef SPATIALTEMPORALTRACE_HPP
#define SPATIALTEMPORALTRACE_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal trace
        class SpatialTemporalTrace {

            private:

                std::vector<unsigned int>   beginIndices;       /*!< The stack of stored trace begin indices */
                unsigned int                beginIndex;         /*!< The currently employed trace begin index */

                std::vector<TimePoint>      timePoints;         /*!< The array of time points */
                unsigned long               lastTimePointValue; /*!< The value of the last added timepoint */

                bool isLastTimePointValueInitialised;  /*!< Flag to indicate if the last time point value was initialised */

            public:

                SpatialTemporalTrace();
                SpatialTemporalTrace(const SpatialTemporalTrace &trace);
                ~SpatialTemporalTrace();

                //! Add a time point to the array
                /*!
                 * \param timePoint Time point added to the array
                 */
                void addTimePoint(const TimePoint &timePoint);

                //! Clear all the stored timepoints and reinitialise
                void clear();

                //! Get the time point at the given index in the array
                /*!
                 * \param index The index of the position in the array
                 */
                TimePoint getTimePoint(unsigned int index) const;

                //! Get the reference to the time point at the given index in the array
                /*!
                 * \param index The index of the position in the array
                 */
                TimePoint& getTimePointReference(unsigned int index);

                //! Get the reference to the time point at the given index in the array
                /*!
                 * \param index The index of the position in the array
                 */
                const TimePoint& getTimePointReference(unsigned int index) const;

                //! Get the length of the spatial temporal trace (i.e. number of timepoints)
                unsigned int length() const;

                //! Get the value of the next timepoint considering beginIndex
                unsigned long nextTimePointValue() const;

                //! Set the subtrace containing timepoints with values greater or equal to the given start value
                /*!
                 * \param startValue    The starting value of the subtrace
                 */
                void setSubTraceWithTimepointsValuesGreaterOrEqualTo(unsigned long startValue);

                //! Advance the trace begin index by the given value
                /*!
                 * \param advanceValue  The value by which the trace begin index should be advanced
                 */
                void advanceTraceBeginIndex(unsigned long advanceValue);

                //! Set the trace begin index to the given value
                /*!
                 * \param newBeginIndex The new value of the trace starting/begin index
                 */
                void setTraceBeginIndex(unsigned int newBeginIndex);

                //! Add the current value of beginIndex to the beginIndices stack
                void storeSubTraceBeginIndex();

                //! Retrieve the value of the most recent stored subtrace begin index
                /*! If the beginIndices stack is non-empty then retrieve the top
                 *  value in the stack. Otherwise return 0.
                 */
                unsigned int getMostRecentlyStoredSubTraceBeginIndex();

                //! Restore the subtrace beginIndex from the beginIndices stack
                /*! If the beginIndices stack is non-empty then the value of beginIndex
                 *  will be equal to the top value in the stack. Otherwise the value of
                 *  beginIndex will be set to 0.
                 *
                 *  If the value of beginIndex is updated from the beginIndices stack then
                 *  the top value is popped out of the stack.
                 */
                void restoreSubTraceBeginIndex();

                // Check if two spatial temporal traces (this instance and the provided one) are equal
                /*!
                 * \param rhsSpatialTemporalTrace   The provided spatial temporal trace against which this trace
                 *                                  is compared
                 */
                bool operator==(const SpatialTemporalTrace &rhsSpatialTemporalTrace);

            private:

                //! Initialise the member fields
                void initialise();

                //! Update the last timepoint value
                /*!
                 * \param timePoint The last added timepoint
                 */
                void updateLastTimePointValue(TimePoint &timePoint);

                //! Check if the provided time point value is greater than the last time point value
                /*! The timepoint is considered to be uninitialised if the value is equal to the
                 *  maximum value which can be represented as an unsigned long.
                 *  Otherwise if the timepoint value is less or equal to the lastTimePointValue
                 *  then an exception is thrown.
                 *
                 * \param timePoint    The given time point
                 */
                void validateTimePointValue(const TimePoint &timePoint);

                //! Check if the provided time point value is greater than the last time point value
                /*! The timepoint is considered to be uninitialised if the value is equal to the
                 *  maximum value which can be represented as an unsigned long.
                 *  Otherwise if the timepoint value is less or equal to the lastTimePointValue
                 *  then an exception is thrown.
                 *
                 * \param timePointValue    The value of the timepoint
                 */
                void validateTimePointValue(unsigned long timePointValue);

                //! Set the begin index for the subtrace starting with the given value
                /*!
                 * \param startValue    The starting timepoint value of the subtrace
                 */
                void setSubTraceIndex(unsigned long startValue);

                //! Get the value of the next timepoint when beginIndex is the index of the last timepoint
                /*!
                 *  Return maximum unsigned long value if the value of the
                 *  last timepoint is smaller than the maximum unsigned long value.
                 *  Otherwise throw an exception.
                 */
                unsigned long nextTimePointValueForLastTimePoint() const;

                //! Add the timepoints starting and ending with the given indices to the subtrace
                /*!
                 * \param subTrace      The resulting subtrace
                 * \param startIndex    The starting timepoint index
                 * \param endIndex      The end timepoint index
                 */
                void addTimePointsToSubTrace(SpatialTemporalTrace &subTrace, int startIndex, int endIndex) const;

                //! Get the index of the first timepoint which has a value greater than or equal to the given value
                /*!
                 * \param value     The given value
                 */
                int indexOfFirstTimePointGreaterOrEqualToValue(unsigned long value) const;

                //! Check if relative to beginIndex the provided index is smaller than the number of timepoints
                /*!
                 * \param index The provided index
                 */
                void validateIndexRelativeToBeginIndex(unsigned int index) const;

                //! Check if the provided absolute index is smaller than the number of timepoints
                /*!
                 * \param index The provided index
                 */
                void validateAbsoluteIndex(unsigned int index) const;

                //! Check if the provided value is smaller than or equal to the maximum timepoint value
                /*!
                 * \param value The provided value
                 */
                void validateValue(unsigned long value) const;


                // Constants
                static const std::string ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START;
                static const std::string ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_MIDDLE;
                static const std::string ERR_RELATIVE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END;

                static const std::string ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START;
                static const std::string ERR_ABSOLUTE_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END;

                static const std::string ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_START;
                static const std::string ERR_TIMEPOINT_VALUE_OUT_OF_BOUNDS_END;

                static const std::string ERR_TIMEPOINT_END_START;
                static const std::string ERR_TIMEPOINT_END_MIDDLE;
                static const std::string ERR_TIMEPOINT_END_END;

                static const std::string ERR_TIMEPOINT_VALUE_INVALID_START;
                static const std::string ERR_TIMEPOINT_VALUE_INVALID_MIDDLE;
                static const std::string ERR_TIMEPOINT_VALUE_INVALID_END;

                static const std::string ERR_NEXT_TIMEPOINT_VALUE_NOT_EXISTS;

                static const std::string ERR_ITERATOR_NEXT;

                static const int TIMEPOINT_INDEX_NOT_FOUND;

        };

    };

};


#endif
