#ifndef REGIONDETECTOR_HPP
#define REGIONDETECTOR_HPP

#include "multiscale/analysis/spatial/detector/Detector.hpp"
#include "multiscale/analysis/spatial/model/Region.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <utility>


namespace multiscale {

    namespace analysis {

        /*! Define a wrapper for polygons i.e. pairs (o, i) where o = outer contour
         *  and i = collection of inner contours/holes
         */
        typedef std::pair<std::vector<cv::Point>, std::vector<std::vector<cv::Point>>> Polygon;


        //! Class for detecting regions of high intensity in grayscale images
        class RegionDetector : public Detector {

            private:

                int alpha;                          /*!< Alpha for brightness and contrast adjustments */
                int beta;                           /*!< Beta for brightness and contrast adjustments */
                int blurKernelSize;                 /*!< Kernel size for Gaussian blur */
                int morphologicalCloseIterations;   /*!< Number of iterations for morphological close operator */
                int epsilon;                        /*!< Epsilon for polygon approximation */
                int regionAreaThresh;               /*!< Threshold for considering a region */
                int thresholdValue;                 /*!< Value of the threshold for the threshold filter */

                std::vector<Region> regions;        /*!< Regions detected in the image */

            public:

                RegionDetector(bool isDebugMode = false);
                ~RegionDetector();

                //! Get the value of field alpha
                int getAlpha();

                //! Get the value of field beta
                int getBeta();

                //! Get the value of field blurKernelSize
                int getBlurKernelSize();

                //! Get the value of field epsilon
                int getEpsilon();

                //! Get the value of field morphologicalCloseIterations
                int getMorphologicalCloseIterations();

                //! Get the value of field originXCoordinate
                int getOriginXCoordinate();

                //! Get the value of field originYCoordinate
                int getOriginYCoordinate();

                //! Get the value of field regionAreaThresh
                int getRegionAreaThresh();

                //! Get the value of field thresholdValue
                int getThresholdValue();

                //! Get a const reference to the vector of detected regions
                std::vector<Region> const &getRegions();

                //! Set the value of field alpha
                /*!
                 * \param alpha Value of alpha
                 */
                void setAlpha(int alpha);

                //! Set the value of field beta
                /*!
                 * \param beta Value of beta
                 */
                void setBeta(int beta);

                //! Set the value of field blurKernelSize
                /*!
                 * \param blurKernelSize Value of blurKernelSize
                 */
                void setBlurKernelSize(int blurKernelSize);

                //! Set the value of field epsilon
                /*!
                 * \param epsilon Value of epsilon
                 */
                void setEpsilon(int epsilon);

                //! Set the value of field morphologicalCloseIterations
                /*!
                 * \param morphologicalCloseIterations Value of morphologicalCloseIterations
                 */
                void setMorphologicalCloseIterations(int morphologicalCloseIterations);

                //! Set the value of field originXCoordinate
                /*!
                 * \param originXCoordinate Value of originXCoordinate
                 */
                void setOriginXCoordinate(int originXCoordinate);

                //! Set the value of field originYCoordinate
                /*!
                 * \param originYCoordinate Value of originYCoordinate
                 */
                void setOriginYCoordinate(int originYCoordinate);

                //! Set the value of field regionAreaThresh
                /*!
                 * \param regionAreaThresh Value of regionAreaThresh
                 */
                void setRegionAreaThresh(int regionAreaThresh);

                //! Set the value of field thresholdValue
                /*!
                 * \param thresholdValue Value of thresholdValue
                 */
                void setThresholdValue(int thresholdValue);

            private:

                //! Initialise the vision members
                void initialiseDetectorSpecificFields() override;

                //! Initialisation of the detector specific image dependent values
                void initialiseDetectorSpecificImageDependentFields() override;

                //! Create the trackbars
                void createDetectorSpecificTrackbars() override;

                //! Get the type of the detector as a string
                std::string getDetectorTypeAsString() override;

                //! Process the given image
                /*! Apply filters to the image, threshold it, find its contours,
                 *  approximate the polygons from these contours. Afterwards, process the polygons
                 *  to find their distance from the origin, their area and the angle determined
                 *  by the points from the contour which are on the edge and the closest point to
                 *  the origin. Return all the polygons together with the processed information
                 *  as a vector of regions.
                 */
                void processImageAndDetect() override;

                //! Change the contrast and brightness of the image
                /*! Change the contrast and brightness of the image by the factors
                 *  alpha and gamma
                 *
                 *  \param processedImage The processed image
                 */
                void changeContrastAndBrightness(cv::Mat &processedImage);

