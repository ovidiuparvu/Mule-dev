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


RegionDetector::RegionDetector(bool debugMode) : Detector(debugMode) {
    avgDensity = 0;
    avgClusterednessDegree = 0;

    alpha = 0;
    beta = 0;
    blurKernelSize = 0;
    morphologicalCloseIterations = 0;
    epsilon = 0;
    regionAreaThresh = 0;
    thresholdValue = 0;
}

RegionDetector::~RegionDetector() {}

int RegionDetector::getAlpha() {
    return alpha;
}

int RegionDetector::getBeta() {
    return beta;
}

int RegionDetector::getBlurKernelSize() {
    return blurKernelSize;
}

int RegionDetector::getMorphologicalCloseIterations() {
    return morphologicalCloseIterations;
}

int RegionDetector::getEpsilon() {
    return epsilon;
}

int RegionDetector::getRegionAreaThresh() {
    return regionAreaThresh;
}

int RegionDetector::getOriginXCoordinate() {
    return origin.x;
}

int RegionDetector::getOriginYCoordinate() {
    return origin.y;
}

int RegionDetector::getThresholdValue() {
    return thresholdValue;
}

vector<Region> const &RegionDetector::getRegions() {
    return regions;
}

void RegionDetector::setAlpha(int alpha) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->alpha = alpha;
}

void RegionDetector::setBeta(int beta) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->beta = beta;
}

void RegionDetector::setBlurKernelSize(int blurKernelSize) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->blurKernelSize = blurKernelSize;
}

void RegionDetector::setEpsilon(int epsilon) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->epsilon = epsilon;
}

void RegionDetector::setMorphologicalCloseIterations(int morphologicalCloseIterations) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->morphologicalCloseIterations = morphologicalCloseIterations;
}

void RegionDetector::setOriginXCoordinate(int originXCoordinate) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->origin.x = originXCoordinate;
}

void RegionDetector::setOriginYCoordinate(int originYCoordinate) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->origin.y = originYCoordinate;
}

void RegionDetector::setRegionAreaThresh(int regionAreaThresh) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->regionAreaThresh = regionAreaThresh;
}

void RegionDetector::setThresholdValue(int thresholdValue) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->thresholdValue = thresholdValue;
}

void RegionDetector::initialiseDetectorSpecificFields() {
    alpha = 750;
    beta = 0;
    blurKernelSize = 15;
    morphologicalCloseIterations = 1;
    epsilon = 1;
    regionAreaThresh = 30000;
    thresholdValue = 100;
}

void RegionDetector::initialiseDetectorSpecificImageDependentFields() {}

void RegionDetector::createDetectorSpecificTrackbars() {
    createTrackbar(TRACKBAR_ALPHA, WIN_OUTPUT_IMAGE, &alpha, ALPHA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_BETA, WIN_OUTPUT_IMAGE, &beta, BETA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_KERNEL, WIN_OUTPUT_IMAGE, &blurKernelSize, KERNEL_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_MORPH, WIN_OUTPUT_IMAGE, &morphologicalCloseIterations, MORPH_ITER_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPSILON, WIN_OUTPUT_IMAGE, &epsilon, EPSILON_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_REGION_AREA_THRESH, WIN_OUTPUT_IMAGE, &regionAreaThresh, REGION_AREA_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_THRESHOLD, WIN_OUTPUT_IMAGE, &thresholdValue, THRESHOLD_MAX, nullptr, nullptr);
}

string RegionDetector::getDetectorTypeAsString() {
    return DETECTOR_TYPE;
}

void RegionDetector::processImageAndDetect() {
    Mat processedImage, thresholdedImage;

    changeContrastAndBrightness(processedImage);
    morphologicalClose(processedImage);
    smoothImage(processedImage);
    thresholdImage(processedImage, thresholdedImage);
    findRegions(thresholdedImage, regions);

    computeAverageMeasures(regions);
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
    vector<Polygon> polygons = findPolygonsInImage(image);

    for (auto polygon : polygons) {
        // Obtain the approximated polygon
        approximatePolygonOuterBorder(polygon);

        // Process and store information about the region
        regions.push_back(createRegionFromPolygon(polygon));
    }
}

void RegionDetector::computeAverageMeasures(vector<Region> &regions) {
    computeAverageClusterednessDegree(regions);
    computeAverageDensity(regions);
}

void RegionDetector::computeAverageClusterednessDegree(vector<Region> &regions) {
    double avgClusterednessDegree = sumOfAverageCentroidDistances(regions);

    // Take the average of the sum of average distances between clusters
    avgClusterednessDegree = (regions.size() != 0) ? avgClusterednessDegree / (regions.size())
                                                   : 0;

    // Invert the value such that it is between 0 and 1. Since we are working with pixels
    // the minimum distance between two distinct pixels is 1.
    if (avgClusterednessDegree != 0) {
        avgClusterednessDegree = (avgClusterednessDegree > 1) ? (1 / avgClusterednessDegree)
                                                              : 1;
    }
}

