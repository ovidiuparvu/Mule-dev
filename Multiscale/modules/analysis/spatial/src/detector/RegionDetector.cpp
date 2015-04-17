#include "multiscale/analysis/spatial/detector/RegionDetector.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/analysis/spatial/util/SpatialMeasureCalculator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace multiscale::analysis;


RegionDetector::RegionDetector(bool isDebugMode) : Detector(isDebugMode) {
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

std::vector<Region> const &RegionDetector::getRegions() {
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

void RegionDetector::initializeDetectorSpecificFields() {
    alpha = 750;
    beta = 0;
    blurKernelSize = 15;
    morphologicalCloseIterations = 1;
    epsilon = 1;
    regionAreaThresh = 30000;
    thresholdValue = 100;
}

void RegionDetector::initializeDetectorSpecificImageDependentFields() {}

void RegionDetector::createDetectorSpecificTrackbars() {
    cv::createTrackbar(TRACKBAR_ALPHA, WIN_OUTPUT_IMAGE, &alpha, ALPHA_MAX, nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_BETA, WIN_OUTPUT_IMAGE, &beta, BETA_MAX, nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_KERNEL, WIN_OUTPUT_IMAGE, &blurKernelSize, KERNEL_MAX, nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_MORPH, WIN_OUTPUT_IMAGE, &morphologicalCloseIterations, MORPH_ITER_MAX,
                       nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_EPSILON, WIN_OUTPUT_IMAGE, &epsilon, EPSILON_MAX, nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_REGION_AREA_THRESH, WIN_OUTPUT_IMAGE, &regionAreaThresh, REGION_AREA_THRESH_MAX,
                       nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_THRESHOLD, WIN_OUTPUT_IMAGE, &thresholdValue, THRESHOLD_MAX, nullptr, nullptr);
}

std::string RegionDetector::getDetectorTypeAsString() {
    return DETECTOR_TYPE;
}

void RegionDetector::processImageAndDetect() {
    cv::Mat processedImage, thresholdedImage;

    changeContrastAndBrightness(processedImage);
    morphologicalClose(processedImage);
    smoothImage(processedImage);
    thresholdImage(processedImage, thresholdedImage);
    findRegions(thresholdedImage, regions);

    computeAverageMeasures(regions);
}

void RegionDetector::changeContrastAndBrightness(cv::Mat &processedImage) {
    image.convertTo(processedImage, -1, convertAlpha(alpha), convertBeta(beta));
}

void RegionDetector::smoothImage(cv::Mat &image) {
    if (blurKernelSize % 2) {
        cv::GaussianBlur(image, image, cv::Size(blurKernelSize, blurKernelSize), 0);
    } else {
        cv::GaussianBlur(image, image, cv::Size(blurKernelSize + 1, blurKernelSize + 1), 0);
    }
}

void RegionDetector::morphologicalClose(cv::Mat &image) {
    if (morphologicalCloseIterations > 0) {
        cv::morphologyEx(image, image, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), morphologicalCloseIterations);
    }
}

void RegionDetector::thresholdImage(const cv::Mat &image, cv::Mat &thresholdedImage) {
    cv::Mat tmpThresholdedImage;

    // Threshold the image
    cv::threshold(image, tmpThresholdedImage, thresholdValue, THRESHOLD_MAX, cv::THRESH_BINARY);

    // Convert the resulting thresholded Image to grayscale
    tmpThresholdedImage.convertTo(thresholdedImage, CV_8UC1);
}

void RegionDetector::findRegions(const cv::Mat &image, std::vector<Region> &regions) {
    std::vector<Polygon> polygons = findPolygonsInImage(image);

    for (auto polygon : polygons) {
        // Obtain the approximated polygon
        approximatePolygonOuterBorder(polygon);

        // Process and store information about the region
        regions.push_back(createRegionFromPolygon(polygon));
    }
}

void RegionDetector::computeAverageMeasures(std::vector<Region> &regions) {
    computeAverageClusterednessDegree(regions);
    computeAverageDensity(regions);
}

void RegionDetector::computeAverageClusterednessDegree(std::vector<Region> &regions) {
    avgClusterednessDegree = computeSumOfAverageCentroidDistances(regions);

    // Take the average of the sum of average distances between clusters
    avgClusterednessDegree = Numeric::division(avgClusterednessDegree, regions.size());

    // Invert the value such that it is between 0 and 1. Since we are working with pixels
    // the minimum distance between two distinct pixels is 1.
    avgClusterednessDegree = (avgClusterednessDegree > 1) ? (1 / avgClusterednessDegree)
                                                          : 1;
}

double RegionDetector::computeSumOfAverageCentroidDistances(std::vector<Region> &regions) {
    double sumOfAverageCentroidDistances = 0;

    for (auto &region: regions) {
        sumOfAverageCentroidDistances += computeAverageCentroidDistance(
                                             region.getCentre(),
                                             regions
                                         );
    }

    return sumOfAverageCentroidDistances;
}

double RegionDetector::computeAverageCentroidDistance(const cv::Point2f &centroid,
                                                      std::vector<Region> &regions) {
    double distance = 0;

    // Compute the sum of all centroid distances
    for (auto &region: regions) {
        distance += Geometry2D::distanceBtwPoints(
                        centroid,
                        region.getCentre()
                    );
    }

    // Divide the centroid distances sum by the number of regions
    // excluding the one for which the centroid was passed as a parameter
    return (
        (regions.size() > 1) ? (distance / (regions.size() - 1))
                             : 0
    );
}

void RegionDetector::computeAverageDensity(std::vector<Region> &regions) {
    avgDensity = 0;

    for (auto &region : regions) {
        avgDensity += region.getDensity();
    }

    avgDensity = Numeric::division(avgDensity, regions.size());
}

std::vector<Polygon> RegionDetector::findPolygonsInImage(const cv::Mat &image) {
    // Two extra pixels required for each dimension, because the contour detection
    // algorithm ignores the first and last lines and columns of the image matrix. In order
    // to consider the entire input image we add blank first and last lines and columns
    // to the image matrix
    cv::Mat modifiedImage = cv::Mat::zeros(image.rows + 2, image.cols + 2, image.type());

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    image.copyTo(modifiedImage(cv::Rect(1, 1, image.cols, image.rows)));

    findContours(modifiedImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    // Offset the contours by (-1, -1) in order to account for the extra rows
    // and columns added initially to the image
    offsetPolygons(contours, cv::Point(-1, -1));

    return createPolygons(contours, hierarchy);
}

std::vector<Polygon> RegionDetector::createPolygons(const std::vector<std::vector<cv::Point> > &contours,
                                                    const std::vector<cv::Vec4i> &hierarchy) {
    std::vector<Polygon> polygons;

    if (existContours(contours)) {
        createPolygonsFromContours(contours, hierarchy, polygons);
    }

    return polygons;
}

bool RegionDetector::existContours(const std::vector<std::vector<cv::Point> > &contours) {
    return (!contours.empty());
}

void RegionDetector::createPolygonsFromContours(const std::vector<std::vector<cv::Point> > &contours,
                                                const std::vector<cv::Vec4i> &hierarchy,
                                                std::vector<Polygon> &polygons) {
    // Assuming that the algorithm for finding contours is the one proposed by Suzuki85
    // the first contour is always an outer contour
    for (int i = 0; i != -1; i = hierarchy[i][HIERARCHY_NEXT_INDEX]) {
        if (isValidContour(contours[i])) {
            polygons.push_back(createPolygon(i, contours, hierarchy));
        }
    }
}

Polygon RegionDetector::createPolygon(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                      const std::vector<cv::Vec4i> &hierarchy) {
    Polygon polygon;

    setPolygonOuterContour  (contourIndex, contours, hierarchy, polygon);
    setPolygonInnerContours (contourIndex, contours, hierarchy, polygon);

    return polygon;
}

void RegionDetector::setPolygonOuterContour(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                            const std::vector<cv::Vec4i> &hierarchy, Polygon &polygon) {
    polygon.first = contours[contourIndex];
}

void RegionDetector::setPolygonInnerContours(int contourIndex, const std::vector<std::vector<cv::Point> > &contours,
                                             const std::vector<cv::Vec4i> &hierarchy, Polygon &polygon) {
    int nrOfContours = contours.size();

    for (int i = 0; i < nrOfContours; i++) {
        if ((hierarchy[i][HIERARCHY_PARENT_INDEX] == contourIndex) &&
            (isValidHole(contours[i], contours[contourIndex]))) {
            polygon.second.push_back(contours[i]);
        }
    }
}

void RegionDetector::approximatePolygonOuterBorder(Polygon &polygon) {
    std::vector<cv::Point> polygonOuterBorder(polygon.first);

    approxPolyDP(polygonOuterBorder, polygon.first, epsilon, true);
}

Region RegionDetector::createRegionFromPolygon(const Polygon &polygon) {
    double density  = computeRegionDensity(polygon);
    double distance = computeDistanceFromOrigin(polygon.first);
    double angle    = computePolygonAngle(polygon.first);

    return (
        Region(
            density,
            distance,
            angle,
            polygon.first,
            polygon.second
        )
    );
}

bool RegionDetector::isValidContour(const std::vector<cv::Point> &contour) {
    double area = SpatialMeasureCalculator::computePolygonArea(contour);

    return (area > regionAreaThresh);
}

bool RegionDetector::isValidHole(const std::vector<cv::Point> &hole,
                                 const std::vector<cv::Point> &outerPolygon) {
    double area = SpatialMeasureCalculator::computePolygonHoleArea(hole, outerPolygon);

    return (area > THRESHOLD_HOLE_AREA);
}

double RegionDetector::computeRegionDensity(const Polygon &polygon) {
    cv::Mat mask = createMaskForPolygon(polygon.first, polygon.second);

    // Compute the average intensity of the pixels considering the mask
    double averageIntensity = computeAverageIntensity(image, mask);

    // Normalise the density such that its value is in [0, 1]
    return (
        Numeric::division(
            averageIntensity,
            static_cast<double>(INTENSITY_MAX)
        )
    );
}

cv::Mat RegionDetector::createMaskForPolygon(const std::vector<cv::Point> &outerBorderPolygon,
                                             const std::vector<std::vector<cv::Point>> &innerBorderPolygons) {
    // Create a blank mask where each pixel is initialized with zero intensity
    cv::Mat mask(cv::Mat::zeros(image.rows, image.cols, CV_8UC1));

    // Set the intensity of all pixels surrounded by the polygon outer border to maximum
    drawContours(
        mask, std::vector<std::vector<cv::Point>>(1, outerBorderPolygon), -1,
        cv::Scalar(INTENSITY_MAX), CV_FILLED
    );

    // Set the intensity of all pixels surrounded by inner borders to zero
    drawContours(
        mask, innerBorderPolygons, -1, cv::Scalar(0), CV_FILLED
    );

    // Set the intensity of all pixels defined by the polygon outer border to maximum.
    // The reason for adding this step is that some of the pixels may have been
    // assigned zero intensity in the previous step because they are common to both
    // outer and inner borders
    drawContours(
        mask, std::vector<std::vector<cv::Point>>(1, outerBorderPolygon), -1,
        cv::Scalar(INTENSITY_MAX), 1
    );

    return mask;
}

double RegionDetector::computeAverageIntensity(const cv::Mat &image, const cv::Mat &mask) {
    std::vector<double> consideredIntensityValues;

    // Collect the considered intensity values
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (mask.at<uchar>(i, j) == INTENSITY_MAX) {
                consideredIntensityValues.push_back(
                    static_cast<double>(image.at<float>(i, j))
                );
            }
        }
    }

    return (
        Numeric::average(
            consideredIntensityValues
        )
    );
}

