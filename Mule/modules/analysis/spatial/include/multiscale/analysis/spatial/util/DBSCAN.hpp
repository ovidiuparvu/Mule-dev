#ifndef DBSCAN_HPP
#define DBSCAN_HPP

#include <cassert>
#include <limits>
#include <memory>
#include <vector>


namespace multiscale {

    namespace analysis {

        //! Enumeration for storing the DBSCAN point clustering tags
        enum class DBSCANPointClusteringTag : int {
            UNCLASSIFIED  = -2,     /*!< The point was not attributed to a cluster */
            BORDER        = -1,     /*!< The point is a border point */
            NOISE         = 0       /*!< The point is noise */
        };


        //! Class which implements an improved version of the DBSCAN algorithm
        template <typename PointType>
        class DBSCAN {

            private:

                double eps;                         /*!< DBSCAN algorithm parameter for specifying the maximum radius
                                                         of the neighbourhood */
                std::size_t minPoints;              /*!< DBSCAN algorithm parameter for specifying the minimum number
                                                         of points in an eps-neighbourhood of that point */

                std::size_t nrOfDataPoints;         /*!< Number of data points in the data set */

                std::vector<std::vector<double>>
                    distancesMatrix;                /*!< The matrix containing the distances between each possible
                                                         pair of datapoints */
                std::vector<std::vector<std::size_t>>
                    neighboursIndicesMatrix;        /*!< The matrix containing for each data point a vector of
                                                         indices corresponding to the neighbouring data points */

            public:

                DBSCAN(): eps(0), minPoints(0), nrOfDataPoints(0) {}

                ~DBSCAN() {
                    distancesMatrix.clear();
                    neighboursIndicesMatrix.clear();
                }

                //! Run the improved DBSCAN algorithm on the provided set of points
                /*! The implementation of the improved DBSCAN algorithm is based on the paper:
                 *  T. N. Tran, K. Drab, and M. Daszykowski, ‘Revised DBSCAN algorithm to cluster data with
                 *  dense adjacent clusters’, Chemometrics and Intelligent Laboratory Systems, vol. 120,
                 *  pp. 92–96, Jan. 2013.
                 *
                 * Clusters start from index 1, because cluster 0 contains only noise data/points.
                 *
                 *  \param dataPoints       Collection of data points
                 *  \param clusterIndexes   Indexes to which cluster each data point belongs
                 *  \param nrOfClusters     Total number of clusters
                 *  \param eps              Maximum distance between two neighbours
                 *  \param minPoints        Minimum number of points in one cluster
                 */
                void run(const std::vector<PointType> &dataPoints,
                         std::vector<int> &clusterIndexes,
                         std::size_t &nrOfClusters, double eps, int minPoints) {
                    this->eps       = eps;
                    this->minPoints = minPoints;

                    nrOfDataPoints  = dataPoints.size();

                    constructDistancesMatrix(dataPoints);
                    constructNeighboursIndicesMatrix(dataPoints);

                    runAlgorithm(dataPoints, clusterIndexes, nrOfClusters);
                }

            private:

                //! Run the improved DBSCAN algorithm on the provided set of points
                /*!
                 *  \param dataPoints       Collection of data points
                 *  \param clusterIndexes   Indexes to which cluster each data point belongs
                 *  \param nrOfClusters     Total number of clusters
                 */
                void runAlgorithm(const std::vector<PointType> &dataPoints,
                                  std::vector<int> &clusterIndexes,
                                  std::size_t &nrOfClusters) {
                    nrOfClusters = 1;

                    // Mark all points as unclassified
                    clusterIndexes.resize(nrOfDataPoints, static_cast<int>(DBSCANPointClusteringTag::UNCLASSIFIED));

                    // Main part of improved DBSCAN algorithm
                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        if (clusterIndexes[i] == CLUSTERING_UNCLASSIFIED) {
                            if (expandCoreCluster(clusterIndexes, i, nrOfClusters)) {
                                nrOfClusters++;
                            }
                        }
                    }

                    assignBorderNodesToClusters(clusterIndexes);
                }

                //! Construct the distances matrix
                /*!
                 * \param dataPoints The considered data points
                 */
                void constructDistancesMatrix(const std::vector<PointType> &dataPoints) {
                    allocateDistancesMatrix();

                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        for (std::size_t j = 0; j < i; j++) {
                            distancesMatrix[i][j] = dataPoints[i].distanceTo(dataPoints[j]);
                            distancesMatrix[j][i] = distancesMatrix[i][j];
                        }
                    }
                }

