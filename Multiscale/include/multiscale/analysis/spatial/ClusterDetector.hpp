#ifndef CLUSTERDETECTOR_HPP_
#define CLUSTERDETECTOR_HPP_

#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/analysis/spatial/Cluster.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define ERR_OUTPUT_FILE     "Unable to create output file."
#define ERR_INVALID_IMAGE   "The input image is invalid."

#define OUTPUT_EXTENSION    ".out"

#define WIN_DEBUG_IMAGE     "Debug image"
#define WIN_PROCESSED_IMAGE "Processed image"


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in grayscale images
        class ClusterDetector {

            private:

                Mat inputImage;         /*!< Input image */
                string outputFilepath;  /*!< Path of the output file */
                bool debugMode;         /*!< Flag for indicating if debug mode is set */

            public:

                ClusterDetector(const Mat &inputImage,
                                const string &outputFilepath,
                                bool debugMode = false);
                virtual ~ClusterDetector();

                //! Detect the clusters in the image and output the results
                void detect();

            private:

                //! Detect the entities in the image
                /*! Detect the entities in the image, compute their centre point and degree of pile up
                 *
                 *  \param entities Entities detected in the image
                 */
                virtual void detectEntitiesInImage(vector<Entity> &entities) = 0;

                //! Detect the clusters of entities in the image
                /*! Detect the clusters of entities in the image using Density Based scan (DBscan) clustering algorithm
                 *
                 *  \param entities     Entities detected in the image
                 *  \param clusters     Indexes to which cluster each entity belongs
                 *  \param nrOfClusters Total number of clusters
                 */
                void detectClusters(const vector<Entity> &entities, vector<int> &clusters, int &nrOfClusters);

                //! Analyse the clusters
                /*! Analyse the clusters and compute the values for the measures of interest
                 *
                 *  \param entities     Entities detected in the image
                 *  \param clusters     Indexes to which cluster each entity belongs
                 *  \param nrOfClusters Total number of clusters
                 *  \param clusters     Collection of clusters, each one with the updated measures
                 */
                void analyseClusters(const vector<Entity> &entities, const vector<int> &clusters, int nrOfClusters,
                                     vector<Cluster> clusters);

                //! Compute the clusteredness index for all the entities detected in the image
                /*! Compute the clusteredness index for all the entities detected in the image using X index
                 *
                 * TODO: Pick one of the indexes in the literature to compute the value of the clusteredness index
                 */
                double computeClusterednessIndex();

                //! Compute the average pile up degree for all entities in the image
                /*! Compute the average pile up degree for all entities in the image
                 *  as the sum of the average pile up degrees of all clusters divided by
                 *  the number of clusters
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                double computeAveragePileUpDegree(const vector<Cluster> &clusters);

                //! Output the information computed for the clusters
                /*! Output the information computed for the clusters considering the state of the debug flag
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                void outputClusters(const vector<Cluster> &clusters);

        };

    };

};

#endif
