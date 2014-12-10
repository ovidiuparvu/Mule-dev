#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/analysis/spatial/Region.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Region::Region(double density, double distanceFromOrigin, double angleWrtOrigin,
               const std::vector<cv::Point> &outerBorderPolygon,
               const std::vector<std::vector<cv::Point> > &innerBorderPolygons) : SpatialEntityPseudo3D() {
    validateInputValues(density, distanceFromOrigin, angleWrtOrigin,
                        outerBorderPolygon, innerBorderPolygons);

    this->density               = density;
    this->distanceFromOrigin    = distanceFromOrigin;
    this->angle                 = angleWrtOrigin;

    this->outerBorderPolygon    = outerBorderPolygon;
    this->innerBorderPolygons   = innerBorderPolygons;
}

Region::~Region() {}

const std::vector<cv::Point>& Region::getOuterBorderPolygon() const {
    return outerBorderPolygon;
}

const std::vector<std::vector<cv::Point> >& Region::getInnerBorderPolygons() const {
    return innerBorderPolygons;
}

void Region::validateInputValues(double density, double distanceFromOrigin, double angleWrtOrigin,
                                 const std::vector<cv::Point> &outerBorderPolygon,
                                 const std::vector<std::vector<cv::Point> > &innerBorderPolygons) {
    if (!areValidInputValues(density, distanceFromOrigin, angleWrtOrigin,
                             outerBorderPolygon, innerBorderPolygons)) {
        MS_throw(InvalidInputException, ERR_INPUT);
    }
}

bool Region::areValidInputValues(double density, double distanceFromOrigin, double angleWrtOrigin,
                                 const std::vector<cv::Point> &outerBorderPolygon,
                                 const std::vector<std::vector<cv::Point> > &innerBorderPolygons) {
    if (!areValidInputPolygons(outerBorderPolygon, innerBorderPolygons)) {
        return false;
    }

    return (
        (Numeric::greaterOrEqual(clusterednessDegree, 0)) &&
        (Numeric::greaterOrEqual(density, 0)) &&
        (Numeric::greaterOrEqual(area, 0)) &&
        (Numeric::greaterOrEqual(distanceFromOrigin, 0)) &&
        (Numeric::lessOrEqual(0, angleWrtOrigin)) &&
        (Numeric::lessOrEqual(angleWrtOrigin, 360))
    );
}

bool Region::areValidInputPolygons(const std::vector<cv::Point> &outerBorderPolygon,
                                   const std::vector<std::vector<cv::Point> > &innerBorderPolygons) {
    return (
        (isValidInputPolygon(outerBorderPolygon)) &&
        (areValidInputPolygons(innerBorderPolygons))
    );
}

bool Region::areValidInputPolygons(const std::vector<std::vector<cv::Point> > &polygons) {
    for (auto polygon : polygons) {
        if (!isValidInputPolygon(polygon)) {
            return false;
        }
    }

    return true;
}

bool Region::isValidInputPolygon(const std::vector<cv::Point> &polygon) {
    for (const cv::Point &point : polygon) {
        if ((point.x < 0) || (point.y < 0)) {
            return false;
        }
    }

    return true;
}

void Region::updateClusterednessDegree() {
    if (outerBorderPolygon.size() > 0) {
        clusterednessDegree = computeClusterednessDegreeIfOuterBorderDefined();
    }
}

double Region::computeClusterednessDegreeIfOuterBorderDefined() {
    double outerPolygonArea = contourArea(outerBorderPolygon, CONTOUR_ORIENTED);
    double innerPolygonArea = 0;

    for (auto innerPolygon : innerBorderPolygons) {
        innerPolygonArea += contourArea(innerPolygon, CONTOUR_ORIENTED);
    }

    return (
        (Numeric::almostEqual(outerPolygonArea, 0))
            ? 0
            : ((outerPolygonArea - innerPolygonArea) / (outerPolygonArea))
    );
}

void Region::updateDensity() {}

void Region::updateArea() {
    if (outerBorderPolygon.size() > 0) {
        area = computeAreaIfOuterBoderDefined();
    }
}

double Region::computeAreaIfOuterBoderDefined() {
    double outerPolygonArea = contourArea(outerBorderPolygon, CONTOUR_ORIENTED);
    double innerPolygonArea = 0;

    for (auto innerPolygon : innerBorderPolygons) {
        innerPolygonArea += contourArea(innerPolygon, CONTOUR_ORIENTED);
    }

    return (outerPolygonArea - innerPolygonArea);
}

void Region::updatePerimeter() {
    perimeter = arcLength(outerBorderPolygon, CONTOUR_CLOSED);
}

double Region::isTriangularMeasure() {
    std::vector<cv::Point2f> minAreaEnclosingTriangle;
    std::vector<cv::Point> contourConvexHull;

    convexHull(outerBorderPolygon, contourConvexHull, CONVEX_HULL_CLOCKWISE);

    double triangleArea = MinEnclosingTriangleFinder().find(
                              convertPoints(contourConvexHull), minAreaEnclosingTriangle
                          );

    return normalisedShapeMeasure(triangleArea);
}

double Region::isRectangularMeasure() {
    cv::RotatedRect minAreaEnclosingRect = minAreaRect(outerBorderPolygon);

    // Compute the area of the minimum area enclosing rectangle
    double rectangleArea = minAreaEnclosingRect.size.height * minAreaEnclosingRect.size.width;

    return normalisedShapeMeasure(rectangleArea);
}

double Region::isCircularMeasure() {
    cv::Point2f minAreaEnclosingCircleCentre;
    float minAreaEnclosingCircleRadius;

    minEnclosingCircle(outerBorderPolygon, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    // Compute the area of the minimum area enclosing cv::circle
    double circleArea = Geometry2D::PI * minAreaEnclosingCircleRadius * minAreaEnclosingCircleRadius;

    return normalisedShapeMeasure(circleArea);
}

void Region::updateCentrePoint() {
    cv::Moments polygonMoments = moments(outerBorderPolygon, false);

    centre.x = (Numeric::almostEqual(polygonMoments.m00, 0))
                    ? polygonMoments.m10
                    : (polygonMoments.m10 / polygonMoments.m00);
    centre.y = (Numeric::almostEqual(polygonMoments.m00, 0))
                    ? polygonMoments.m01
                    : (polygonMoments.m01 / polygonMoments.m00);
}

SpatialEntityPseudo3DType Region::type() {
    return SpatialEntityPseudo3DType::Region;
}


// Constants
const bool Region::CONTOUR_ORIENTED = false;
const bool Region::CONTOUR_CLOSED   = true;
