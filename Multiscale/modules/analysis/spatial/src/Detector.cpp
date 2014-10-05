#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace multiscale::analysis;


Detector::Detector(bool debugMode) {
    this->debugMode = debugMode;

    this->avgDensity = 0.0;
    this->avgClusterednessDegree = 0.0;

    this->detectMethodCalled = false;
    this->detectorSpecificFieldsInitialised = false;
}

Detector::~Detector() {
    image.release();
    outputImage.release();
}

void Detector::detect(const cv::Mat &inputImage) {
    if (!isValidInputImage(inputImage)) {
        MS_throw(InvalidInputException, ERR_INVALID_IMAGE);
    }

    inputImage.copyTo(image);

    initialise();
    detect();
}

void Detector::outputResults(const std::string &outputFilepath) {
    if (detectMethodCalled) {
        this->outputFilepath = outputFilepath;

        outputResultsToFile();
    } else {
        printOutputErrorMessage();
    }
}

void Detector::initialise() {
    initialiseImageDependentFields();
    initialiseDetectorSpecificFieldsIfNotSet();
}

void Detector::initialiseDetectorSpecificFieldsIfNotSet() {
    if (!detectorSpecificFieldsInitialised) {
        initialiseDetectorSpecificFields();

        detectorSpecificFieldsInitialised = true;
    }
}

void Detector::setDetectorSpecificFieldsInitialisationFlag(bool flag) {
    detectorSpecificFieldsInitialised = flag;
}

void Detector::initialiseImageDependentFields() {
    initialiseImageOrigin();
    initialiseDetectorSpecificImageDependentFields();
}

void Detector::initialiseImageOrigin() {
    int originX = (image.rows + 1) / 2;
    int originY = (image.cols + 1) / 2;

    origin = cv::Point(originX, originY);
}

bool Detector::isValidInputImage(const cv::Mat &inputImage) {
    return (
        (inputImage.type() == CV_8UC1) &&
        (inputImage.dims == 2) &&
        (inputImage.rows > 1) &&
        (inputImage.cols > 1)
    );
}

void Detector::detect() {
    detectMethodCalled = true;

    if (debugMode) {
        detectInDebugMode();
    } else {
        detectInReleaseMode();
    }
}

void Detector::detectInDebugMode() {
    char pressedKey = -1;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        clearPreviousDetectionResults();

        processImageAndDetect();
        displayResultsInWindow();

        processPressedKeyRequest(pressedKey);
    }
}

void Detector::detectInReleaseMode() {
    clearPreviousDetectionResults();
    processImageAndDetect();
}

double Detector::polygonAngle(const std::vector<cv::Point> &polygon, unsigned int closestPointIndex) {
    std::vector<cv::Point> polygonConvexHull;

    convexHull(polygon, polygonConvexHull);

    return polygonAngle(polygonConvexHull, polygon[closestPointIndex]);
}

double Detector::polygonAngle(const std::vector<cv::Point> &polygonConvexHull, const cv::Point &closestPoint) {
    cv::Point centre;
    std::vector<cv::Point> goodPointsForAngle;

    minAreaRectCentre(polygonConvexHull, centre);
    findGoodPointsForAngle(polygonConvexHull, centre, closestPoint, goodPointsForAngle);

    return (
        (goodPointsForAngle.size() == 2)
            ? Geometry2D::angleBtwPoints(goodPointsForAngle.at(0), closestPoint, goodPointsForAngle.at(1))
            : 0
    );
}

void Detector::minAreaRectCentre(const std::vector<cv::Point> &polygon, cv::Point &centre) {
    cv::RotatedRect enclosingRectangle = minAreaRect(polygon);

    centre = enclosingRectangle.center;
}

void Detector::findGoodPointsForAngle(const std::vector<cv::Point> &polygonConvexHull,
                                      const cv::Point &boundingRectCentre,
                                      const cv::Point &closestPoint,
                                      std::vector<cv::Point> &goodPointsForAngle) {
    cv::Point firstEdgePoint, secondEdgePoint;

    Geometry2D::orthogonalLineToAnotherLineEdgePoints(closestPoint, boundingRectCentre, firstEdgePoint,
                                                      secondEdgePoint, image.rows, image.cols);

    findGoodIntersectionPoints(polygonConvexHull, firstEdgePoint, secondEdgePoint, goodPointsForAngle);
}

void Detector::findGoodIntersectionPoints(const std::vector<cv::Point> &polygonConvexHull,
                                          const cv::Point &edgePointA,
                                          const cv::Point &edgePointB,
                                          std::vector<cv::Point> &goodPointsForAngle) {
    cv::Point intersection;
    int nrOfPolygonPoints = polygonConvexHull.size();

    for (int i = 0; i < nrOfPolygonPoints; i++) {
        if (Geometry2D::lineSegmentIntersection(polygonConvexHull.at(i),
                                                polygonConvexHull.at((i+1) % nrOfPolygonPoints),
                                                edgePointA, edgePointB, intersection)) {
            goodPointsForAngle.push_back(intersection);
        }
    }
}

