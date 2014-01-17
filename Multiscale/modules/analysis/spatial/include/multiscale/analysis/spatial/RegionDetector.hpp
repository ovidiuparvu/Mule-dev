#ifndef REGIONDETECTOR_HPP
#define REGIONDETECTOR_HPP

#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/analysis/spatial/Region.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace pt = boost::property_tree;

using namespace std;
using namespace cv;

const int ENCLOSING_RECT_VERTICES = 4;


namespace multiscale {

    namespace analysis {

        //! Class for detecting regions of high intensity in grayscale images
        class RegionDetector : public Detector {

            private:

                double avgClusterednessDegree;      /*!< Average degree of clusteredness of all regions */
                double avgDensity;                  /*!< Average density of all regions */

                int alpha;                          /*!< Alpha for brightness and contrast adjustments */
                int beta;                           /*!< Beta for brightness and contrast adjustments */
                int blurKernelSize;                 /*!< Kernel size for Gaussian blur */
                int morphologicalCloseIterations;   /*!< Number of iterations for morphological close operator */
                int epsilon;                        /*!< Epsilon for polygon approximation */
                int regionAreaThresh;               /*!< Threshold for considering a region */
                int thresholdValue;                 /*!< Value of the threshold for the threshold filter */

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

                //! Initialisation of the detector specific image dependent values
                void initialiseDetectorSpecificImageDependentFields() override;

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
                void findRegions(const Mat &image, vector<Region> &regions);

                //! Compute the average clusteredness degree and average density
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageMeasures(vector<Region> &regions);

                //! Compute the average clusteredness degree
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageClusterednessDegree(vector<Region> &regions);

                //! Compute the average density
                /*!
                 * \param regions The regions in the image
                 */
                void computeAverageDensity(vector<Region> &regions);

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

                //! Compute the clusteredness degree of the region delimited by the given polygon
                /*!
                 * The density is equal to the average intensity of the pixels in the area
                 * delimited by the given polygon divided by INTENSITY_MAX. The intensities
                 * are considered from the thresholded image where the threshold value is 1
                 * i.e. only the black patches are discarded.
                 *
                 * \param polygon The given polygon
                 */
                double regionClusterednessDegree(const vector<Point> &polygon);

                //! Compute the density of the area delimited by the given polygon
                /*!
                 * The density is equal to the average intensity of the pixels in the area
                 * delimited by the given polygon divided by INTENSITY_MAX.
                 *
                 * \param polygon The given polygon
                 */
                double regionDensity(const vector<Point> &polygon);

                //! Compute the area of the given polygon considering holes
                /*!
                 * \param polygon The given polygon
                 */
                double regionArea(const vector<Point> &polygon);

                //! Compute the area of the white holes in the given matrix
                /*!
                 * \param matrix The given matrix
                 */
                double regionHolesArea(const Mat &matrix);

                //! Clear the element present in the regions vector
                void clearPreviousDetectionResults() override;

                //! Output the regions and averaged measures to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputResultsToCsvFile(ofstream &fout) override;

                //! Output the regions to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputRegionsToCsvFile(ofstream &fout);

                //! Output the averaged measures to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputAveragedMeasuresToCsvFile(ofstream &fout);

                //! Output the regions and averaged measures to an xml file
                /*!
                 * \param filepath Output file path
                 */
                void outputResultsToXMLFile(const string &filepath) override;

                //! Add the regions to the property tree
                /*!
                 * \param propertyTree The property tree
                 */
                void addRegionsToPropertyTree(pt::ptree &propertyTree);

                //! Construct the property tree corresponding to the given region
                /*!
                 * \param region The region to be converted
                 */
                pt::ptree constructPropertyTree(Region &region);

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

            private:

                // Constants
                static const string OUTPUT_CLUSTEREDNESS;
                static const string OUTPUT_DENSITY;

                static const string TRACKBAR_ALPHA;
                static const string TRACKBAR_BETA;
                static const string TRACKBAR_KERNEL;
                static const string TRACKBAR_MORPH;
                static const string TRACKBAR_CANNY;
                static const string TRACKBAR_EPSILON;
                static const string TRACKBAR_REGION_AREA_THRESH;
                static const string TRACKBAR_THRESHOLD;

                static const bool USE_CANNY_L2;
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
                static const int INTENSITY_MAX;

                static const bool POLYGON_CLOSED;

                static const int DISPLAY_LINE_THICKNESS;

        };

    };

};

#endif