double RegionDetector::sumOfAverageCentroidDistances(vector<Region> &regions) {
    avgClusterednessDegree = 0;

    for (auto &region: regions) {
        Point2f centroid = region.getCentre();
        double distance = 0;

        for (auto &otherRegion: regions) {
            Point2f otherCentroid = otherRegion.getCentre();

            distance += Geometry2D::distanceBtwPoints(centroid, otherCentroid);
        }

        avgClusterednessDegree += (regions.size() > 1) ? (distance / (regions.size() - 1))
                                                       : 0;
    }

    return avgClusterednessDegree;
}

void RegionDetector::computeAverageDensity(vector<Region> &regions) {
    avgDensity = 0;

    for (auto &region : regions) {
        avgDensity += region.getDensity();
    }

    avgDensity = (regions.size() != 0) ? (avgDensity / regions.size())
                                       : 0;
}

vector<Polygon> RegionDetector::findPolygonsInImage(const Mat &image) {
    // Two extra pixels required for each dimension, because the contour detection
    // algorithm ignores the first and last lines and columns of the image matrix. In order
    // to consider the entire input image we add blank first and last lines and columns
    // to the image matrix
    Mat modifiedImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    image.copyTo(modifiedImage(Rect(1, 1, image.cols, image.rows)));

    findContours(modifiedImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    return createPolygons(contours, hierarchy);
}

vector<Polygon> RegionDetector::createPolygons(const vector<vector<Point> > &contours,
                                               const vector<Vec4i> &hierarchy) {
    vector<Polygon> polygons;

    // Assuming that the algorithm for finding contours is the one proposed by Suzuki85
    // the first contour is always an outer contour
    for (int i = 0; i != -1; i = hierarchy[i][HIERARCHY_NEXT_INDEX]) {
        if (isValidContour(contours[i])) {
            polygons.push_back(createPolygon(i, contours, hierarchy));
        }
    }

    return polygons;
}

Polygon RegionDetector::createPolygon(int contourIndex, const vector<vector<Point> > &contours,
                                      const vector<Vec4i> &hierarchy) {
    Polygon polygon;

    setPolygonOuterContour  (contourIndex, contours, hierarchy, polygon);
    setPolygonInnerContours (contourIndex, contours, hierarchy, polygon);

    return polygon;
}

void RegionDetector::setPolygonOuterContour(int contourIndex, const vector<vector<Point> > &contours,
                                            const vector<Vec4i> &hierarchy, Polygon &polygon) {
    polygon.first = contours[contourIndex];
}

void RegionDetector::setPolygonInnerContours(int contourIndex, const vector<vector<Point> > &contours,
                                             const vector<Vec4i> &hierarchy, Polygon &polygon) {
    int nrOfContours = contours.size();

    for (int i = 0; i < nrOfContours; i++) {
        if ((hierarchy[i][HIERARCHY_PARENT_INDEX] == contourIndex) &&
            (isValidHole(contours[i]))) {
            polygon.second.push_back(contours[i]);
        }
    }
}

void RegionDetector::approximatePolygonOuterBorder(Polygon &polygon) {
    vector<Point> polygonOuterBorder(polygon.first);

    approxPolyDP(polygonOuterBorder, polygon.first, epsilon, true);
}

Region RegionDetector::createRegionFromPolygon(const Polygon &polygon) {
    unsigned int minDistancePointIndex = Geometry2D::minimumDistancePointIndex(polygon.first, origin);

    double density = regionDensity(polygon);
    double distance = Geometry2D::distanceBtwPoints(polygon.first[minDistancePointIndex], origin);
    double angle = polygonAngle(polygon.first, minDistancePointIndex);

    return Region(density, distance, angle, polygon.first, polygon.second);
}

bool RegionDetector::isValidContour(const vector<Point> &contour) {
    double area = contourArea(contour, CONTOUR_AREA_ORIENTED);

    return (area >= regionAreaThresh);
}

bool RegionDetector::isValidHole(const vector<Point> &hole) {
    double area = contourArea(hole, CONTOUR_AREA_ORIENTED);

    return (area >= THRESHOLD_HOLE_AREA);
}

double RegionDetector::regionDensity(const Polygon &polygon) {
    Mat mask(Mat::zeros(image.rows, image.cols, image.type()));

    drawContours(mask, vector<vector<Point>>(1, polygon.first), -1, Scalar(INTENSITY_MAX), CV_FILLED);
    drawContours(mask, polygon.second, -1, Scalar(0), CV_FILLED);

    double averageIntensity = (mean(image, mask))[0];

    return (averageIntensity / static_cast<double>(INTENSITY_MAX));
}

void RegionDetector::clearPreviousDetectionResults() {
    regions.clear();
}

vector<shared_ptr<SpatialEntityPseudo3D>> RegionDetector::getCollectionOfSpatialEntityPseudo3D() {
    vector<shared_ptr<SpatialEntityPseudo3D>> convertedRegions;

    for (Region &region : regions) {
        convertedRegions.push_back(shared_ptr<SpatialEntityPseudo3D>(new Region(region)));
    }

    return convertedRegions;
}

void RegionDetector::outputResultsToImage() {
    // Two extra pixels required for each dimension, because the contour detection
    // algorithm ignores the first and last lines and columns of the image matrix. In order
    // to consider the entire input image we add blank first and last lines and columns
    // to the image matrix
    Mat outputImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());

    image.copyTo(outputImage(Rect(1, 1, image.cols, image.rows)));

    cvtColor(outputImage, outputImage, CV_GRAY2BGR);

    for (Region &region : regions) {
        outputRegionToImage(region, outputImage);
    }

    outputImage(Rect(1, 1, image.cols, image.rows)).copyTo(this->outputImage);
}

