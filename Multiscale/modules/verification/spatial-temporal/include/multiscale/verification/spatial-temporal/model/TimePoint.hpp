#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the considered spatial entity type(s)
        enum class ConsideredSpatialEntityType : int {
            All,        /*!< All */
            Clusters,   /*!< Clusters */
            Regions     /*!< Regions */
        };


        //! Class for representing a timepoint
        class TimePoint {

            private:

                unsigned long value;   /*!< The value of the timepoint within a simulation/experiment */

                std::set<Cluster>  clusters;     /*!< The set of clusters */
                std::set<Region>   regions;      /*!< The set of regions */

                std::map<std::string, double>   numericStateVariables;      /*!< The associative map for storing numeric state variables */

                ConsideredSpatialEntityType consideredSpatialEntityType;    /*!< The considered spatial entity type */

            public:

                TimePoint(unsigned long value = std::numeric_limits<unsigned long>::max());
                TimePoint(const TimePoint &timePoint);
                ~TimePoint();

                //! Get the value of the timepoint
                unsigned long getValue() const;

                //! Set the value of the timepoint
                /*!
                 * \param value The value of the timepoint
                 */
                void setValue(unsigned long value);

                //! Add a cluster to the list of clusters
                /*!
                 * \param cluster The cluster to be added
                 */
                void addCluster(const Cluster &cluster);

                //! Add a region to the list of regions
                /*!
                 * \param region The region to be added
                 */
                void addRegion(const Region &region);

                //! Add a numeric state variable to the map
                /*!
                 * If a numeric state variable with the same name exists then the value
                 * of the existing numeric state variable will be replaced by the provided
                 * new value.
                 *
                 * \param name  The name of the numeric state variable
                 * \param value The value of the numeric state variable
                 */
                void addNumericStateVariable(const std::string &name, double value);

                //! Check if the numeric state variable with the given name exists
                /*!
                 * \param name The name of the numeric state variable
                 */
                bool existsNumericStateVariable(const std::string &name);

                //! Get the set of clusters
                std::set<Cluster> getClusters() const;

                //! Get the set of regions
                std::set<Region> getRegions() const;

                //! Get the value of the numeric state variable with the given name if it exists and throw an exception otherwise
                /*!
                 * \param name The name of the numeric state variable
                 */
                double getNumericStateVariable(const std::string &name) const;

                //! Compute the difference of this timepoint and the given timepoint
                /*! Compute the difference of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                template <class InputIterator1, class InputIterator2, class OutputIterator>
                void timePointDifference(const TimePoint &timePoint) {
                    timePointSetOperation(
                        timePoint,
                        [] (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                            InputIterator2 last2, OutputIterator result)
                            {
                                std::set_difference(first1, last1, first2, last2, result);
                            }
                    );
                }

                //! Compute the intersection of this timepoint and the given timepoint
                /*! Compute the intersection of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                template <class InputIterator1, class InputIterator2, class OutputIterator>
                void timePointIntersection(const TimePoint &timePoint) {
                    timePointSetOperation(
                        timePoint,
                        [] (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                            InputIterator2 last2, OutputIterator result)
                            {
                                std::set_intersection(first1, last1, first2, last2, result);
                            }
                    );
                }

                //! Compute the union of this timepoint and the given timepoint
                /*! Compute the union of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                template <class InputIterator1, class InputIterator2, class OutputIterator>
                void timePointUnion(const TimePoint &timePoint) {
                    timePointSetOperation(
                        timePoint,
                        [] (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                            InputIterator2 last2, OutputIterator result)
                            {
                                std::set_union(first1, last1, first2, last2, result);
                            }
                    );
                }

                //! Remove the cluster from the given position
                /*!
                 * \param position  The position of the cluster to be removed
                 */
                void removeCluster(const std::set<Cluster>::iterator &position);

                //! Remove the region from the given position
                /*!
                 * \param position  The position of the region to be removed
                 */
                void removeRegion(const std::set<Region>::iterator &position);

                //! Set the considered spatial entity type
                /*!
                 * \param consideredSpatialEntityType   The considered type of the spatial entities
                 */
                void setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType);

            private:

                //! Compute the given set operation of this timepoint and the given timepoint considering the given set operation type
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                void timePointSetOperation(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    switch (consideredSpatialEntityType) {
                        case ConsideredSpatialEntityType::All:
                            timePointSetOperationAll(timePoint, setOperationType);
                            break;

                        case ConsideredSpatialEntityType::Clusters:
                            timePointSetOperationClusters(timePoint, setOperationType);
                            break;

                        case ConsideredSpatialEntityType::Regions:
                            timePointSetOperationRegions(timePoint, setOperationType);
                            break;
                    }
                }

                //! Compute the given set operation of this timepoint and the given timepoint considering all spatial entities
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                void timePointSetOperationAll(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    clusters = clustersSetOperation(timePoint, setOperationType);
                    regions  = regionsSetOperation(timePoint, setOperationType);
                }

                //! Compute the given set operation of this timepoint and the given timepoint considering clusters
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                void timePointSetOperationClusters(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    clusters = clustersSetOperation(timePoint, setOperationType);
                }

                //! Compute the given set operation of this timepoint and the given timepoint considering regions
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                void timePointSetOperationRegions(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    regions  = regionsSetOperation(timePoint, setOperationType);
                }

                //! Compute the given set operation of this set of clusters and the one provided by the given timepoint
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                std::set<Cluster> clustersSetOperation(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    std::set<Cluster> newClusters;
                    std::set<Cluster> timePointClusters = timePoint.getClusters();

                    SetOperation(clusters.begin(), clusters.end(), timePointClusters.begin(),
                                 timePointClusters.end(), newClusters.begin());

                    return newClusters;
                }

                //! Compute the given set operation of this set of regions and the one provided by the given timepoint
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                template <typename SetOperation>
                std::set<Region> regionsSetOperation(const TimePoint &timePoint, SetOperation &&setOperationType) {
                    std::set<Region> newRegions;
                    std::set<Region> timePointRegions = timePoint.getRegions();

                    SetOperation(regions.begin(), regions.end(), timePointRegions.begin(),
                                 timePointRegions.end(), newRegions.begin());

                    return newRegions;
                }


                // Constants
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX;
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX;

        };

    };

};

#endif
