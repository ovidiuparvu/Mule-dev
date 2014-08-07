#ifndef SILHOUETTE_HPP
#define SILHOUETTE_HPP

#include "multiscale/analysis/spatial/Cluster.hpp"

using namespace std;


namespace multiscale {

    namespace analysis {

        //! Class for computing the "Silhouette" clustering index
        class Silhouette {

            public:

                //! Compute the overall average silhouette measure for the given collection of clusters
                /*!
                 * \param clusters Collection of all clusters
                 */
                static double computeOverallAverageMeasure(const vector<Cluster> &clusters);

                //! Compute the average silhouette measure for the given cluster
                /*!
                 * \param clusterIndex  The index of the cluster for which the average silhouette measure is computed
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageMeasure(unsigned int clusterIndex, const vector<Cluster> &clusters);

                //! Compute the silhouette measure for the given entity
                /*!
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeMeasure(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters);

            private:

                //! Compute the average dissimilarity within cluster to which the entity belongs
                /*!
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageDissimilarityWithinCluster(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters);

                //! Compute the average dissimilarity of the entity to the other clusters (i.e. clusters which are different from the cluster to which the entity belongs)
                /*!
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageDissimilarityToOtherClusters(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters);

                //! Compute the average dissimilarity between entity and cluster
                /*!
                 * \param entityIndex           The index of the entity in the cluster for which the distance is computed
                 * \param entityClusterIndex    The index of the cluster to which the entity belongs
                 * \param clusterIndex          The index of the cluster to which the average distance is computed
                 * \param clusters              Collection of all clusters
                 */
                static double computeAverageDissimilarityBtwEntityAndCluster(unsigned int entityIndex, unsigned int entityClusterIndex,
                                                                             unsigned int clusterIndex, const vector<Cluster> &clusters);

        };

    };

};


#endif
