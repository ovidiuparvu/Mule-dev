#include "multiscale/analysis/spatial/util/SpatialMeasureCalculator.hpp"

#include "opencv2/imgproc/imgproc.hpp"

using namespace multiscale::analysis;


int SpatialMeasureCalculator::computePolygonArea(const std::vector<cv::Point> &polygon) {
    cv::Mat polygonImage = drawFilledPolygonOnImage(polygon);

    // Return the number of pixels covered by the polygon
    return (
        cv::countNonZero(polygonImage)
    );
}

int SpatialMeasureCalculator::computePolygonHoleArea(const std::vector<cv::Point> &hole,
                                                     const std::vector<cv::Point> &polygon) {
    cv::Mat holeImage = drawFilledPolygonOnImage(hole);

    // Set the pixels which are common to the polygon and the
    // hole to the minimum value
    subtractPolygonBorderFromImage(polygon, holeImage);

    // Return the number of pixels covered by the hole
    // and not contained by the polygon border
    return (
        cv::countNonZero(holeImage)
    );
}

int SpatialMeasureCalculator::computeCircleArea(const cv::Point2f &circleOrigin, double circleRadius) {
    // The circle radius has to be converted to a
    cv::Mat circleImage = drawFilledCircleOnImage(circleOrigin, circleRadius);

    // Return the number of pixels covered by the circle
    return (
        cv::countNonZero(circleImage)
    );
}

int SpatialMeasureCalculator::computePolygonPerimeter(const std::vector<cv::Point> &polygon) {
    cv::Mat polygonImage = drawFilledPolygonOnImage(polygon);

    // Compute the number of exterior polygon sides in the matrix
    int nrOfPolygonExteriorSides = 0;

    for (int i = 0; i < polygonImage.rows; i++) {
        for (int j = 0; j < polygonImage.cols; j++) {
            // If the pixel is white
            if (polygonImage.at<uchar>(i, j) == POINT_MAX_VALUE) {
                nrOfPolygonExteriorSides +=
                    computeNrOfMinValuePointSides(i, j, polygonImage);
            }
        }
    }

    return nrOfPolygonExteriorSides;
}

cv::Mat SpatialMeasureCalculator::drawFilledPolygonOnImage(const std::vector<cv::Point> &polygon) {
    // Compute the size of the image to which the polygon will be added
    // The width and height of the polygon are equal to the width and height of
    // its corresponding upright bounding box
    cv::Rect polygonBoundingBox = cv::boundingRect(polygon);

    // Define the image to which the polygon is added
    cv::Mat polygonImage = cv::Mat::zeros(
        polygonBoundingBox.height + polygonBoundingBox.y,
        polygonBoundingBox.width + polygonBoundingBox.x,
        CV_8UC1
    );

    // Add the polygon to the image
    cv::fillConvexPoly(
        polygonImage, cv::Mat(polygon), cv::Scalar(POINT_MAX_VALUE)
    );

    return polygonImage;
}

void SpatialMeasureCalculator::subtractPolygonBorderFromImage(const std::vector<cv::Point> &polygon,
                                                              cv::Mat &image) {
    std::size_t nrOfPolygonPoints = polygon.size();

    // Draw lines between each two points in the polygon
    for (std::size_t i = 0; i < nrOfPolygonPoints; i++) {
        line(
            image,
            polygon[i],
            polygon[(i + 1) % nrOfPolygonPoints],
            cv::Scalar(POINT_MIN_VALUE)
        );
    }
}

cv::Mat SpatialMeasureCalculator::drawFilledCircleOnImage(const cv::Point2f &circleOrigin, double circleRadius) {
    int circleRadiusAsInt = static_cast<int>(circleRadius);

    // Define the image to which the circle is added.
    cv::Mat circleImage = cv::Mat::zeros(
        std::ceil(circleOrigin.y) + circleRadiusAsInt + 2,
        std::ceil(circleOrigin.x) + circleRadiusAsInt + 2,
        CV_8UC1
    );

    // Add the circle to the image
    cv::circle(
        circleImage, circleOrigin, circleRadiusAsInt,
        cv::Scalar(POINT_MAX_VALUE), CV_FILLED
    );

    return circleImage;
}

int SpatialMeasureCalculator::computeNrOfMinValuePointSides(int rowIndex, int colIndex,
                                                         const cv::Mat &image) {
    return (
      (isMinValuePointUp    (rowIndex, colIndex, image) ? 1 : 0) +
      (isMinValuePointLeft  (rowIndex, colIndex, image) ? 1 : 0) +
      (isMinValuePointDown  (rowIndex, colIndex, image) ? 1 : 0) +
      (isMinValuePointRight (rowIndex, colIndex, image) ? 1 : 0)
    );
}

bool SpatialMeasureCalculator::isMinValuePointUp(int rowIndex, int colIndex, const cv::Mat &image) {
    return (
        (rowIndex == 0) ||
        (image.at<uchar>(rowIndex - 1, colIndex) == POINT_MIN_VALUE)
    );
}

bool SpatialMeasureCalculator::isMinValuePointLeft(int rowIndex, int colIndex, const cv::Mat &image) {
    return (
        (colIndex == 0) ||
        (image.at<uchar>(rowIndex, colIndex - 1) == POINT_MIN_VALUE)
    );
}

bool SpatialMeasureCalculator::isMinValuePointDown(int rowIndex, int colIndex, const cv::Mat &image) {
    return (
        (rowIndex == (image.rows - 1)) ||
        (image.at<uchar>(rowIndex + 1, colIndex) == POINT_MIN_VALUE)
    );
}

bool SpatialMeasureCalculator::isMinValuePointRight(int rowIndex, int colIndex, const cv::Mat &image) {
    return (
        (colIndex == (image.cols - 1)) ||
        (image.at<uchar>(rowIndex, colIndex + 1) == POINT_MIN_VALUE)
    );
}


// Constants
const int SpatialMeasureCalculator::POINT_MIN_VALUE = 0;
const int SpatialMeasureCalculator::POINT_MAX_VALUE = 255;
