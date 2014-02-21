#ifndef SPATIALTEMPORALTRACE_HPP
#define SPATIALTEMPORALTRACE_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        class SpatialTemporalTrace {

            private:

                std::vector<TimePoint> timePoints;  /*!< The array of time points */

            public:

                SpatialTemporalTrace();
                ~SpatialTemporalTrace();

                //! Add a time point to the array
                /*!
                 * \param timePoint Time point added to the array
                 */
                void addTimePoint(const TimePoint &timePoint);

                //! Get the time point at the given index in the array
                /*!
                 * \param index The index of the position in the array
                 */
                TimePoint &getTimePoint(unsigned int index);

                //! Get the length of the spatial temporal trace (i.e. number of timepoints)
                unsigned int length();

                //! Get the subtrace starting at the timepoint identified by the given index
                /*!
                 * \param startIndex The starting position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace subTrace(unsigned int startIndex);

            private:

                //! Get the subtrace starting at the timepoint identified by the given index
                /*!
                 * \param startIndex The starting position of the subtrace in the initial trace
                 */
                SpatialTemporalTrace getSubTrace(unsigned int startIndex);

                //! Check if the provided index is smaller than the size of the timepoints vector
                /*!
                 * \param index The provided index
                 */
                void validateIndex(unsigned int index);

                // Constants
                static const std::string ERR_TIMEPOINT_INDEX_OUT_OF_BOUNDS;

        };

    };

};

#endif