void RegionDetector::clearPreviousDetectionResults() {
    regions.clear();
}

std::vector<std::shared_ptr<SpatialEntityPseudo3D>> RegionDetector::getCollectionOfSpatialEntityPseudo3D() {
    std::vector<std::shared_ptr<SpatialEntityPseudo3D>> convertedRegions;

    for (Region &region : regions) {
        convertedRegions.push_back(std::shared_ptr<SpatialEntityPseudo3D>(new Region(region)));
    }

    return convertedRegions;
}

void RegionDetector::outputResultsToImage() {
    // Convert the floating point initial image to a unsigned char output image
    image.convertTo(outputImage, CV_8UC1);

    // Convert the temporary grayscale output image to coloured
    cvtColor(outputImage, outputImage, CV_GRAY2BGR);

    // Output the regions to the image
    for (Region &region : regions) {
        outputRegionToImage(region, outputImage);
    }
}

void RegionDetector::outputRegionToImage(const Region &region, cv::Mat &outputImage) {
    outputRegionOuterBorderToImage(region.getOuterBorderPolygon(), outputImage);
    outputRegionInnerBordersToImage(region.getInnerBorderPolygons(), outputImage);
}

void RegionDetector::outputRegionOuterBorderToImage(const std::vector<cv::Point> &outerBorder,
                                                    cv::Mat &outputImage) {
    polylines(outputImage, outerBorder, POLYGON_CLOSED,
              cv::Scalar(INTENSITY_MAX, 0, 0), DISPLAY_LINE_THICKNESS);
}