void RegionDetector::outputRegionToImage(const Region &region, Mat &outputImage) {
    outputRegionOuterBorderToImage(region.getOuterBorderPolygon(), outputImage);
    outputRegionInnerBordersToImage(region.getInnerBorderPolygons(), outputImage);
}

void RegionDetector::outputRegionOuterBorderToImage(const vector<Point> &outerBorder,
                                                    Mat &outputImage) {
    polylines(outputImage, outerBorder, POLYGON_CLOSED, Scalar(INTENSITY_MAX, 0, 0), DISPLAY_LINE_THICKNESS);
}

void RegionDetector::outputRegionInnerBordersToImage(const vector<vector<Point> > &innerBorders,
                                                     Mat &outputImage) {
    for (auto innerBorder : innerBorders) {
        polylines(outputImage, innerBorder, POLYGON_CLOSED, Scalar(INTENSITY_MAX, 0, 0), DISPLAY_LINE_THICKNESS);
    }
}

double RegionDetector::convertAlpha(int alpha) {
    return NumericRangeManipulator::convertFromRange<int, double>(0, ALPHA_MAX, ALPHA_REAL_MIN, ALPHA_REAL_MAX, alpha);
}

int RegionDetector::convertBeta(int beta) {
    return NumericRangeManipulator::convertFromRange<int, int>(0, BETA_MAX, BETA_REAL_MIN, BETA_REAL_MAX, beta);
}


// Constants
const string RegionDetector::DETECTOR_TYPE  = "Regions";

const string RegionDetector::TRACKBAR_ALPHA              = "Alpha";
const string RegionDetector::TRACKBAR_BETA               = "Beta";
const string RegionDetector::TRACKBAR_KERNEL             = "Gaussian blur kernel size";
const string RegionDetector::TRACKBAR_MORPH              = "Morphological open, number of iterations";
const string RegionDetector::TRACKBAR_CANNY              = "Canny lower threshold";
const string RegionDetector::TRACKBAR_EPSILON            = "Epsilon";
const string RegionDetector::TRACKBAR_REGION_AREA_THRESH = "Region area threshold";
const string RegionDetector::TRACKBAR_THRESHOLD          = "Threshold value";

const int RegionDetector::HIERARCHY_NEXT_INDEX          = 0;
const int RegionDetector::HIERARCHY_PREV_INDEX          = 1;
const int RegionDetector::HIERARCHY_FIRST_CHILD_INDEX   = 2;
const int RegionDetector::HIERARCHY_PARENT_INDEX        = 3;

const bool RegionDetector::USE_CANNY_L2             = true;
const bool RegionDetector::CONTOUR_AREA_ORIENTED    = false;

const double RegionDetector::ALPHA_REAL_MIN = 1.0;
const double RegionDetector::ALPHA_REAL_MAX = 3.0;

const int RegionDetector::BETA_REAL_MIN     = -100;
const int RegionDetector::BETA_REAL_MAX     = 100;

const int RegionDetector::ALPHA_MAX               = 1000;
const int RegionDetector::BETA_MAX                = 200;
const int RegionDetector::KERNEL_MAX              = 2000;
const int RegionDetector::MORPH_ITER_MAX          = 100;
const int RegionDetector::CANNY_THRESH_MAX        = 100;
const int RegionDetector::EPSILON_MAX             = 100;
const int RegionDetector::REGION_AREA_THRESH_MAX  = 200000;
const int RegionDetector::THRESHOLD_MAX           = 255;
const int RegionDetector::THRESHOLD_CLUSTEREDNESS = 0;
const int RegionDetector::INTENSITY_MAX           = 255;

const int RegionDetector::THRESHOLD_HOLE_AREA     = 1000;

const bool RegionDetector::POLYGON_CLOSED         = true;

const int RegionDetector::DISPLAY_LINE_THICKNESS  = 10;
