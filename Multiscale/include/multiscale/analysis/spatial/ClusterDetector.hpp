#ifndef CLUSTERDETECTOR_HPP_
#define CLUSTERDETECTOR_HPP_

#include "multiscale/analysis/spatial/Cluster.hpp"
#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/analysis/spatial/Entity.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define OUTPUT_CLUSTEREDNESS    "Clusteredness index: "
#define OUTPUT_PILE_UP          "Average pile up degree: "

#define TRACKBAR_EPS            "Eps (Multiplied by 10)"
#define TRACKBAR_MINPOINTS      "Minimum number of points"

#define MIN_POINTS_MIN          0
#define MIN_POINTS_MAX          100

#define EPS_MIN                 0
#define EPS_MAX                 10000
#define EPS_REAL_MIN            0
#define EPS_REAL_MAX            1000


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in 2D images
        class ClusterDetector : public Detector {

            protected:

                double clusterednessIndex;      /*!< Index of clusteredness for all clusters */
                double avgPileUpDegree;         /*!< Average pile up degree of all clusters */

                double entityPileupDegree;      /*!< The pile up degree (intensity) of a grid position occupied by only
                                                     one entity*/

                int eps;                        /*!< DBSCAN algorithm parameter for specifying the maximum radius
                                                     of the neighbourhood */
                int minPoints;                  /*!< DBSCAN algorithm parameter for specifying the minimum number
                                                     of points in an eps-neighbourhood of that point */

                vector<Cluster> clusters;       /*!< Clusters found in the image */

            public:

                /*!
                 * \param debugMode             Flag indicating if detector should run in debug mode or not
                 * \param maxPileupNumber       The maximum number of entities which can occupy a grid position at the same time
                 * \param maxPileupIntensity    The grayscale intensity of a maximally piled up grid position
                 */
                ClusterDetector(int maxPileupNumber, double maxPileupIntensity, bool debugMode = false);
                virtual ~ClusterDetector();

                //! Get the value of the clustering algorithm parameter eps
                double getEps();

                //! Get the value of the clustering algorithm parameter MinPoints
                int getMinPoints();

                //! Get a const reference to the vector of detected clusters
                vector<Cluster> const &getClusters();

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

                //! Process the provided image and detect clusters in it
                void processImageAndDetect() override;

                //! Detect the entities in the image
                /*! Detect the entities in the image, compute their centre point and degree of pile up
                 *
                 *  \param entities Entities detected in the image
                 */
                virtual void detectEntitiesInImage(vector<Entity> &entities) = 0;

                //! Detect and analyse the clusters of entities in the image
                /*! Detect and analyse the clusters of entities in the image
                 *
                 *  \param entities     Entities detected in the image
                 *  \param clusters     Clusters of entities detected in the image
                 */
                void detectAndAnalyseClusters(const vector<Entity> &entities, vector<Cluster> &clusters);

                //! Detect the clusters of entities in the image
                /*! Detect the clusters of entities in the image using Density Based scan (DBscan) clustering algorithm
                 *  Clusters start from index 1, because cluster 0 contains only noise data/points.
                 *
                 *  \param entities         Entities detected in the image
                 *  \param clusterIndexes   Indexes to which cluster each entity belongs
                 *  \param nrOfClusters     Total number of clusters
                 */
                void detectClusters(const vector<Entity> &entities, vector<int> &clusterIndexes, int &nrOfClusters);

                //! Convert the entities to the format required by the DBSCAN class
                /*!
                 * \param entities Entities detected in the image
                 */
                vector<shared_ptr<DataPoint>> convertEntities(const vector<Entity> &entities);

                //! Convert the non pile up entities to the format required by the DBSCAN class
                /*!
                 * \param entities Entities detected in the image
                 * \param dataPoints Collection of DataPoint instances required by the DBSCAN class
                 */
                void convertNonPiledUpEntities(const vector<Entity> &entities, vector<shared_ptr<DataPoint> > &dataPoints);

                //! Convert the entities to the required format by the DBSCAN class
                /*!
                 * \param entities Entities detected in the image
                 * \param dataPoints Collection of DataPoint instances required by the DBSCAN class
                 */
                void convertPiledUpEntities(const vector<Entity> &entities, vector<shared_ptr<DataPoint> > &dataPoints);

                //! Add the entities to the clusters as indicated by the clusterIndexes parameter
                /*! Add the entities to the clusters as indicated by the clusterIndexes parameter
                 *
                 *  \param entities         Entities detected in the image
                 *  \param clusterIndexes   Indexes to which cluster each entity belongs
                 *  \param nrOfClusters     Total number of clusters
                 *  \param clusters         Collection of clusters, each one with the updated measures
                 */
                void addEntitiesToClusters(const vector<Entity> &entities, const vector<int> &clusterIndexes, int nrOfClusters,
                                           vector<Cluster> &clusters);

                //! Analyse the clusters
                /*! Analyse the clusters and compute the average clusteredness and pile up degree
                 *
                 *  \param clusters Collection of clusters, each one with the updated measures
                 */
                void analyseClusters(vector<Cluster> &clusters);

                //! Compute the clusteredness index for all the entities detected in the image
                /*! Compute the clusteredness index for all the entities detected in the image using Silhouette cluster validity index
                 *
                 *  \param clusters Collection of clusters, each one with the updated measures
                 */
                double computeClusterednessIndex(const vector<Cluster> &clusters);

                //! Compute the average pile up degree for all entities in the image
                /*! Compute the average pile up degree for all entities in the image
                 *  as the sum of the average pile up degrees of all clusters divided by
                 *  the number of clusters
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                double computeAveragePileUpDegree(vector<Cluster> &clusters);

                //! Output the information computed for the clusters to a csv file
                /*!
                 *  \param fout     Output file stream
                 */
                void outputResultsToCsvFile(ofstream &fout) override;

                //! Convert the value of eps from integer to double
                double convertEpsValue();

                //! Return non-zero value for minPoints
                int getValidMinPointsValue();
        };

    };

};

#endif
