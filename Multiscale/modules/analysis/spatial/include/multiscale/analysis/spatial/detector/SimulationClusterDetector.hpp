#ifndef SIMULATIONCLUSTERDETECTOR_HPP
#define SIMULATIONCLUSTERDETECTOR_HPP

#include "multiscale/analysis/spatial/detector/ClusterDetector.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for detecting clusters in 2D images obtained from simulations
        class SimulationClusterDetector : public ClusterDetector {

            private:

                cv::Mat thresholdedImage;   /*!< Thresholded version of the image */

                unsigned int height;        /*!< Height of the grid used in the simulation */
                unsigned int width;         /*!< Width of the grid used in the simulation */

                double entityHeight;        /*!< Height of an entity */
                double entityWidth;         /*!< Width of an entity */

            public:

                SimulationClusterDetector(unsigned int height,
                                          unsigned int width,
                                          unsigned int maxPileupNumber,
                                          bool isDebugMode = false);
                ~SimulationClusterDetector();

            private:

                //! Initialise the image dependent values
                void initialiseDetectorSpecificImageDependentFields() override;

                //! Initialise the thresholdedImage field
                void initialiseThresholdedImage();

                //! Detect the entities in the image
                /*! Detect the entities in the image, compute their centre point and degree of pile up
                 *
                 *  \param entities Entities detected in the image
                 */
                void detectEntitiesInImage(std::vector<Entity> &entities) override;

                //! Check if there is an entity in the image at the given position
                /*!
                 * \param x Coordinate for Ox axis
                 * \param y Coordinate for Oy axis
                 */
                bool isEntityAtPosition(int x, int y);

                //! Compute the point representing the centre of the entity
                /*!
                 * \param x Ox coordinate
                 * \param y Oy coordinate
                 */
                cv::Point2f computeEntityCentrePoint(int x, int y);

                //! Compute the points representing the contour of the entity
                /*!
                 * \param x Ox coordinate
                 * \param y Oy coordinate
                 */
                std::vector<cv::Point2f> computeEntityContourPoints(int x, int y);

                //! Compute the pile up degree at the given position
                /*!
                 * \param x Coordinate for Ox axis
                 * \param y Coordinate for Oy axis
                 */
                double computePileUpDegreeAtPosition(int x, int y);

                //! Dsiaply clusters on image
                void outputResultsToImage() override;

                //! Display cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterToImage(Cluster &cluster, cv::Scalar colour, cv::Mat &image);

                //! Draw the best matching shape (triangular, rectangular, circular) of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image);

                //! Draw the best matching triangular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterTriangularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image);

                //! Draw the best matching rectangular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterRectangularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image);

                //! Draw the best matching circular shape of the cluster on the image
                /*!
                 * \param cluster   Cluster
                 * \param colour    Colour associated to all entities in the cluster
                 * \param image     The image on which to display the cluster related information
                 */
                void outputClusterCircularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image);

            private:

                // Constants
                static const int THRESHOLD;
                static const int THRESHOLD_MAX;

                static const int ENTITY_THRESH;

                static const int DATAPOINT_WIDTH;
                static const int DATAPOINT_THICKNESS;

        };

    };

};


#endif
