#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/analysis/spatial/RegionDetector.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace multiscale::analysis;


RegionDetector::RegionDetector(const Mat &inputImage, const string &outputFilepath, bool debugMode) {
    inputImage.copyTo(image);

    this->outputFilepath = outputFilepath;
    this->isDebugMode = debugMode;

    initialiseVisionMembers();
}

RegionDetector::~RegionDetector() {
    image.release();
}

void RegionDetector::detect() {
    if (!isValidImage())
        throw ERR_INVALID_IMAGE;

    // Initialise the origin
    initialiseImageDependentMembers();
    detectRegions();
}

void RegionDetector::initialiseVisionMembers() {
    alpha = 750;
    beta = 0;
    blurKernelSize = 15;
    morphologicalCloseIterations = 1;
    epsilon = 1;
    regionAreaThresh = 30000;
    thresholdValue = 100;
}

void RegionDetector::initialiseImageDependentMembers() {
    int originX = (image.rows + 1) / 2;
    int originY = (image.cols + 1) / 2;

    origin = Point(originX, originY);
}

bool RegionDetector::isValidImage() {
    return ((image.dims == 2) && (image.rows > 1) && (image.cols > 1));
}

void RegionDetector::createTrackbars() {
    namedWindow( WIN_PROCESSED_IMAGE, WINDOW_NORMAL);
    setWindowProperty( WIN_PROCESSED_IMAGE, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );

    createTrackbar(TRACKBAR_ALPHA, WIN_PROCESSED_IMAGE, &alpha, ALPHA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_BETA, WIN_PROCESSED_IMAGE, &beta, BETA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_KERNEL, WIN_PROCESSED_IMAGE, &blurKernelSize, KERNEL_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_MORPH, WIN_PROCESSED_IMAGE, &morphologicalCloseIterations, ITER_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPSILON, WIN_PROCESSED_IMAGE, &epsilon, EPSILON_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_REGION_AREA_THRESH, WIN_PROCESSED_IMAGE, &regionAreaThresh, REGION_AREA_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_THRESHOLD, WIN_PROCESSED_IMAGE, &thresholdValue, THRESHOLD_MAX, nullptr, nullptr);
}

void RegionDetector::detectRegions() {
    vector<Region> regions;

    if (isDebugMode) {
        detectRegionsInDebugMode(regions);
    } else {
        detectRegionsInNormalMode(regions);
    }
}

void RegionDetector::detectRegionsInDebugMode(vector<Region> &regions) {
    char pressedKey = -1;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        regions.clear();

        processImage(regions);
        outputRegions(regions, isDebugMode);

        pressedKey = waitKey(1);
    }

    outputRegions(regions, !isDebugMode);
}

void RegionDetector::detectRegionsInNormalMode(vector<Region> &regions) {
    processImage(regions);
    outputRegions(regions, isDebugMode);
}

void RegionDetector::processImage(vector<Region> &regions) {
    Mat processedImage, thresholdedImage;

    changeContrastAndBrightness(processedImage);
    morphologicalClose(processedImage);
    smoothImage(processedImage);
    thresholdImage(processedImage, thresholdedImage);
    findRegions(thresholdedImage, regions);
}

void RegionDetector::changeContrastAndBrightness(Mat &processedImage) {
    image.convertTo(processedImage, -1, convertAlpha(alpha), convertBeta(beta));
}

void RegionDetector::smoothImage(Mat &image) {
    if (blurKernelSize % 2) {
        GaussianBlur(image, image, Size(blurKernelSize, blurKernelSize), 0);
    } else {
        GaussianBlur(image, image, Size(blurKernelSize + 1, blurKernelSize + 1), 0);
    }
}

void RegionDetector::morphologicalClose(Mat &image) {
    if (morphologicalCloseIterations > 0) {
        morphologyEx(image, image, MORPH_CLOSE, Mat(), Point(-1, -1), morphologicalCloseIterations);
    }
}

void RegionDetector::thresholdImage(const Mat &image, Mat &thresholdedImage) {
    threshold(image, thresholdedImage, thresholdValue, THRESHOLD_MAX, THRESH_BINARY);
}

void RegionDetector::findRegions(const Mat &image, vector<Region> &regions) {
    vector<vector<Point> > contours = findContoursInImage(image);

    for (const vector<Point> &contour : contours) {
        if (!isValidRegion(contour))
            continue;

        // Obtain the approximated polygon
        vector<Point> approxPolygon;

        approxPolyDP(contour, approxPolygon, epsilon, true);

        // Process and store information about the region
        regions.push_back(createRegionFromPolygon(approxPolygon));
    }
}

vector<vector<Point> > RegionDetector::findContoursInImage(const Mat &image) {
    // Two extra pixels required for each dimension, because the contour detection
    // algorithm ignores the first and last lines and columns of the image matrix. In order
    // to consider the entire input image we add blank first and last lines and columns
    // to the image matrix
    Mat modifiedImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());
    vector<vector<Point> > contours;

    image.copyTo(modifiedImage(Rect(1, 1, image.cols, image.rows)));

    findContours(modifiedImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    return contours;
}

