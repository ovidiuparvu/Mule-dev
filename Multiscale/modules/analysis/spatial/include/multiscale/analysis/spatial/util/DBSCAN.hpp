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
                    distanceMatrix;                 /*!< The matrix containing the distances between any two
                                                         data points */

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

                //! Construct the distance matrix between any two data points
                /*!
                 * \param dataPoints Data points
                 */
                void constructDistanceMatrix(const std::vector<std::shared_ptr<DataPoint>> &dataPoints);

                //! Expand the cluster around the given core data point
                /*!
                 *  \param clusterIndexes       Indexes to which cluster each data point belongs
                 *  \param coreDataPointIndex   Core data point index
                 *  \param clusterId            Id of the cluster to which the core data point belongs
                 */
                bool expandCoreCluster(std::vector<int> &clusterIndexes, int coreDataPointIndex, int clusterId);

                //! Add all unclassified neighbour nodes to the seeds list
                /*!
                 * \param neighbours        Neighbour nodes
                 * \param clusterIndexes    Indexes to which cluster each data point belongs
                 * \param seeds             List of seeds (see DBSCAN algorithm)
                 */
                void addUnclassifiedNodesToSeedsList(const std::vector<int> &neighbours,
                                                     const std::vector<int> &clusterIndexes,
                                                     std::vector<int> &seeds);

               //! Label all unclassified and noise neighbour nodes as border nodes
               /*!
                * \param neighbours        Neighbour nodes
                * \param clusterIndexes    Indexes to which cluster each data point belongs
                */
                void labelUnclassifiedAndNoiseAsBorder(const std::vector<int> &neighbours,
                                                       std::vector<int> &clusterIndexes);

                //! Retrieve the list of neighbour indexes which are at a distance < eps far from the given data point
                /*!
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
                 * \param neighbours            Set of neighbours
                 * \param borderDataPointIndex  Index of the border data point
                 * \param clusterIndexes        Indexes to which cluster each data point belongs
                 */
                int findClosestCoreDataPoint(const std::vector<int> &neighbours, int borderDataPointIndex,
                                             const std::vector<int> &clusterIndexes);

                //! Allocate the distance matrix
                void allocateDistanceMatrix();

            public:

                // Constants
                static const int CLUSTERING_UNCLASSIFIED;
                static const int CLUSTERING_BORDER;
                static const int CLUSTERING_NOISE;


        };

    };

};


#endif
