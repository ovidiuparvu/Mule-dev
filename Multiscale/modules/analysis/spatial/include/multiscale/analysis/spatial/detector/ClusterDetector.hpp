#ifndef CLUSTERDETECTOR_HPP
#define CLUSTERDETECTOR_HPP

#include "multiscale/analysis/spatial/detector/Detector.hpp"
#include "multiscale/analysis/spatial/model/Cluster.hpp"
#include "multiscale/analysis/spatial/model/Entity.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in 2D images
        class ClusterDetector : public Detector {

            protected:

                double singleEntityIntensity;   /*!< The intensity (pile up degree) of a grid position
                                                     occupied by a single entity */

                unsigned int maxPileupNumber;   /*!< The maximum number of entities which can occupy
                                                     the same grid position */

                int eps;                        /*!< DBSCAN algorithm parameter for specifying the maximum radius
                                                     of the neighbourhood */
                int minPoints;                  /*!< DBSCAN algorithm parameter for specifying the minimum number
                                                     of points in an eps-neighbourhood of that point */

                std::vector<Cluster> clusters;  /*!< Clusters found in the image */

            public:

                ClusterDetector(unsigned int maxPileupNumber,
                                bool isDebugMode = false);
                virtual ~ClusterDetector();

                //! Get the value of the clustering algorithm parameter eps
                double getEps();

                //! Get the value of the clustering algorithm parameter MinPoints
                int getMinPoints();

                //! Get a const reference to the vector of detected clusters
                std::vector<Cluster> const &getClusters();

                //! Set the value of the clustering algorithm parameter eps
                /*!
                 * \param eps Value of the clustering algorithm parameter eps
                 */
                void setEps(double eps);

                //! Set the value of the clustering algorithm parameter MinPoints
                /*!
                 * \param minPoints Value of the clustering algorithm parameter MinPoints
                 */
                void setMinPoints(int minPoints);

            protected:

                //! Initialise clustering values
                void initialiseDetectorSpecificFields() override;

                //! Create the trackbars
                void createDetectorSpecificTrackbars() override;

                //! Clear the clusters from the previous detection
                void clearPreviousDetectionResults() override;

                //! Get the type of the detector as a string
                std::string getDetectorTypeAsString() override;

                //! Process the provided image and detect clusters in it
                void processImageAndDetect() override;

                //! Detect the entities in the image
                /*! Detect the entities in the image, compute their centre point and degree of pile up
                 *
                 *  \param entities Entities detected in the image
                 */
                virtual void detectEntitiesInImage(std::vector<Entity> &entities) = 0;

                //! Detect and analyse the clusters of entities in the image
                /*! Detect and analyse the clusters of entities in the image
                 *
                 *  Remark: The "noise" cluster will be ignored.
                 *
                 *  \param entities     Entities detected in the image
                 *  \param clusters     Clusters of entities detected in the image
                 */
                void detectAndAnalyseClusters(const std::vector<Entity> &entities, std::vector<Cluster> &clusters);

                //! Detect the clusters of entities in the image
                /*! Detect the clusters of entities in the image using Density Based scan (DBscan) clustering algorithm
                 *  Clusters start from index 1, because cluster 0 contains only noise data/points.
                 *
                 *  \param entities         Entities detected in the image
                 *  \param clusterIndexes   Indexes to which cluster each entity belongs
                 *  \param nrOfClusters     Total number of clusters
                 */
                void detectClusters(const std::vector<Entity> &entities,
                                    std::vector<int> &clusterIndexes,
                                    std::size_t &nrOfClusters);

                //! Flatten the collection of entities
                /*! Add each piled up entity in the original collection as a single
                 *  standing entity in the resulting collection. The first entities
                 *  in the resulting collection are the entities in the given collection.
                 *  All piled up entities are added afterwards in the resulting collection.
                 *
                 * \param entities Entities detected in the image
                 */
                std::vector<Entity> flattenEntitiesCollection(const std::vector<Entity> &entities);

                //! Add the piled up entities to the flattened collection of entities
                /*!
                 * \param entities          Entities detected in the image
                 * \param flattenedEntities Flattened collection of entities
                 */
                void addPiledUpEntitiesToCollection(const std::vector<Entity> &entities,
                                                    std::vector<Entity> &flattenedEntities);

                //! Add the entities to the clusters as indicated by the clusterIndexes parameter
                /*! Add the entities to the clusters as indicated by the clusterIndexes parameter
                 *
                 * The "noise" cluster will be ignored.
                 *
                 *  \param entities         Entities detected in the image
                 *  \param clusterIndexes   Indexes to which cluster each entity belongs
                 *  \param nrOfClusters     Total number of clusters
                 *  \param clusters         Collection of clusters, each one with the updated measures
                 */
                void addEntitiesToClusters(const std::vector<Entity> &entities,
                                           const std::vector<int> &clusterIndexes,
                                           std::size_t nrOfClusters,
                                           std::vector<Cluster> &clusters);

                //! Analyse the clusters
                /*! Analyse the clusters and compute the angle and distance from the centre,
                 *  average clusteredness degree and pile up degree
                 *
                 *  \param clusters Collection of clusters, each one with the updated measures
                 */
                void analyseClusters(std::vector<Cluster> &clusters);

                //! Analyse the clusters and compute the origin dependent values
                /*! The values which depend on the origin point are the distance of the
                 * cluster from the centre and the angle
                 *
                 *  \param clusters Collection of clusters, each one with the updated measures
                 */
                void analyseClustersOriginDependentValues(std::vector<Cluster> &clusters);

                //! Update the cluster and compute the origin dependent values considering the convex hull
                /*! The values which depend on the origin point are the distance of the
                 * cluster from the centre and the angle
                 *
                 *  \param cluster              Cluster
                 *  \param clusterConvexHull    Convex hull of the cluster
                 */
                void updateClusterOriginDependentValues(Cluster &cluster,
                                                        const std::vector<cv::Point2f> &clusterConvexHull);

                //! Compute the clusteredness index for all the entities detected in the image
                /*! Compute the clusteredness index for all the entities detected in the image using Silhouette
                 *  cluster validity index
                 *
                 *  \param clusters Collection of clusters, each one with the updated measures
                 */
                double computeClusterednessIndex(const std::vector<Cluster> &clusters);

                //! Compute the average pile up degree for all entities in the image
                /*! Compute the average pile up degree for all entities in the image
                 *  as the sum of the average pile up degrees of all clusters divided by
                 *  the number of clusters
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                double computeAveragePileUpDegree(std::vector<Cluster> &clusters);

                //! Get the collection of clusters detected in the image
                std::vector<std::shared_ptr<SpatialEntityPseudo3D>> getCollectionOfSpatialEntityPseudo3D() override;

                //! Convert the value of eps from integer to double
                double convertEpsValue();

                //! Return non-zero value for minPoints
                int getValidMinPointsValue();

            private:

                // Constants
                static const std::string DETECTOR_TYPE;

                static const std::string TRACKBAR_EPS;
                static const std::string TRACKBAR_MINPOINTS;

                static const int MIN_POINTS_MIN;
                static const int MIN_POINTS_MAX;

                static const int EPS_MIN;
                static const int EPS_MAX;
                static const int EPS_REAL_MIN;
                static const int EPS_REAL_MAX;

        };

    };

};


#endif
