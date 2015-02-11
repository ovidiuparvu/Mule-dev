#ifndef SILHOUETTE_HPP
#define SILHOUETTE_HPP

#include "multiscale/analysis/spatial/model/Cluster.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for computing the "Silhouette" clustering index
        class Silhouette {

            public:

                //! Compute the overall average silhouette measure for the given collection of clusters
                /*!
                 * \param clusters Collection of all clusters
                 */
                static double computeOverallAverageMeasure(const std::vector<Cluster> &clusters);

                //! Compute the average silhouette measure for the given cluster
                /*!
                 * \param clusterIndex  The index of the cluster for which the average silhouette measure
                 *                      is computed
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageMeasure(std::size_t clusterIndex, const std::vector<Cluster> &clusters);

                //! Compute the silhouette measure for the given entity
                /*!
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure
                 *                      is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeMeasure(std::size_t entityIndex, std::size_t clusterIndex,
                                             const std::vector<Cluster> &clusters);

            private:

                //! Compute the average dissimilarity within cluster to which the entity belongs
                /*!
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure
                 *                      is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageDissimilarityWithinCluster(std::size_t entityIndex,
                                                                       std::size_t clusterIndex,
                                                                       const std::vector<Cluster> &clusters);

                //! Compute the average dissimilarity of the entity to the other clusters
                /*! Compute the average dissimilarity of the entity to the other clusters (i.e. clusters which are
                 *  different from the cluster to which the entity belongs)
                 *
                 * \param entityIndex   The index of the entity in the cluster for which the silhouette measure
                 *                      is computed
                 * \param clusterIndex  The index of the cluster to which the entity belongs
                 * \param clusters      Collection of all clusters
                 */
                static double computeAverageDissimilarityToOtherClusters(std::size_t entityIndex,
                                                                         std::size_t clusterIndex,
                                                                         const std::vector<Cluster> &clusters);

                //! Compute the average dissimilarity between entity and cluster
                /*!
                 * \param entityIndex           The index of the entity in the cluster for which the distance
                 *                              is computed
                 * \param entityClusterIndex    The index of the cluster to which the entity belongs
                 * \param clusterIndex          The index of the cluster to which the average distance is computed
                 * \param clusters              Collection of all clusters
                 */
                static double computeAverageDissimilarityBtwEntityAndCluster(std::size_t entityIndex,
                                                                             std::size_t entityClusterIndex,
                                                                             std::size_t clusterIndex,
                                                                             const std::vector<Cluster> &clusters);

                //! Check if the provided cluster index is valid
                /*! The cluster index clusterIndex (0-based indexing) is valid if and only if:
                 *  0 <= clusterIndex < total number of clusters
                 *
                 * \param clusterIndex      The index of the cluster
                 * \param totalNrOfClusters The total number of clusters
                 */
                static void validateClusterIndex(std::size_t clusterIndex, std::size_t totalNrOfClusters);

                //! Check if the provided entity index is valid
                /*! The entity index entityIndex (0-based indexing) is valid if and only if:
                 *  0 <= entityIndex < total number of entities
                 *
                 * \param entityIndex       The index of the entity
                 * \param totalNrOfEntities The total number of entities
                 */
                static void validateEntityIndex(std::size_t entityIndex, std::size_t totalNrOfEntities);

                //! Check if the provided element index is valid
                /*! The element index elementIndex (0-based indexing) is valid if and only if:
                 *  0 <= elementIndex < total number of elements
                 *
                 * \param elementIndex      The index of the element
                 * \param totalNrOfElements The total number of elements
                 */
                static void validateElementIndex(std::size_t elementIndex, std::size_t totalNrOfElements);

        };

    };

};


#endif
