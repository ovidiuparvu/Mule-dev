#include "multiscale/analysis/spatial/Detector.hpp"
#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace multiscale::analysis;
using namespace std;


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

void Detector::outputResultsToCsvFile(ofstream &fout) {
    // Output header
    fout << SpatialEntityPseudo3D::fieldNamesToString() << endl;

    outputSpatialEntitiesToCsvFile(fout);

    // Add an empty line between the pseudo 3D spatial entities data and the averaged data
    fout << endl;

    outputAveragedMeasuresToCsvFile(fout);
}

void Detector::outputSpatialEntitiesToCsvFile(ofstream &fout) {
    vector<shared_ptr<SpatialEntityPseudo3D>> spatialEntities = getCollectionOfSpatialEntityPseudo3D();

    for (shared_ptr<SpatialEntityPseudo3D> &spatialEntityPointer : spatialEntities) {
        fout << spatialEntityPointer->toString() << endl;
    }
}

void Detector::outputAveragedMeasuresToCsvFile(ofstream &fout) {
    fout << OUTPUT_CLUSTEREDNESS << avgClusterednessDegree << endl
         << OUTPUT_DENSITY << avgDensity << endl;
}

void Detector::outputResultsToXMLFile() {
    outputResultsToXMLFile(outputFilepath + XML_EXTENSION);
}

void Detector::outputResultsToXMLFile(const string &filepath) {
    pt::ptree propertyTree;

    propertyTree.put<string>(LABEL_COMMENT, LABEL_COMMENT_CONTENTS);

    addSpatialEntitiesToPropertyTree(propertyTree);
    addAverageMeasuresToPropertyTree(propertyTree);

    // Pretty writing of the property tree to the file
    pt::xml_writer_settings<char> settings('\t', 1);

    write_xml(filepath, propertyTree, std::locale(), settings);
}

void Detector::addSpatialEntitiesToPropertyTree(pt::ptree &propertyTree) {
    vector<shared_ptr<SpatialEntityPseudo3D>> spatialEntities = getCollectionOfSpatialEntityPseudo3D();

    for (shared_ptr<SpatialEntityPseudo3D> &spatialEntityPointer : spatialEntities) {
        pt::ptree spatialEntityPropertyTree = constructPropertyTree(*spatialEntityPointer);

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
                                                     const string &name, double value) {
    pt::ptree numericStateVariablePropertyTree;

    numericStateVariablePropertyTree.put<string>(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_NAME, name);
    numericStateVariablePropertyTree.put<double>(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_VALUE, value);

    propertyTree.add_child(LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE, numericStateVariablePropertyTree);
}

pt::ptree Detector::constructPropertyTree(SpatialEntityPseudo3D &spatialEntity) {
    pt::ptree propertyTree;
    pt::ptree pseudo3DpropertyTree;

    addSpatialEntityPropertiesToTree(spatialEntity, pseudo3DpropertyTree);
    addSpatialEntityTypeToPropertyTree(spatialEntity, pseudo3DpropertyTree);

    propertyTree.add_child(LABEL_SPATIAL_ENTITY_PSEUDO_3D, pseudo3DpropertyTree);

    return propertyTree;
}

void Detector::addSpatialEntityPropertiesToTree(SpatialEntityPseudo3D &spatialEntity, pt::ptree &propertyTree) {
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_CLUSTEREDNESS, spatialEntity.getClusterednessDegree());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_DENSITY, spatialEntity.getDensity());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_AREA, spatialEntity.getArea());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_PERIMETER, spatialEntity.getPerimeter());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN, spatialEntity.getDistanceFromOrigin());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_ANGLE, spatialEntity.getAngle());
    propertyTree.put<string>(LABEL_SPATIAL_ENTITY_SHAPE, spatialEntity.getShapeAsString());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE, spatialEntity.getTriangularMeasure());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE, spatialEntity.getRectangularMeasure());
    propertyTree.put<double>(LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE, spatialEntity.getCircularMeasure());
    propertyTree.put<float>(LABEL_SPATIAL_ENTITY_CENTROID_X, spatialEntity.getCentre().x);
    propertyTree.put<float>(LABEL_SPATIAL_ENTITY_CENTROID_Y, spatialEntity.getCentre().y);
}

void Detector::addSpatialEntityTypeToPropertyTree(SpatialEntityPseudo3D &spatialEntity, pt::ptree &propertyTree) {
    pt::ptree attributeTree;

    attributeTree.put<string>(LABEL_SPATIAL_ENTITY_TYPE, spatialEntity.typeAsString());

    propertyTree.add_child(LABEL_ATTRIBUTE, attributeTree);
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
const string Detector::OUTPUT_CLUSTEREDNESS   = "Average clusteredness degree: ";
const string Detector::OUTPUT_DENSITY         = "Average density: ";

const string Detector::ERR_OUTPUT_WITHOUT_DETECT  = "Unable to output results if the detect method was not called previously.";
const string Detector::ERR_OUTPUT_FILE            = "Unable to create output file.";
const string Detector::ERR_INVALID_IMAGE          = "The input image is invalid.";

const string Detector::CSV_EXTENSION    = ".out";
const string Detector::IMG_EXTENSION    = ".png";
const string Detector::XML_EXTENSION    = ".xml";

const string Detector::WIN_OUTPUT_IMAGE    = "Output image";

const int Detector::KEY_ESC     = 27;
const int Detector::KEY_SAVE    = 115;

const string Detector::LABEL_ATTRIBUTE  = "<xmlattr>";
const string Detector::LABEL_COMMENT    = "<xmlcomment>";

const string Detector::LABEL_COMMENT_CONTENTS   = "Warning! This xml file was automatically generated by a C++ program using the Boost PropertyTree library.";

const string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE    = "experiment.timepoint.numericStateVariable";
const string Detector::LABEL_EXPERIMENT_TIMEPOINT_SPATIAL_ENTITY            = "experiment.timepoint.spatialEntity";

const string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_NAME   = "name";
const string Detector::LABEL_EXPERIMENT_TIMEPOINT_NUMERIC_STATE_VARIABLE_VALUE  = "value";

const string Detector::LABEL_SPATIAL_ENTITY_PSEUDO_3D   = "pseudo3D";

const string Detector::LABEL_SPATIAL_ENTITY_TYPE                  = "type";
const string Detector::LABEL_SPATIAL_ENTITY_CLUSTEREDNESS         = "clusteredness";
const string Detector::LABEL_SPATIAL_ENTITY_DENSITY               = "density";
const string Detector::LABEL_SPATIAL_ENTITY_AREA                  = "area";
const string Detector::LABEL_SPATIAL_ENTITY_PERIMETER             = "perimeter";
const string Detector::LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN  = "distanceFromOrigin";
const string Detector::LABEL_SPATIAL_ENTITY_ANGLE                 = "angle";
const string Detector::LABEL_SPATIAL_ENTITY_SHAPE                 = "shape";
const string Detector::LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE      = "triangleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE     = "rectangleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE        = "circleMeasure";
const string Detector::LABEL_SPATIAL_ENTITY_CENTROID_X            = "centroid.x";
const string Detector::LABEL_SPATIAL_ENTITY_CENTROID_Y            = "centroid.y";

const string Detector::LABEL_AVG_CLUSTEREDNESS  = "avgClusteredness";
const string Detector::LABEL_AVG_DENSITY        = "avgDensity";
