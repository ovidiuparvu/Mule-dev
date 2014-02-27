#ifndef SPATIALTEMPORALTRACE_HPP
#define SPATIALTEMPORALTRACE_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a spatial temporal trace
        class SpatialTemporalTrace {

            // Forward declaration of Iterator class
            class Iterator;

            // Friend classes
            friend class SpatialTemporalTrace::Iterator;

            private:

                std::vector<TimePoint> timePoints;          /*!< The array of time points */
                double                 lastTimePointValue;  /*!< The value of the last added timepoint */

            public:

                SpatialTemporalTrace();
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
                unsigned int length();

                //! Get the subtrace starting at the timepoint identified by the given index
                /*!
                 * \param startIndex    The starting position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace::Iterator subTrace(unsigned int startIndex);

                //! Get the subtrace starting and ending at the timepoints identified by the given indices
                /*!
                 * \param startIndex    The starting position of the subtrace in the initial trace
                 * \param endIndex      The end position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace::Iterator subTrace(unsigned int startIndex, unsigned endIndex);

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
                void updateLastTimePointValue(TimePoint &timePoint, double timePointValue);

                //! Check if the provided time point value is greater than the last time point value
                /*! The timepoint is considered to be uninitialised if the value is less than 0.
                 *  Otherwise if the timepoint value is less or equal to the lastTimePointValue
                 *  then an exception is thrown
                 *
                 * \param timePointValue    The value of the timepoint
                 */
                void validateTimePointValue(double timePointValue);

                //! Get the subtrace starting at the timepoint identified by the given index
                /*!
                 * \param startIndex    The starting position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace::Iterator getSubTrace(unsigned int startIndex);

                //! Get the subtrace starting and ending at the timepoints identified by the given indices
                /*!
                 * \param startIndex    The starting position of the subtrace in the initial trace
                 * \param endIndex      The end position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace::Iterator getSubTrace(unsigned int startIndex, unsigned int endIndex);

                //! Check if the provided index pair is valid
                /*! Check if the provided indices are smaller than the size of the timepoints vector and
                 *  the second timepoint is greater than the start timepoint
                 *
                 * \param startIndex    The start index
                 * \param endIndex      The end index
                 */
                void validateIndices(unsigned int startIndex, unsigned int endIndex);

                //! Check if the provided index is smaller than the size of the timepoints vector
                /*!
                 * \param index The provided index
                 */
                void validateIndex(unsigned int index);


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

        };

        //! Class for representing an iterator on a spatial temporal trace
        class SpatialTemporalTrace::Iterator {

            private:

                SpatialTemporalTrace    trace;                  /*!< The spatial temporal trace */

                unsigned int            currentTimePointIndex;  /*!< The index of  the current timepoint */

                unsigned int            startTimePointIndex;    /*!< The index of the start timepoint */
                unsigned int            endTimePointIndex;      /*!< The index of the end timepoint */

            public:

                //! Constructor with parameters
                /*!
                 * \param startTimePoint    The start timepoint
                 * \param endTimePoint      The end timepoint
                 */
                Iterator(const SpatialTemporalTrace &trace, unsigned int startTimePoint, unsigned int endTimePoint);
                ~Iterator();

                //! Return the next timepoint if it exists
                TimePoint& next();

                //! Check if there is a next timepoint
                bool hasNext();

                //! Reset currentTimePoint to its initial position (startTimePoint)
                void reset();

        };

    };

};

#endif
