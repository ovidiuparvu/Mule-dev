#ifndef DBSCAN_HPP
#define DBSCAN_HPP

#include "multiscale/analysis/spatial/model/DataPoint.hpp"

#include <memory>
#include <vector>


namespace multiscale {

    namespace analysis {

        //! Class which implements an improved version of the DBSCAN algorithm
        class DBSCAN {

            private:

                double eps;                         /*!< DBSCAN algorithm parameter for specifying the maximum radius
                                                         of the neighbourhood */
                unsigned int minPoints;             /*!< DBSCAN algorithm parameter for specifying the minimum number
                                                         of points in an eps-neighbourhood of that point */

                unsigned int nrOfDataPoints;        /*!< Number of data points in the data set */

                std::vector<std::vector<double>>
                    distancesMatrix;                /*!< The matrix containing the distances between each possible
                                                         pair of datapoints */
                std::vector<std::vector<int>>
                    neighboursIndicesMatrix;        /*!< The matrix containing for each data point a vector of
                                                         indices corresponding to the neighbouring data points */

            public:

                DBSCAN();
                ~DBSCAN();

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
                void run(const std::vector<std::shared_ptr<DataPoint>> &dataPoints,
                         std::vector<int> &clusterIndexes, int &nrOfClusters,
                         double eps, int minPoints);

            private:

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
                 */
                void runAlgorithm(const std::vector<std::shared_ptr<DataPoint>> &dataPoints,
                                  std::vector<int> &clusterIndexes, int &nrOfClusters);

                //! Construct the distances matrix
                /*!
                 * \param dataPoints The considered data points
                 */
                void constructDistancesMatrix(const std::vector<std::shared_ptr<DataPoint>> &dataPoints);

                //! Construct the neighbours indices matrix
                /*!
                 * \param dataPoints The considered data points
                 */
                void constructNeighboursIndicesMatrix(const std::vector<std::shared_ptr<DataPoint>> &dataPoints);

                //! Expand the cluster around the given core data point
                /*!
                 *  \param clusterIndexes       Indexes to which cluster each data point belongs
                 *  \param coreDataPointIndex   Core data point index
                 *  \param clusterId            Id of the cluster to which the core data point belongs
                 */
                bool expandCoreCluster(std::vector<int> &clusterIndexes, int coreDataPointIndex, int clusterId);

                //! Process the collection of provided seeds (see DBSCAN algorithm for details)
                /*!
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 * \param clusterId         The index of the data point to which the seeds correspond
                 * \param seeds             The collection of seeds
                 * \param consideredSeeds   The collection of previously considered seeds
                 */
                void processSeeds(std::vector<int> &clusterIndexes, int clusterId,
                                  std::vector<int> &seeds, std::vector<bool> &consideredSeeds);

                //! Add all unclassified previously not considered neighbour nodes to the seeds list
                /*! A node is added to the seed list only if it was not considered already
                 *
                 * \param neighbours        Neighbour nodes
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 * \param seeds             List of seeds (see DBSCAN algorithm)
                 * \param consideredSeeds   List of previously considered seeds
                 */
                void addUnclassifiedNodesToSeedsList(const std::vector<int> &neighbours,
                                                     const std::vector<int> &clusterIndexes,
                                                     std::vector<int> &seeds,
                                                     std::vector<bool> &consideredSeeds);

               //! Label all unclassified and noise neighbour nodes as border nodes
               /*!
                * \param neighbours        Neighbour nodes
                * \param clusterIndexes    Indexes to which cluster each data point belongs
                */
                void labelUnclassifiedAndNoiseAsBorder(const std::vector<int> &neighbours,
                                                       std::vector<int> &clusterIndexes);

                //! Retrieve the list of neighbour indexes for the given data point
                /*! Retrieve the list of neighbour indexes which are at a distance < eps
                 *  far from the given data point
                 *
                 * \param dataPointIndex    Index of the data point for which the neighbours will be retrieved
                 */
                std::vector<int> retrieveNeighbours(int dataPointIndex);

                //! Assign the border nodes to the clusters to which the closest core objects belong
                /*!
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 */
                void assignBorderNodesToClusters(std::vector<int> &clusterIndexes);

                //! Find the closest core data point from the given set of neighbours to the given border data point
                /*!
                 * \param borderDataPointIndex  Index of the border data point
                 * \param clusterIndexes        Indexes to which cluster each data point belongs
                 */
                int findClosestCoreDataPoint(int borderDataPointIndex,
                                             const std::vector<int> &clusterIndexes);

                //! Allocate the distances matrix
                void allocateDistancesMatrix();

                //! Allocate the neighbours indices matrix
                void allocateNeighboursIndicesMatrix();

            public:

                // Constants
                static const int CLUSTERING_UNCLASSIFIED;
                static const int CLUSTERING_BORDER;
                static const int CLUSTERING_NOISE;


        };

    };

};


#endif
