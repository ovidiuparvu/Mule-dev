#ifndef REGIONDETECTOR_HPP_
#define REGIONDETECTOR_HPP_

#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/analysis/spatial/Region.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define TRACKBAR_ALPHA              "Alpha"
#define TRACKBAR_BETA               "Beta"
#define TRACKBAR_KERNEL             "Gaussian blur kernel size"
#define TRACKBAR_MORPH              "Morphological open, number of iterations"
#define TRACKBAR_CANNY              "Canny lower threshold"
#define TRACKBAR_EPSILON            "Epsilon"
#define TRACKBAR_REGION_AREA_THRESH "Region area threshold"
#define TRACKBAR_THRESHOLD          "Threshold value"

#define USE_CANNY_L2            true
#define CONTOUR_AREA_ORIENTED   false

#define ALPHA_REAL_MIN          1.0
#define ALPHA_REAL_MAX          3.0
#define BETA_REAL_MIN           -100
#define BETA_REAL_MAX           100

#define ALPHA_MAX               1000
#define BETA_MAX                200
#define KERNEL_MAX              2000
#define ITER_MAX                100
#define CANNY_THRESH_MAX        100
#define EPSILON_MAX             100
#define REGION_AREA_THRESH_MAX  200000
#define THRESHOLD_MAX           255
#define INTENSITY_MAX           255

#define POLYGON_CLOSED          true

#define DISPLAY_LINE_THICKNESS  10

#define ENCLOSING_RECT_VERTICES 4


namespace multiscale {

    namespace analysis {

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

                Point origin;                       /*!< The point representing the origin */

                vector<Region> regions;             /*!< Regions detected in the image */

            public:

                RegionDetector(bool debugMode = false);
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
                vector<Region> const &getRegions();

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

                //! Initialise the members dependent on the image
                void initialiseImageDependentFields() override;

                //! Create the trackbars
                void createDetectorSpecificTrackbars() override;

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
                void changeContrastAndBrightness(Mat &processedImage);

                //! Smooth out differences in the image
                /*! Apply a Gaussian blur filter
                 *
                 * \param image The image
                 */
                void smoothImage(Mat &image);

                //! Apply the morphological close operator on the image
                /*!
                 * \param image The image
                 */
                void morphologicalClose(Mat &image);

                //! Apply the threshold filter on the image
                /*!
                 * \param image The image
                 * \param thresholdedImage The thresholded image
                 */
                void thresholdImage(const Mat &image, Mat &thresholdedImage);

                //! Find the regions in the image
                /*! Find the contours, approximate the polygons and extract the required
                 * information from them.
                 *
                 * \param image The image
                 * \param regions The regions in the image
                 */
                void findRegions(const Mat &image, vector<Region>& regions);

                //! Find contours in image
                /*!
                 * \param image The image
                 */
                vector<vector<Point> > findContoursInImage(const Mat &image);

                //! Create a new region from the given polygon
                /*! Process the polygon in order to get the required information and
                 *  create a region using this information
                 *
                 * \param polygon Polygon determining the region
                 */
                Region createRegionFromPolygon(const vector<Point> &polygon);

                //! Check if the region is valid
                /*! Check if the area of the region > regionAreaThreshold
                 *
                 * \param polygon The polygon defining the region
                 */
                bool isValidRegion(const vector<Point> &polygon);

                //! Compute the density of the area delimited by the given polygon
                /*!
                 * The density is equal to the average intensity of the pixels in the area
                 * delimited by the given polygon divided by INTENSITY_MAX.
                 *
                 * \param polygon The given polygon
                 */
                double regionDensity(const vector<Point> &polygon);

                //! Compute the angle of the polygon
                /*! Compute the angle determined by the closest point to the origin and the points P1 and P2.
                 * These points are obtained from the intersection of the polygon with the line AB, determined
                 * by points A and B. Points A and B are the middle points of the sides of the rotated rectangle enclosing
                 * the polygon that are orthogonal to the line which is the nearest to the closestPoint.
                 *
                 *  \param polygon Polygon determining the region
                 *  \param closestPointIndex Index of the closest point to the origin from the set of points defining the polygon
                 */
                double regionAngle(const vector<Point> &polygon, unsigned int closestPointIndex);

                //! Compute the angle of the polygon
                /*! Compute the angle determined by the closest point to the origin and the points P1 and P2.
                 * These points are obtained from the intersection of the convex hull with the line AB, determined
                 * by points A and B. Points A and B are the middle points of the sides of the rotated rectangle enclosing
                 * the polygon that are orthogonal to the line which is the nearest to the closestPoint.
                 *
                 *  \param polygonConvexHull Convex hull of polygon determining the region
                 *  \param closestPoint Closest point to the origin from the set of points defining the polygon
                 */
                double regionAngle(const vector<Point> &polygonConvexHull, const Point &closestPoint);

                //! Get the centre of the minimum area bounding rectangle
                /*!
                 * \param polygon The polygon
                 * \param centre The centre of the bounding rectangle
                 */
                void minAreaRectCentre(const vector<Point> &polygon, Point &centre);

                //! Find the points for determining the angle of the region
                /*!
                 *  \param polygonConvexHull Convex hull of polygon determining the region
                 *  \param boundingRectCentre Centre of the rotated rectangle enclosing the polygon convex hull
                 *  \param closestPoint Closest point to the origin from the set of points defining the polygon
                 *  \param goodPointsForAngle The points which are relevant for computing the angle
                 */
                void findGoodPointsForAngle(const vector<Point> &polygonConvexHull, const Point &boundingRectCentre,
                                            const Point &closestPoint, vector<Point> &goodPointsForAngle);

                //! Find good intersection points for computing the angle of the region
                /*!
                 * \param polygonConvexHull The convex hull of the polygon
                 * \param edgePointA Point A on the edge
                 * \param edgePointB Point B on the edge
                 * \param goodPointsForAngle The "good" points for computing the angle
                 */
                void findGoodIntersectionPoints(const vector<Point> &polygonConvexHull, const Point &edgePointA,
                                                const Point &edgePointB, vector<Point> &goodPointsForAngle);

                //! Clear the element present in the regions vector
                void clearPreviousDetectionResults() override;

                //! Output the regions to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputResultsToCsvFile(ofstream &fout) override;

                //! Output the results to the outputImage instance
                void outputResultsToImage() override;

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

        };

    };

};

#endif