Region RegionDetector::createRegionFromPolygon(const vector<Point> &polygon) {
    unsigned int minDistancePointIndex = Geometry2D::minimumDistancePointIndex(polygon, origin);

    double area = contourArea(polygon, CONTOUR_AREA_ORIENTED);
    double distance = Geometry2D::distanceBtwPoints(polygon[minDistancePointIndex], origin);
    double angle = regionAngle(polygon, minDistancePointIndex);

    return Region(area, distance, angle, polygon);
}

bool RegionDetector::isValidRegion(const vector<Point> &polygon) {
    double area = contourArea(polygon, CONTOUR_AREA_ORIENTED);

    return (area >= regionAreaThresh);
}

double RegionDetector::regionAngle(const vector<Point> &polygon, unsigned int closestPointIndex) {
    vector<Point> polygonConvexHull;

    convexHull(polygon, polygonConvexHull);

    return regionAngle(polygonConvexHull, polygon[closestPointIndex]);
}

double RegionDetector::regionAngle(const vector<Point> &polygonConvexHull, const Point &closestPoint) {
    Point centre;
    vector<Point> goodPointsForAngle;

    minAreaRectCentre(polygonConvexHull, centre);
    findGoodPointsForAngle(polygonConvexHull, centre, closestPoint, goodPointsForAngle);

    return (goodPointsForAngle.size() == 2) ? Geometry2D::angleBtwPoints(goodPointsForAngle.at(0), closestPoint, goodPointsForAngle.at(1))
                                            : 0;
}

void RegionDetector::minAreaRectCentre(const vector<Point> &polygon, Point &centre) {
    RotatedRect enclosingRectangle = minAreaRect(polygon);

    centre = enclosingRectangle.center;
}

void RegionDetector::findGoodPointsForAngle(const vector<Point> &polygonConvexHull,
                                            const Point &boundingRectCentre,
                                            const Point &closestPoint,
                                            vector<Point> &goodPointsForAngle) {
    Point firstEdgePoint, secondEdgePoint;

    Geometry2D::orthogonalLineToAnotherLineEdgePoints(closestPoint, boundingRectCentre, firstEdgePoint,
                                                      secondEdgePoint, image.rows, image.cols);

    findGoodIntersectionPoints(polygonConvexHull, firstEdgePoint, secondEdgePoint, goodPointsForAngle);
}

void RegionDetector::findGoodIntersectionPoints(const vector<Point> &polygonConvexHull, const Point &edgePointA,
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

void RegionDetector::outputRegions(const vector<Region> &regions, bool isDebugMode) {
    if (isDebugMode) {
        outputRegionsInDebugMode(image, regions);
    } else {
        outputRegionsAsCsvFile(regions);
    }
}

void RegionDetector::outputRegionsAsXMLFile(const vector<Region> &regions) {
    // TODO: Implement
}

void RegionDetector::outputRegionsAsCsvFile(const vector<Region> &regions) {
    ofstream fout(outputFilepath + OUTPUT_EXTENSION, ios_base::trunc);

    if (!fout.is_open())
        throw ERR_OUTPUT_FILE;

    outputRegionsAsCsvFile(regions, fout);

    fout.close();
}

void RegionDetector::outputRegionsAsCsvFile(const vector<Region> &regions, ofstream &fout) {
    // Output header
    fout << Region::fieldNamesToString() << endl;

    if (!regions.empty()) {
        Region firstRegion = regions.front();

        // Output content
        for (auto region : regions) {
            fout << region.toString() << endl;
        }
    }
}

void RegionDetector::outputRegionsInDebugMode(const Mat &image, const vector<Region> &regions) {
    // Two extra pixels required for each dimension, because the contour detection
    // algorithm ignores the first and last lines and columns of the image matrix. In order
    // to consider the entire input image we add blank first and last lines and columns
    // to the image matrix
    Mat outputImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());

    image.copyTo(outputImage(Rect(1, 1, image.cols, image.rows)));

    cvtColor(outputImage, outputImage, CV_GRAY2BGR);

    for (const auto &region : regions) {
        polylines(outputImage, region.getPolygon(), true, Scalar(INTENSITY_MAX, 0, 0), DISPLAY_LINE_THICKNESS);
    }

    displayImage(outputImage(Rect(1, 1, image.cols, image.rows)), WIN_PROCESSED_IMAGE);
}

void RegionDetector::displayImage(const Mat& image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

double RegionDetector::convertAlpha(int alpha) {
    return NumericRangeManipulator::convertFromRange<int, double>(0, ALPHA_MAX, ALPHA_REAL_MIN, ALPHA_REAL_MAX, alpha);
}

int RegionDetector::convertBeta(int beta) {
    return NumericRangeManipulator::convertFromRange<int, int>(0, BETA_MAX, BETA_REAL_MIN, BETA_REAL_MAX, beta);
}

void convertVertices(const Point2f *src, vector<Point> &dst) {
    dst.clear();

    for (int i = 0; i < ENCLOSING_RECT_VERTICES; i++) {
      dst.push_back(src[i]);
    }
}