                //! Smooth out differences in the image
                /*! Apply a Gaussian blur filter
                 *
                 * \param image The image
                 */
                void smoothImage(cv::Mat &image);

                //! Apply the morphological close operator on the image
                /*!
                 * \param image The image
                 */
                void morphologicalClose(cv::Mat &image);

                //! Apply the threshold filter on the image
                /*!
                 * \param image The image
                 * \param thresholdedImage The thresholded image
                 */
                void thresholdImage(const cv::Mat &image, cv::Mat &thresholdedImage);

                //! Find the regions in the image
                /*! Find the contours, approximate the polygons and extract the required
                 * information from them.
                 *
                 * \param image The image
                 * \param regions The regions in the image
                 */
                void findRegions(const cv::Mat &image, std::vector<Region> &regions);

                //! Compute the average clusteredness degree and average density
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageMeasures(std::vector<Region> &regions);

                //! Compute the average clusteredness degree
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageClusterednessDegree(std::vector<Region> &regions);

                //! Compute the average distances sum between regions' centroids
                /*!
                 * \param regions The regions in the image
                 */
                double computeSumOfAverageCentroidDistances(std::vector<Region> &regions);

                //! Compute the average distance from the given centroid to all other regions centroids
                /*!
                 * \param centroid  The centroid from which the distance to all other regions' centroids
                 *                  are computed
                 * \param regions   The collection of all regions
                 */
                double computeAverageCentroidDistance(const cv::Point2f &centroid,
                                                      std::vector<Region> &regions);

                //! Compute the average density
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageDensity(std::vector<Region> &regions);

                //! Find polygons in image
                /*!
                 * \param image The image
                 */
                std::vector<Polygon> findPolygonsInImage(const cv::Mat &image);

                //! Create polygons from the given contours and hierarchy information
                /*!
                 * \param contours  The given contours
                 * \param hierarchy The information regarding the hierarchy between contours
                 */
                std::vector<Polygon> createPolygons(const std::vector<std::vector<cv::Point> > &contours,
                                               const std::vector<cv::Vec4i> &hierarchy);

                //! Check if the number of contours is greater than 0
                /*!
                 * \param contours  The given contours
                 */
                bool existContours(const std::vector<std::vector<cv::Point> > &contours);

                //! Create polygons from the given contours and hierarchy information
                /*!
                 * \param contours  The given contours
                 * \param hierarchy The information regarding the hierarchy between contours
                 * \param polygons  The collection of polygons created from the given contours
                 */
                void createPolygonsFromContours(const std::vector<std::vector<cv::Point> > &contours,
                                                const std::vector<cv::Vec4i> &hierarchy,
                                                std::vector<Polygon> &polygons);

                //! Create a new polygon considering the given contour index, contours and hierarchy information
                /*!
                 * \param contourIndex  The index of the outer contour
                 * \param contours      The collection of all contours
                 * \param hierarchy     The information regarding the hierarchy between contours
                 */
                Polygon createPolygon(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                      const std::vector<cv::Vec4i> &hierarchy);

                //! Set the outer contour of the polygon
                /*!
                 * \param contourIndex  The index of the outer contour
                 * \param contours      The collection of all contours
                 * \param hierarchy     The information regarding the hierarchy between contours
                 * \param polygon       The polygon for which the outer contour is set
                 */
                void setPolygonOuterContour(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                            const std::vector<cv::Vec4i> &hierarchy, Polygon &polygon);

                //! Set the inner contours of the polygon
                /*!
                 * \param contourIndex  The index of the outer contour
                 * \param contours      The collection of all contours
                 * \param hierarchy     The information regarding the hierarchy between contours
                 * \param polygon       The polygon for which the outer contour is set
                 */
                void setPolygonInnerContours(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                             const std::vector<cv::Vec4i> &hierarchy, Polygon &polygon);

                //! Approximate the outer contour of the given polygon
                /*!
                 * \param polygon The given polygon
                 */
                void approximatePolygonOuterBorder(Polygon &polygon);

                //! Create a new region from the given polygon
                /*! Process the polygon in order to get the required information
                 *  (e.g. clusteredness, area etc.) and create a region using this
                 *  information
                 *
                 * \param polygon Polygon determining the region
                 */
                Region createRegionFromPolygon(const Polygon &polygon);

                //! Check if the contour is valid
                /*! The contour is valid if its area > regionAreaThreshold
                 *
                 * \param contour The given contour
                 */
                bool isValidContour(const std::vector<cv::Point> &contour);

