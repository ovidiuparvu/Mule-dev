#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace multiscale::analysis;
using namespace std;


Detector::Detector(bool debugMode) {
    this->debugMode = debugMode;

    this->detectMethodCalled = false;
    this->detectorSpecificFieldsInitialised = false;
}

Detector::~Detector() {
    image.release();
    outputImage.release();
}

void Detector::detect(const Mat &inputImage) {
    if (!isValidInputImage(inputImage)) {
        MS_throw(InvalidInputException, ERR_INVALID_IMAGE);
    }

    inputImage.copyTo(image);

    initialise();
    detect();
}

void Detector::outputResults(const string &outputFilepath) {
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

    origin = Point(originX, originY);
}

bool Detector::isValidInputImage(const Mat &inputImage) {
    return ((inputImage.type() == CV_8UC1) && (inputImage.dims == 2) && (inputImage.rows > 1) && (inputImage.cols > 1));
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

double Detector::polygonAngle(const vector<Point> &polygon, unsigned int closestPointIndex) {
    vector<Point> polygonConvexHull;

    convexHull(polygon, polygonConvexHull);

    return polygonAngle(polygonConvexHull, polygon[closestPointIndex]);
}

double Detector::polygonAngle(const vector<Point> &polygonConvexHull, const Point &closestPoint) {
    Point centre;
    vector<Point> goodPointsForAngle;

    minAreaRectCentre(polygonConvexHull, centre);
    findGoodPointsForAngle(polygonConvexHull, centre, closestPoint, goodPointsForAngle);

    return (goodPointsForAngle.size() == 2) ? Geometry2D::angleBtwPoints(goodPointsForAngle.at(0), closestPoint, goodPointsForAngle.at(1))
                                            : 0;
}

void Detector::minAreaRectCentre(const vector<Point> &polygon, Point &centre) {
    RotatedRect enclosingRectangle = minAreaRect(polygon);

    centre = enclosingRectangle.center;
}

void Detector::findGoodPointsForAngle(const vector<Point> &polygonConvexHull,
                                            const Point &boundingRectCentre,
                                            const Point &closestPoint,
                                            vector<Point> &goodPointsForAngle) {
    Point firstEdgePoint, secondEdgePoint;

    Geometry2D::orthogonalLineToAnotherLineEdgePoints(closestPoint, boundingRectCentre, firstEdgePoint,
                                                      secondEdgePoint, image.rows, image.cols);

    findGoodIntersectionPoints(polygonConvexHull, firstEdgePoint, secondEdgePoint, goodPointsForAngle);
}

void Detector::findGoodIntersectionPoints(const vector<Point> &polygonConvexHull, const Point &edgePointA,
                                                const Point &edgePointB, vector<Point> &goodPointsForAngle) {
    Point intersection;
    int nrOfPolygonPoints = polygonConvexHull.size();

    for (int i = 0; i < nrOfPolygonPoints; i++) {
        if (Geometry2D::lineSegmentIntersection(polygonConvexHull.at(i), polygonConvexHull.at((i+1) % nrOfPolygonPoints),
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
    ofstream fout(outputFilepath + CSV_EXTENSION, ios_base::trunc);

    if (!fout.is_open()) {
        MS_throw(FileOpenException, ERR_OUTPUT_FILE);
    }

    outputResultsToCsvFile(fout);

    fout.close();
}

void Detector::outputResultsToXMLFile() {
    outputResultsToXMLFile(outputFilepath + XML_EXTENSION);
}

void Detector::createTrackbars() {
    createTrackbarsWindow();
    createDetectorSpecificTrackbars();
}

void Detector::createTrackbarsWindow() {
    namedWindow( WIN_OUTPUT_IMAGE, WINDOW_NORMAL);
    setWindowProperty( WIN_OUTPUT_IMAGE, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
}

void Detector::processPressedKeyRequest(char &pressedKey) {
    pressedKey = waitKey(1);

    // Additional processing can be added here in the future
}

void Detector::displayImage(const Mat &image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

void Detector::printOutputErrorMessage() {
    cout << ERR_OUTPUT_WITHOUT_DETECT << endl;
}


// Constants
const string Detector::ERR_OUTPUT_WITHOUT_DETECT  = "Unable to output results if the detect method was not called previously.";
const string Detector::ERR_OUTPUT_FILE            = "Unable to create output file.";
const string Detector::ERR_INVALID_IMAGE          = "The input image is invalid.";

const string Detector::CSV_EXTENSION    = ".out";
const string Detector::IMG_EXTENSION    = ".png";
const string Detector::XML_EXTENSION    = ".xml";

const string Detector::WIN_OUTPUT_IMAGE    = "Output image";

const int Detector::KEY_ESC     = 27;
const int Detector::KEY_SAVE    = 115;

const string Detector::LABEL_COMMENT            = "<xmlcomment>";
const string Detector::LABEL_COMMENT_CONTENTS   = "Warning! This xml file was automatically generated by a C++ program using the Boost PropertyTree library.";

const string Detector::LABEL_EXPERIMENT_TIMEPOINT_SPATIAL_ENTITY    = "experiment.timepoint.spatialEntity";

const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_CLUSTEREDNESS         = "pseudo3D.clusteredness";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_DENSITY               = "pseudo3D.density";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_AREA                  = "pseudo3D.area";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_PERIMETER             = "pseudo3D.perimeter";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_DISTANCE_FROM_ORIGIN  = "pseudo3D.distanceFromOrigin";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_ANGLE_DEGREES         = "pseudo3D.angleDegrees";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_SHAPE                 = "pseudo3D.shape";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_TRIANGLE_MEASURE      = "pseudo3D.triangleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_RECTANGLE_MEASURE     = "pseudo3D.rectangleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_CIRCLE_MEASURE        = "pseudo3D.circleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_CENTROID_X            = "pseudo3D.centroid.x";
const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D_CENTROID_Y            = "pseudo3D.centroid.y";