void RegionDetector::outputRegionInnerBordersToImage(const std::vector<std::vector<cv::Point> > &innerBorders,
                                                     cv::Mat &outputImage) {
    for (auto innerBorder : innerBorders) {
        polylines(outputImage, innerBorder, POLYGON_CLOSED,
                  cv::Scalar(INTENSITY_MAX, 0, 0), DISPLAY_LINE_THICKNESS);
    }
}

double RegionDetector::convertAlpha(int alpha) {
    return (
        NumericRangeManipulator::convertFromRange<int, double>(
            0, ALPHA_MAX, ALPHA_REAL_MIN, ALPHA_REAL_MAX, alpha
        )
    );
}

int RegionDetector::convertBeta(int beta) {
    return (
        NumericRangeManipulator::convertFromRange<int, int>(
            0, BETA_MAX, BETA_REAL_MIN, BETA_REAL_MAX, beta
        )
    );
}


// Constants
const std::string RegionDetector::DETECTOR_TYPE  = "Regions";

const std::string RegionDetector::TRACKBAR_ALPHA              = "Alpha";
const std::string RegionDetector::TRACKBAR_BETA               = "Beta";
const std::string RegionDetector::TRACKBAR_KERNEL             = "Gaussian blur kernel size";
const std::string RegionDetector::TRACKBAR_MORPH              = "Morphological open, number of iterations";
const std::string RegionDetector::TRACKBAR_CANNY              = "Canny lower threshold";
const std::string RegionDetector::TRACKBAR_EPSILON            = "Epsilon";
const std::string RegionDetector::TRACKBAR_REGION_AREA_THRESH = "Region area threshold";
const std::string RegionDetector::TRACKBAR_THRESHOLD          = "Threshold value";

const int RegionDetector::HIERARCHY_NEXT_INDEX          = 0;
const int RegionDetector::HIERARCHY_PREV_INDEX          = 1;
const int RegionDetector::HIERARCHY_FIRST_CHILD_INDEX   = 2;
const int RegionDetector::HIERARCHY_PARENT_INDEX        = 3;

const bool RegionDetector::CONTOUR_AREA_ORIENTED = false;

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

const int RegionDetector::THRESHOLD_HOLE_AREA     = 0;

const bool RegionDetector::POLYGON_CLOSED         = true;

const int RegionDetector::DISPLAY_LINE_THICKNESS  = 1;