                //! Check if the hole contained by the outer polygon is valid
                /*! The hole is valid if its area > THRESHOLD_HOLE_AREA
                 *
                 * \param hole          The contour of the hole
                 * \param outerPolygon  The contour of the outer polygon which contains the hole
                 */
                bool isValidHole(const std::vector<cv::Point> &hole,
                                 const std::vector<cv::Point> &outerPolygon);

                //! Compute the density of the area delimited by the given polygon
                /*!
                 * The density is equal to the average intensity of the pixels in the area
                 * delimited by the given polygon divided by INTENSITY_MAX.
                 *
                 * \param polygon The given polygon
                 */
                double computeRegionDensity(const Polygon &polygon);

                //! Create an image mask considering the given outer and inner border polygons
                /*! The value of a mask pixel is maximum if the pixel is contained by the outer and not
                 *  the inner border polygons. Otherwise the value of the mask pixel is minimum.
                 *
                 * \param outerBorderPolygon    The outer border polygon
                 * \param innerBorderPolygons   The collection of inner border polygons
                 */
                cv::Mat createMaskForPolygon(const std::vector<cv::Point> &outerBorderPolygon,
                                             const std::vector<std::vector<cv::Point>> &innerBorderPolygons);

                //! Compute the average intensity of the image considering only the positions specified by the mask
                /*! The type of the image is assumed to be CV_32FC1, respectively of the mask CV_8UC1.
                 *
                 * \param image The provided image
                 * \param mask  The considered mask
                 */
                double computeAverageIntensity(const cv::Mat &image, const cv::Mat &mask);

                //! Clear the element present in the regions vector
                void clearPreviousDetectionResults() override;

                //! Get the collection of clusters detected in the image
                std::vector<std::shared_ptr<SpatialEntityPseudo3D>> getCollectionOfSpatialEntityPseudo3D() override;

                //! Output the results to the outputImage instance
                void outputResultsToImage() override;

                //! Output the region to the outputImage instance
                /*!
                 * \param region        The given region
                 * \param outputImage   The given output image
                 */
                void outputRegionToImage(const Region &region, cv::Mat &outputImage);

                //! Output the outer border polygon of a region to the outputImage instance
                /*!
                 * \param outerBorder   The polygon defining the outer border of the region
                 * \param outputImage   The given output image
                 */
                void outputRegionOuterBorderToImage(const std::vector<cv::Point> &outerBorder,
                                                    cv::Mat &outputImage);

                //! Output the inner border polygons of a region to the outputImage instance
                /*!
                 * \param innerBorders  The polygons defining the inner border(s) of the region
                 * \param outputImage   The given output image
                 */
                void outputRegionInnerBordersToImage(const std::vector<std::vector<cv::Point> > &innerBorders,
                                                     cv::Mat &outputImage);

                //! Convert alpha from the range [0, ALPHA_MAX] to [ALPHA_REAL_MIN, ALPHA_REAL_MAX]
                /*!
                 * \param alpha Alpha
                 */
                double convertAlpha(int alpha);

                //! Convert beta from the range [0, BETA_MAX] to [BETA_REAL_MIN, BETA_REAL_MAX]
                /*!
                 * \param beta Beta
                 */
                int convertBeta(int beta);

            private:

                // Constants
                static const std::string DETECTOR_TYPE;

                static const std::string TRACKBAR_ALPHA;
                static const std::string TRACKBAR_BETA;
                static const std::string TRACKBAR_KERNEL;
                static const std::string TRACKBAR_MORPH;
                static const std::string TRACKBAR_CANNY;
                static const std::string TRACKBAR_EPSILON;
                static const std::string TRACKBAR_REGION_AREA_THRESH;
                static const std::string TRACKBAR_THRESHOLD;

                static const int HIERARCHY_NEXT_INDEX;
                static const int HIERARCHY_PREV_INDEX;
                static const int HIERARCHY_FIRST_CHILD_INDEX;
                static const int HIERARCHY_PARENT_INDEX;

                static const bool CONTOUR_AREA_ORIENTED;

                static const double ALPHA_REAL_MIN;
                static const double ALPHA_REAL_MAX;

                static const int BETA_REAL_MIN;
                static const int BETA_REAL_MAX;

                static const int ALPHA_MAX;
                static const int BETA_MAX;
                static const int KERNEL_MAX;
                static const int MORPH_ITER_MAX;
                static const int CANNY_THRESH_MAX;
                static const int EPSILON_MAX;
                static const int REGION_AREA_THRESH_MAX;
                static const int THRESHOLD_MAX;
                static const int THRESHOLD_CLUSTEREDNESS;

                static const int THRESHOLD_HOLE_AREA;

                static const bool POLYGON_CLOSED;

                static const int DISPLAY_LINE_THICKNESS;

        };

    };

};


#endif
