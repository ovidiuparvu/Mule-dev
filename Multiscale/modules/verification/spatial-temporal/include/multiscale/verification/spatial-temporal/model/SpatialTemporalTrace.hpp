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

                std::vector<TimePoint> timePoints;          /*!< The array of time points */
                unsigned long          lastTimePointValue;  /*!< The value of the last added timepoint */

            public:

                SpatialTemporalTrace();
                SpatialTemporalTrace(const SpatialTemporalTrace &trace);
                ~SpatialTemporalTrace();

                //! Add a time point to the array
                /*!
                 * \param timePoint Time point added to the array
                 */
                void addTimePoint(TimePoint &timePoint);

                //! Get the time point at the given index in the array
                /*!
                 * \param index The index of the position in the array
                 */
                TimePoint &getTimePoint(unsigned int index);

                //! Get the length of the spatial temporal trace (i.e. number of timepoints)
                unsigned int length() const;

                //! Get the subtrace containing timepoints with the index greater than the given index
                /*!
                 * \param startIndex    The starting index of the subtrace
                 */
                SpatialTemporalTrace subTrace(unsigned int startIndex);

                //! Get the subtrace containing timepoints with values between the given values
                /*!
                 * \param startValue    The starting value of the subtrace
                 * \param endValue      The end value of the subtrace
                 */
                SpatialTemporalTrace subTrace(unsigned long startValue, unsigned long endValue);

                //! Get the subtrace containing timepoints with the index greater than the given index
                /*!
                 * \param trace         The spatial temporal trace
                 * \param startValue    The starting value of the subtrace
                 * \param endValue      The end value of the subtrace
                 */
                static SpatialTemporalTrace subTrace(const SpatialTemporalTrace &trace, unsigned int startIndex);

                //! Get the subtrace containing timepoints with values between the given values
                /*!
                 * \param trace         The spatial temporal trace
                 * \param startValue    The starting value of the subtrace
                 * \param endValue      The end value of the subtrace
                 */
                static SpatialTemporalTrace subTrace(const SpatialTemporalTrace &trace, unsigned long startValue,
                                                     unsigned long endValue);

            private:

                //! Update the last timepoint value
                /*!
                 * \param timePoint The last added timepoint
                 */
                void updateLastTimePointValue(TimePoint &timePoint);

                //! Update the last timepoint value considering the given timepoint value
                /*!
                 * \param timePoint         The last added timepoint
                 * \param timePointValue    The value of the current timepoint
                 */
                void updateLastTimePointValue(TimePoint &timePoint, unsigned long timePointValue);

                //! Check if the provided time point value is greater than the last time point value
                /*! The timepoint is considered to be uninitialised if the value is equal to the
                 *  maximum value which can be represented as an unsigned long.
                 *  Otherwise if the timepoint value is less or equal to the lastTimePointValue
                 *  then an exception is thrown.
                 *
                 * \param timePointValue    The value of the timepoint
                 */
                void validateTimePointValue(unsigned long timePointValue);

                //! Get the subtrace starting and ending with the given values
                /*!
                 * \param subTrace      The resulting subtrace
                 * \param startValue    The starting timepoint value of the subtrace
                 * \param endValue      The end timepoint value of the subtrace
                 */
                void getSubTrace(SpatialTemporalTrace &subTrace, unsigned long startValue, unsigned long endValue);

                //! Add the timepoints starting and ending with the given indices to the subtrace
                /*!
                 * \param subTrace      The resulting subtrace
                 * \param startValue    The starting timepoint index
                 * \param endValue      The end timepoint index
                 */
                void addTimePointsToSubTrace(SpatialTemporalTrace &subTrace, int startIndex, int endIndex);

                //! Get the index of the first timepoint which has a value greater than or equal to the given value
                /*!
                 * \param value     The given value
                 */
                int indexOfFirstTimePointGreaterOrEqualToValue(unsigned long value);

                //! Get the index of the last timepoint which has a value less than or equal to the given value
                /*!
                 * \param value     The given value
                 */
                int indexOfLastTimePointLessOrEqualToValue(unsigned long value);

                //! Check if the provided value pair is valid
                /*! Check if the provided timepoint values are smaller than the maximum timepoint value and
                 *  the end timepoint value is greater than the start timepoint value
                 *
                 * \param startValue    The start value
                 * \param endValue      The end value
                 */
                void validateValues(unsigned long startValue, unsigned long endValue);

                //! Check if the provided index is smaller than the number of timepoints
                /*!
                 * \param index The provided index
                 */
                void validateIndex(unsigned int index);

                //! Check if the provided value is smaller than or equal to the maximum timepoint value
                /*!
                 * \param value The provided value
                 */
                void validateValue(unsigned long value);


                // Constants
                static const std::string ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_START;
                static const std::string ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS_END;

                static const std::string ERR_TIMEPOINT_END_START;
                static const std::string ERR_TIMEPOINT_END_MIDDLE;
                static const std::string ERR_TIMEPOINT_END_END;

                static const std::string ERR_TIMEPOINT_VALUE_INVALID_START;
                static const std::string ERR_TIMEPOINT_VALUE_INVALID_MIDDLE;
                static const std::string ERR_TIMEPOINT_VALUE_INVALID_END;

                static const std::string ERR_ITERATOR_NEXT;

                static const int TIMEPOINT_INDEX_NOT_FOUND;

        };

    };

};

#endif
