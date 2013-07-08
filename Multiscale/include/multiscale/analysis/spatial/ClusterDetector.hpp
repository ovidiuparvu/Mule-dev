#ifndef CLUSTERDETECTOR_HPP_
#define CLUSTERDETECTOR_HPP_

#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/analysis/spatial/Cluster.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define ERR_OUTPUT_FILE         "Unable to create output file."
#define ERR_INVALID_IMAGE       "The input image is invalid."

#define OUTPUT_CLUSTEREDNESS    "Clusteredness index: "
#define OUTPUT_PILE_UP          "Average pile up degree: "

#define OUTPUT_EXTENSION        ".out"
#define IMG_EXTENSION           ".png"

#define MSG_IMG_SAVED           "The image was successfully saved to disk."

#define TRACKBAR_EPS            "Eps (Multiplied by 10)"
#define TRACKBAR_MINPOINTS      "Minimum number of points"

#define MIN_POINTS_MIN          0
#define MIN_POINTS_MAX          100

#define EPS_MIN                 0
#define EPS_MAX                 100000
#define EPS_REAL_MIN            0
#define EPS_REAL_MAX            10000

#define WIN_OUTPUT_IMAGE        "Output image"

#define KEY_ESC     27
#define KEY_SAVE    115


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in 2D images
        class ClusterDetector {

            protected:

                Mat image;                      /*!< Input image */
                string outputFilepath;          /*!< Path of the output file */
                bool debugMode;                 /*!< Flag for indicating if debug mode is set */

                double clusterednessIndex;      /*!< Index of clusteredness for all clusters */
                double avgPileUpDegree;         /*!< Average pile up degree of all clusters */

                int eps;                        /*!< DBSCAN algorithm parameter for specifying the maximum radius
                                                     of the neighbourhood */
                int minPoints;                  /*!< DBSCAN algorithm parameter for specifying the minimum number
                                                     of points in an eps-neighbourhood of that point */

            public:

                ClusterDetector(const Mat &inputImage,
                                const string &outputFilepath,
                                bool debugMode = false);
                virtual ~ClusterDetector();

                //! Detect the clusters in the image and output the results
                void detect();

            protected:

                //! Initialisation function for the class
                void initialise();

                //! Initialise clustering values
                void initialiseClusteringValues();

                //! Check if the image is valid
                /*!
                 * Check if the number of dimensions = 2,  if the
                 * number of rows and number of columns is greater than one
                 * and if the image is of type CV_8UC1
                 */
                bool isValidImage();

                //! Create the trackbars
                void createTrackbars();

                //! Detect the clusters in the provided image
                void detectClusters();

                //! Detect the clusters in the provided image in debug mode
                /*!
                 * \param clusters The clusters from the image
                 */
                void detectClustersInDebugMode(vector<Cluster> &clusters);

                //! Detect the clusters in the provided image in normal mode
                /*!
                 * \param clusters The clusters from the image
                 */
                void detectClustersInNormalMode(vector<Cluster>& clusters);

                //! Find clusters in the provided image
                /*!
                 * \param clusters The clusters from the image
                 */
                void findClusters(vector<Cluster> &clusters);

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

                //! Convert the entities to the required format by the DBSCAN class
                /*!
                 * \param entities Entities detected in the image
                 */
                vector<shared_ptr<DataPoint>> convertEntities(const vector<Entity> &entities);

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
                /*! Compute the clusteredness index for all the entities detected in the image using X index
                 *
                 * TODO: Pick one of the indexes in the literature to compute the value of the clusteredness index
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

                //! Output the information computed for the clusters
                /*! Output the information computed for the clusters considering the state of the debug flag
                 *
                 *  \param clusters Clusters of entities detected in the image
                 *  \param debugMode Flag for indicating if debug mode is set or not
                 */
                void outputClusters(vector<Cluster> &clusters, bool debugMode);

                //! Output the information computed for the clusters visually in a separate window
                /*! Output the information computed for the clusters visually in a separate window
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                virtual void outputClustersInDebugMode(vector<Cluster> &clusters) = 0;

                //! Output the information computed for the clusters in a csv file
                /*! Output the information computed for the clusters in a csv file
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                void outputClustersAsCsvFile(vector<Cluster> &clusters);

                //! Output the information computed for the clusters in a csv file
                /*! Output the information computed for the clusters in a csv file
                 *
                 *  \param clusters Clusters of entities detected in the image
                 *  \param fout     Output file stream
                 */
                void outputClustersAsCsvFile(vector<Cluster> &clusters, ofstream &fout);

                //! Process the request of the user by pressing the key
                /*!
                 * \param pressedKey Key pressed by the user, if a key was pressed, or "-1", otherwise
                 */
                void processPressedKeyRequest(char &pressedKey);

                //! Process the save request in case the lowercase "s" key was pressed
                virtual void processSaveRequest() = 0;

                //! Display an image in a particular window
                /*!
                 * \param image The image
                 * \param windowName The name of the window
                 */
                void displayImage(const Mat &image, const string &windowName);

                //! Convert the value of eps from integer to double
                double convertEpsValue();
        };

    };

};

#endif