                //! Construct the neighbours indices matrix
                /*!
                 * \param dataPoints The considered data points
                 */
                void constructNeighboursIndicesMatrix(const std::vector<PointType> &dataPoints) {
                    allocateNeighboursIndicesMatrix();

                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        for (std::size_t j = 0; j <= i; j++) {
                            if (distancesMatrix[i][j] < eps) {
                                neighboursIndicesMatrix[i].push_back(j);
                                neighboursIndicesMatrix[j].push_back(i);
                            }
                        }
                    }
                }

                //! Expand the cluster around the given core data point
                /*!
                 *  \param clusterIndexes       Indexes to which cluster each data point belongs
                 *  \param coreDataPointIndex   Core data point index
                 *  \param clusterId            Id of the cluster to which the core data point belongs
                 */
                bool expandCoreCluster(std::vector<int> &clusterIndexes,
                                       std::size_t coreDataPointIndex, std::size_t clusterId) {
                    std::vector<std::size_t> seeds = retrieveNeighbours(coreDataPointIndex);

                    if (seeds.size() < minPoints) {
                        // Mark data point as noise
                        clusterIndexes[coreDataPointIndex] = CLUSTERING_NOISE;

                        return false;
                    } else {
                        std::vector<bool> consideredSeeds = std::vector<bool>(nrOfDataPoints, false);

                        processSeeds(
                            clusterIndexes, clusterId,
                            seeds, consideredSeeds
                        );

                        return true;
                    }
                }

                //! Process the collection of provided seeds (see DBSCAN algorithm for details)
                /*!
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 * \param clusterId         The index of the data point to which the seeds correspond
                 * \param seeds             The collection of seeds
                 * \param consideredSeeds   The collection of previously considered seeds
                 */
                void processSeeds(std::vector<int> &clusterIndexes, std::size_t clusterId,
                                  std::vector<std::size_t> &seeds, std::vector<bool> &consideredSeeds) {
                    std::size_t currentSeedIndex = 0;

                    while (currentSeedIndex < seeds.size()) {
                        std::vector<std::size_t> neighbours = retrieveNeighbours(seeds[currentSeedIndex]);

                        if (neighbours.size() >= minPoints) {
                            // Assign data point to cluster identified by clusterId
                            clusterIndexes[seeds[currentSeedIndex]] = clusterId;

                            addUnclassifiedNodesToSeedsList(neighbours, clusterIndexes, seeds, consideredSeeds);
                            labelUnclassifiedAndNoiseAsBorder(neighbours, clusterIndexes);
                        }

                        // Update the list of visited seeds
                        consideredSeeds[seeds[currentSeedIndex]] = true;

                        currentSeedIndex++;
                    }
                }

                //! Add all unclassified previously not considered neighbour nodes to the seeds list
                /*! A node is added to the seed list only if it was not considered already
                 *
                 * \param neighbours        Neighbour nodes
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 * \param seeds             List of seeds (see DBSCAN algorithm)
                 * \param consideredSeeds   List of previously considered seeds
                 */
                void addUnclassifiedNodesToSeedsList(const std::vector<std::size_t> &neighbours,
                                                     const std::vector<int> &clusterIndexes,
                                                     std::vector<std::size_t> &seeds,
                                                     std::vector<bool> &consideredSeeds) {
                    for (auto neighbour : neighbours) {
                        if (clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) {
                            if (consideredSeeds[neighbour] == false) {
                                seeds.push_back(neighbour);

                                consideredSeeds[neighbour] = true;
                            }
                        }
                    }
                }

               //! Label all unclassified and noise neighbour nodes as border nodes
               /*!
                * \param neighbours        Neighbour nodes
                * \param clusterIndexes    Indexes to which cluster each data point belongs
                */
                void labelUnclassifiedAndNoiseAsBorder(const std::vector<std::size_t> &neighbours,
                                                       std::vector<int> &clusterIndexes) {
                    for (auto neighbour : neighbours) {
                        if ((clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) ||
                            (clusterIndexes[neighbour] == CLUSTERING_NOISE)) {
                            clusterIndexes[neighbour] = CLUSTERING_BORDER;
                        }
                    }
                }

                //! Retrieve the list of neighbour indexes for the given data point
                /*! Retrieve the list of neighbour indexes which are at a distance < eps
                 *  far from the given data point
                 *
                 * \param dataPointIndex    Index of the data point for which the neighbours will be retrieved
                 */
                std::vector<std::size_t> retrieveNeighbours(std::size_t dataPointIndex) {
                    return (
                        neighboursIndicesMatrix[dataPointIndex]
                    );
                }

                //! Assign the border nodes to the clusters to which the closest core objects belong
                /*!
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 */
                void assignBorderNodesToClusters(std::vector<int> &clusterIndexes) {
                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        if (clusterIndexes[i] == static_cast<int>(DBSCANPointClusteringTag::BORDER)) {
                            std::size_t closestCoreDataPoint = findClosestCoreDataPoint(i, clusterIndexes);

                            clusterIndexes[i] = clusterIndexes[closestCoreDataPoint];
                        }
                    }
                }

                //! Find the closest core data point from the given set of neighbours to the given border data point
                /*!
                 * \param borderDataPointIndex  Index of the border data point
                 * \param clusterIndexes        Indexes to which cluster each data point belongs
                 */
                std::size_t findClosestCoreDataPoint(std::size_t borderDataPointIndex,
                                                     const std::vector<int> &clusterIndexes) {
                    std::vector<std::size_t> neighbours = retrieveNeighbours(borderDataPointIndex);

                    double      minDistance      = std::numeric_limits<double>::max();
                    std::size_t minDistanceIndex = -1;

                    for (auto neighbourIndex : neighbours) {
                        // Check if the neighbour is a core data point
                        if (clusterIndexes[neighbourIndex] > 0) {
                            if (distancesMatrix[borderDataPointIndex][neighbourIndex] < minDistance) {
                                minDistance = distancesMatrix[borderDataPointIndex][neighbourIndex];
                                minDistanceIndex = neighbourIndex;
                            }
                        }
                    }

                    return minDistanceIndex;
                }

                //! Allocate the distances matrix
                void allocateDistancesMatrix() {
                    distancesMatrix.clear();

                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        distancesMatrix.push_back(
                            std::vector<double>(nrOfDataPoints, 0)
                        );
                    }
                }

                //! Allocate the neighbours indices matrix
                void allocateNeighboursIndicesMatrix() {
                    neighboursIndicesMatrix.clear();

                    for (std::size_t i = 0; i < nrOfDataPoints; i++) {
                        neighboursIndicesMatrix.push_back(
                            std::vector<std::size_t>()
                        );
                    }
                }

            public:

                // Constants
                static const int CLUSTERING_UNCLASSIFIED = -2;
                static const int CLUSTERING_BORDER       = -1;
                static const int CLUSTERING_NOISE        = 0;

        };

    };

};


#endif