void Detector::displayResultsInWindow() {
    outputResultsToImage();
    displayImage(outputImage, WIN_OUTPUT_IMAGE);
}

void Detector::outputResultsToFile() {
    outputResultsToCsvFile();
    outputResultsToXMLFile();

    outputResultsToImage();
    storeOutputImageOnDisk();
}

void Detector::storeOutputImageOnDisk() {
    if (outputImage.data) {
        imwrite(outputFilepath + IMG_EXTENSION, outputImage);
    }
}

void Detector::outputResultsToCsvFile() {
    std::ofstream fout(outputFilepath + CSV_EXTENSION, std::ios_base::trunc);

    if (!fout.is_open()) {
        MS_throw(FileOpenException, ERR_OUTPUT_FILE);
    }

    outputResultsToCsvFile(fout);

    fout.close();
}

void Detector::outputResultsToCsvFile(std::ofstream &fout) {
    // Output header
    fout << SpatialEntityPseudo3D::fieldNamesToString() << std::endl;

    outputSpatialEntitiesToCsvFile(fout);

    // Add an empty cv::line between the pseudo 3D spatial entities data and the averaged data
    fout << std::endl;

    outputAveragedMeasuresToCsvFile(fout);
}

void Detector::outputSpatialEntitiesToCsvFile(std::ofstream &fout) {
    std::vector<std::shared_ptr<SpatialEntityPseudo3D>> spatialEntities = getCollectionOfSpatialEntityPseudo3D();

    for (std::shared_ptr<SpatialEntityPseudo3D> &spatialEntityPointer : spatialEntities) {
        fout << spatialEntityPointer->toString() << std::endl;
    }
}

void Detector::outputAveragedMeasuresToCsvFile(std::ofstream &fout) {
    fout << OUTPUT_CLUSTEREDNESS << avgClusterednessDegree << std::endl
         << OUTPUT_DENSITY << avgDensity << std::endl;
}

void Detector::outputResultsToXMLFile() {
    outputResultsToXMLFile(outputFilepath + XML_EXTENSION);
}

void Detector::outputResultsToXMLFile(const std::string &filepath) {
    pt::ptree propertyTree;

    propertyTree.put<std::string>(LABEL_COMMENT, LABEL_COMMENT_CONTENTS);

    addSpatialEntitiesToPropertyTree(propertyTree);
    addAverageMeasuresToPropertyTree(propertyTree);

    // Pretty writing of the property tree to the file
    pt::xml_writer_settings<char> settings('\t', 1);

    write_xml(filepath, propertyTree, std::locale(), settings);
}

void Detector::addSpatialEntitiesToPropertyTree(pt::ptree &propertyTree) {
    std::vector<std::shared_ptr<SpatialEntityPseudo3D>> spatialEntities = getCollectionOfSpatialEntityPseudo3D();

    for (std::shared_ptr<SpatialEntityPseudo3D> &spatialEntityPointer : spatialEntities) {
        pt::ptree spatialEntityPropertyTree = constructSpatialEntityPropertyTree(*spatialEntityPointer);

        propertyTree.add_child(LABEL_EXPERIMENT_TIMEPOINT_SPATIAL_ENTITY, spatialEntityPropertyTree);
    }
}

void Detector::addAverageMeasuresToPropertyTree(pt::ptree &propertyTree) {
    addNumericStateVariableToPropertyTree(
        propertyTree, LABEL_AVG_CLUSTEREDNESS + getDetectorTypeAsString(), avgClusterednessDegree
    );
    addNumericStateVariableToPropertyTree(
        propertyTree, LABEL_AVG_DENSITY + getDetectorTypeAsString(), avgDensity
    );
}

void Detector::addNumericStateVariableToPropertyTree(pt::ptree &propertyTree,
                                                     const std::string &name, double value) {
    pt::ptree numericStateVariablePropertyTree;

    numericStateVariablePropertyTree.put<std::string>(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_NAME, name);
    numericStateVariablePropertyTree.put<double>(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_VALUE, value);

    propertyTree.add_child(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE, numericStateVariablePropertyTree);
}

pt::ptree Detector::constructSpatialEntityPropertyTree(SpatialEntityPseudo3D &spatialEntity) {
    pt::ptree spatialEntityTree;

    addSpatialEntityPropertiesToTree(spatialEntity, spatialEntityTree);
    addSpatialEntityTypeToPropertyTree(spatialEntity, spatialEntityTree);

    return spatialEntityTree;
}

