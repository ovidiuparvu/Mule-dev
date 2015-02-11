#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include "multiscale/analysis/spatial/model/SpatialEntityPseudo3D.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace analysis {

        //! Abstract class for detecting entities of interest in images
        class Detector {

            protected:

                double avgClusterednessDegree;          /*!< For regions:
                                                             Average degree of clusteredness of all regions

                                                             For clusters:
                                                             Index of clusteredness for all clusters */
                double avgDensity;                      /*!< For regions:
                                                             Average density of all regions

                                                             For clusters:
                                                             Average pile up degree of all clusters */

                cv::Mat image;                          /*!< Input image */
                std::string outputFilepath;             /*!< Path of the output file */

                bool isDebugMode;                       /*!< Flag for indicating if debug mode is set */

                cv::Mat outputImage;                    /*!< Image for displaying the results */

                bool detectMethodCalled;                /*!< Flag for indicating if the detect method was called */
                bool detectorSpecificFieldsInitialised; /*!< Flag for indicating if the parameters were */

                cv::Point2f origin;                     /*!< The point representing the origin */

            public:

                Detector(bool isDebugMode = false);
                virtual ~Detector();

                //! Run the detection procedure on the given image
                /*!
                 * \param inputImage The input image
                 */
                void detect(const cv::Mat &inputImage);

                //! Output the results to the given file
                /*!
                 * \param outputFilepath Path to the output file
                 */
                void outputResults(const std::string &outputFilepath);

            protected:

                //! Initialisation function for the class
                /*!
                 * \param inputImage    The provided input image
                 */
                void initialise(const cv::Mat &inputImage);

                //! Initialise the image field of the class
                /*!
                 * \param inputImage    The provided input image
                 */
                void initialiseImage(const cv::Mat &inputImage);

                //! Initialise the image field of the class as a scaled copy of the given image
                /*!
                 * \param inputImage    The provided input image
                 */
                void initialiseScaledImage(const cv::Mat &inputImage);

                //! Initialisation of the image dependent values
                void initialiseImageDependentFields();

                // Initialisation function for the image origin
                void initialiseImageOrigin();

                //! Initialisation of the detector specific image dependent values
                virtual void initialiseDetectorSpecificImageDependentFields() = 0;

                //! Initialisation of the detector specific values in case they were not set
                void initialiseDetectorSpecificFieldsIfNotSet();

                //! Set the detector specific fields initialisation flag to true
                void setDetectorSpecificFieldsInitialisationFlag(bool flag = true);

                //! Initialisation of the detector specific values
                virtual void initialiseDetectorSpecificFields() = 0;

                //! Check if the image is valid
                /*!
                 * Check if the number of dimensions = 2,  if the
                 * number of rows and number of columns is greater than one
                 * and if the image is of type CV_8UC1
                 *
                 * \param inputImage The input image
                 */
                bool isValidInputImage(const cv::Mat& inputImage);

                //! Get the type of the employed detector as a string
                virtual std::string getDetectorTypeAsString() = 0;

                //! Run the detection procedure
                void detect();

                //! Run the detection procedure when in debug mode
                void detectInDebugMode();

                //! Run the detection procedure when in release mode (i.e. non-debug mode)
                void detectInReleaseMode();

                //! Compute the distance of the given polygon from the origin
                /*!
                 * \param polygon   The considered polygon
                 */
                double computeDistanceFromOrigin(const std::vector<cv::Point> &polygon);

                //! Compute the distance of the given polygon from the origin
                /*!
                 * \param polygon   The considered polygon
                 */
                double computeDistanceFromOrigin(const std::vector<cv::Point2f> &polygon);

                //! Compute the angle determined by the polygon tangents from a given point
                /*! The considered point through which the tangents pass is the image/matrix
                 *  centre point (origin).
                 *
                 *  \param polygon  Polygon for which the angle is computed
                 */
                double computePolygonAngle(const std::vector<cv::Point> &polygon);

                //! Compute the angle determined by the polygon tangents from a given point
                /*! The considered point through which the tangents pass is the image/matrix
                 *  centre point (origin).
                 *
                 *  \param polygon  Polygon for which the angle is computed
                 */
                double computePolygonAngle(const std::vector<cv::Point2f> &polygon);

                //! Compute the angle of the tangents from the provided point to the polygon
                /*!
                 *  \param polygonConvexHull    Convex hull of polygon
                 *  \param tangentsPoint        Point through which the tangents pass
                 */
                double computePolygonAngle(const std::vector<cv::Point2f> &polygonConvexHull,
                                           const cv::Point2f &tangentsPoint);

                //! Display the results in a window
                void displayResultsInWindow();

                //! Output the results to file(s)
                void outputResultsToFile();

                //! Output the results to an image
                virtual void outputResultsToImage() = 0;

                //! Store the image with the output results on disk
                void storeOutputImageOnDisk();

                //! Output the results to a csv file
                void outputResultsToCsvFile();

                //! Output the results to a file using the provided output file stream
                /*!
                 * \param fout Output file stream
                 */
                void outputResultsToCsvFile(std::ofstream &fout);

                //! Output the pseudo 3D spatial entities to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputSpatialEntitiesToCsvFile(std::ofstream &fout);

                //! Output the averaged measures to a csv file
                /*!
                 * \param fout Output file stream
                 */
                void outputAveragedMeasuresToCsvFile(std::ofstream &fout);

                //! Output the results to an xml file
                void outputResultsToXMLFile();

                //! Output the clusters and averaged measures to an xml file
                /*!
                 * \param filepath Output file path
                 */
                void outputResultsToXMLFile(const std::string &filepath);

                //! Add the pseudo 3D spatial entities to the property tree
                /*!
                 * \param propertyTree The property tree
                 */
                void addSpatialEntitiesToPropertyTree(pt::ptree &propertyTree);

                //! Add the average clusteredness and average density to the property tree
                /*!
                 * \param propertyTree The property tree
                 */
                void addAverageMeasuresToPropertyTree(pt::ptree &propertyTree);

                //! Add a numeric state variable to the property tree
                /*!
                 * \param propertyTree  The property tree
                 * \param name          The name of the numeric state variable
                 * \param value         The value of the numeric state variable
                 */
                void addNumericStateVariableToPropertyTree(pt::ptree &propertyTree,
                                                           const std::string &name, double value);

                //! Construct the property tree corresponding to the given spatial entity
                /*!
                 * \param spatialEntity The spatial entity to be converted
                 */
                pt::ptree constructSpatialEntityPropertyTree(SpatialEntityPseudo3D &spatialEntity);

                //! Add the properties of the spatial entity to the property tree
                /*!
                 * \param spatialEntity Spatial entity
                 * \param propertyTree  Property tree
                 */
                void addSpatialEntityPropertiesToTree(SpatialEntityPseudo3D &spatialEntity,
                                                      pt::ptree &propertyTree);

                //! Add the type of the spatial entity to the property tree
                /*!
                 * \param spatialEntity Spatial entity
                 * \param propertyTree  Property tree
                 */
                void addSpatialEntityTypeToPropertyTree(SpatialEntityPseudo3D &spatialEntity,
                                                        pt::ptree &propertyTree);

                //! Get the collection of pseudo 3D entities detected in the image
                virtual std::vector<std::shared_ptr<SpatialEntityPseudo3D>> getCollectionOfSpatialEntityPseudo3D() = 0;

                //! Process the input image and detect objects/entities of interest
                virtual void processImageAndDetect() = 0;

                //! Clear the results from the previous detection
                virtual void clearPreviousDetectionResults() = 0;

                //! Create the trackbars which allow the user to change the values of the parameters
                void createTrackbars();

                //! Create the window in which the trackbars are placed
                void createTrackbarsWindow();

                //! Create the trackbars specific to the used detector
                virtual void createDetectorSpecificTrackbars() = 0;

                //! Process the request of the user by pressing the key
                /*!
                 * \param pressedKey Key pressed by the user, if a key was pressed, or "-1", otherwise
                 */
                void processPressedKeyRequest(char &pressedKey);

                //! Display an image in a particular window
                /*!
                 * \param image The image
                 * \param windowName The name of the window
                 */
                void displayImage(const cv::Mat &image, const std::string &windowName);

                //! Print error message, because the detect method was not called before calling the output method
                void printOutputErrorMessage();

                //! Offset the given collection of polygons by the given point
                /*! The polygon points are offset by adding to their coordinates the
                 *  coordinates of the given point.
                 *
                 * \param polygons  The collection of given polygons
                 * \param offset    The offset point
                 */
                void offsetPolygons(std::vector<std::vector<cv::Point>> &polygons,
                                    const cv::Point &offset);

            protected:

                // Constants
                static const int INTENSITY_MAX;

                static const std::string OUTPUT_CLUSTEREDNESS;
                static const std::string OUTPUT_DENSITY;

                static const std::string ERR_OUTPUT_WITHOUT_DETECT;
                static const std::string ERR_OUTPUT_FILE;
                static const std::string ERR_INVALID_IMAGE;

                static const std::string CSV_EXTENSION;
                static const std::string IMG_EXTENSION;
                static const std::string XML_EXTENSION;

                static const std::string WIN_OUTPUT_IMAGE;

                static const int KEY_ESC;
                static const int KEY_SAVE;

                static const std::string LABEL_ATTRIBUTE;
                static const std::string LABEL_COMMENT;

                static const std::string LABEL_COMMENT_CONTENTS;

                static const std::string LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE;
                static const std::string LABEL_EXPERIMENT_TIMEPOINT_SPATIAL_ENTITY;

                static const std::string LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_NAME;
                static const std::string LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_VALUE;

                static const std::string LABEL_SPATIAL_ENTITY_SPATIAL_TYPE;
                static const std::string LABEL_SPATIAL_ENTITY_CLUSTEREDNESS;
                static const std::string LABEL_SPATIAL_ENTITY_DENSITY;
                static const std::string LABEL_SPATIAL_ENTITY_AREA;
                static const std::string LABEL_SPATIAL_ENTITY_PERIMETER;
                static const std::string LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN;
                static const std::string LABEL_SPATIAL_ENTITY_ANGLE;
                static const std::string LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_CENTROID_X;
                static const std::string LABEL_SPATIAL_ENTITY_CENTROID_Y;

                static const std::string LABEL_AVG_CLUSTEREDNESS;
                static const std::string LABEL_AVG_DENSITY;

        };

    };

};


#endif
