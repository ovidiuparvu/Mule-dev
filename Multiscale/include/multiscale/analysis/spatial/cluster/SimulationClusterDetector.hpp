#ifndef SIMULATIONCLUSTERDETECTOR_HPP_
#define SIMULATIONCLUSTERDETECTOR_HPP_

#include "multiscale/analysis/spatial/ClusterDetector.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define THRESHOLD           1
#define THRESHOLD_MAX       255

#define ENTITY_THRESH       200

#define DATAPOINT_WIDTH     3


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in 2D images obtained from simulations
        class SimulationClusterDetector : public ClusterDetector {

            private:

                Mat thresholdedImage;           /*!< Thresholded version of the image */

                unsigned int height;            /*!< Height of the grid used in the simulation */
                unsigned int width;             /*!< Width of the grid used in the simulation */

                unsigned int entityHeight;      /*!< Height of an entity */
                unsigned int entityWidth;       /*!< Width of an entity */

            public:

                SimulationClusterDetector(const Mat &inputImage,
                                          const string &outputFilepath,
                                          unsigned int height,
                                          unsigned int width,
                                          bool debugMode = false
                                          );
                ~SimulationClusterDetector();

            private:

                //! Initialise the thresholdedImage field
                void initialiseThresholdedImage();

                //! Detect the entities in the image
                /*! Detect the entities in the image, compute their centre point and degree of pile up
                 *
                 *  \param entities Entities detected in the image
                 */
                void detectEntitiesInImage(vector<Entity> &entities);

                //! Check if there is an entity in the image at the given position
                /*!
                 * \param x Coordinate for Ox axis
                 * \param y Coordinate for Oy axis
                 */
                bool isEntityAtPosition(int x, int y);

                //! Compute the pile up degree at the given position
                /*!
                 * \param x Coordinate for Ox axis
                 * \param y Coordinate for Oy axis
                 */
                double computePileUpDegreeAtPosition(int x, int y);

                //! Output the information computed for the clusters visually in a separate window
                /*! Output the information computed for the clusters visually in a separate window
                 *
                 *  \param clusters Clusters of entities detected in the image
                 */
                void outputClustersInDebugMode(vector<Cluster> &clusters);

                //! Display cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterInDebugMode(Cluster &cluster, Scalar colour, Mat &image);

                //! Draw the best matching shape (triangular, rectangular, circular) of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterShape(Cluster &cluster, Scalar colour, Mat &image);

                //! Draw the best matching triangular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterTriangularShape(Cluster &cluster, Scalar colour, Mat &image);

                //! Draw the best matching rectangular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterRectangularShape(Cluster &cluster, Scalar colour, Mat &image);

                //! Draw the best matching circular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterCircularShape(Cluster &cluster, Scalar colour, Mat &image);

        };

    };

};

#endif