void Detector::addSpatialEntityPropertiesToTree(SpatialEntityPseudo3D &spatialEntity, pt::ptree &propertyTree) {
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_CLUSTEREDNESS, spatialEntity.getClusterednessDegree());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_DENSITY, spatialEntity.getDensity());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_AREA, spatialEntity.getArea());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_PERIMETER, spatialEntity.getPerimeter());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN, spatialEntity.getDistanceFromOrigin());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_ANGLE, spatialEntity.getAngle());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE, spatialEntity.getTriangularMeasure());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE, spatialEntity.getRectangularMeasure());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE, spatialEntity.getCircularMeasure());
    propertyTree.put<float>(LABEL_SPATIAL_ENTITY_CENTROID_X, spatialEntity.getCentre().x);
    propertyTree.put<float>(LABEL_SPATIAL_ENTITY_CENTROID_Y, spatialEntity.getCentre().y);
}

void Detector::addSpatialEntityTypeToPropertyTree(SpatialEntityPseudo3D &spatialEntity,
                                                  pt::ptree &propertyTree) {
    pt::ptree attributeTree;

    attributeTree.put<std::string>(LABEL_SPATIAL_ENTITY_SPATIAL_TYPE, spatialEntity.typeAsString());

    propertyTree.add_child(LABEL_ATTRIBUTE, attributeTree);
}

void Detector::createTrackbars() {
    createTrackbarsWindow();
    createDetectorSpecificTrackbars();
}

void Detector::createTrackbarsWindow() {
    cv::namedWindow( WIN_OUTPUT_IMAGE, cv::WINDOW_NORMAL);
    cv::setWindowProperty( WIN_OUTPUT_IMAGE, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
}

void Detector::processPressedKeyRequest(char &pressedKey) {
    pressedKey = cv::waitKey(1);

    // Additional processing can be added here in the future
}

void Detector::displayImage(const cv::Mat &image, const std::string &windowName) {
    cv::namedWindow( windowName, cv::WINDOW_NORMAL );
    cv::imshow( windowName, image );
}

void Detector::printOutputErrorMessage() {
    std::cout << ERR_OUTPUT_WITHOUT_DETECT << std::endl;
}


// Constants
const std::string Detector::OUTPUT_CLUSTEREDNESS   = "Average clusteredness degree: ";
const std::string Detector::OUTPUT_DENSITY         = "Average density: ";

const std::string Detector::ERR_OUTPUT_WITHOUT_DETECT  = "Unable to output results if the detect method was not called previously.";
const std::string Detector::ERR_OUTPUT_FILE            = "Unable to create output file.";
const std::string Detector::ERR_INVALID_IMAGE          = "The input image is invalid.";

const std::string Detector::CSV_EXTENSION    = ".out";
const std::string Detector::IMG_EXTENSION    = ".png";
const std::string Detector::XML_EXTENSION    = ".xml";

const std::string Detector::WIN_OUTPUT_IMAGE    = "Output image";

const int Detector::KEY_ESC     = 27;
const int Detector::KEY_SAVE    = 115;

const std::string Detector::LABEL_ATTRIBUTE  = "<xmlattr>";
const std::string Detector::LABEL_COMMENT    = "<xmlcomment>";

const std::string Detector::LABEL_COMMENT_CONTENTS   = "Warning! This xml file was automatically generated by a C++ program using the Boost PropertyTree library.";

const std::string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE    = "experiment.timepoint.numericStateVariable";
const std::string Detector::LABEL_EXPERIMENT_TIMEPOINT_SPATIAL_ENTITY            = "experiment.timepoint.spatialEntity";

const std::string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_NAME   = "name";
const std::string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_VALUE  = "value";

const std::string Detector::LABEL_SPATIAL_ENTITY_SPATIAL_TYPE          = "spatialType";
const std::string Detector::LABEL_SPATIAL_ENTITY_CLUSTEREDNESS         = "clusteredness";
const std::string Detector::LABEL_SPATIAL_ENTITY_DENSITY               = "density";
const std::string Detector::LABEL_SPATIAL_ENTITY_AREA                  = "area";
const std::string Detector::LABEL_SPATIAL_ENTITY_PERIMETER             = "perimeter";
const std::string Detector::LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN  = "distanceFromOrigin";
const std::string Detector::LABEL_SPATIAL_ENTITY_ANGLE                 = "angle";
const std::string Detector::LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE      = "triangleMeasure";
const std::string Detector::LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE     = "rectangleMeasure";
const std::string Detector::LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE        = "circleMeasure";
const std::string Detector::LABEL_SPATIAL_ENTITY_CENTROID_X            = "centroidX";
const std::string Detector::LABEL_SPATIAL_ENTITY_CENTROID_Y            = "centroidY";

const std::string Detector::LABEL_AVG_CLUSTEREDNESS  = "avgClusteredness";
const std::string Detector::LABEL_AVG_DENSITY        = "avgDensity";
