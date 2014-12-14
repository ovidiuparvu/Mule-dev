#include "multiscale/analysis/spatial/model/Region.hpp"
#include "multiscale/analysis/spatial/util/SpatialMeasureCalculator.hpp"
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
    double outerPolygonArea = static_cast<double>(
                                  SpatialMeasureCalculator::computePolygonArea(outerBorderPolygon)
                              );
    double innerPolygonArea = 0.0;

    for (auto innerPolygon : innerBorderPolygons) {
        innerPolygonArea += static_cast<double>(
                                SpatialMeasureCalculator::computePolygonArea(innerPolygon)
                            );
    }

    return (
        Numeric::division(
            (outerPolygonArea - innerPolygonArea),
            outerPolygonArea
        )
    );
}

void Region::updateDensity() {}

void Region::updateArea() {
    if (outerBorderPolygon.size() > 0) {
        area = static_cast<double>(computeAreaIfOuterBoderDefined());
    }
}

double Region::computeAreaIfOuterBoderDefined() {
    double outerPolygonArea = static_cast<double>(
                                  SpatialMeasureCalculator::computePolygonArea(outerBorderPolygon)
                              );
    double innerPolygonArea = 0.0;

    for (auto innerPolygon : innerBorderPolygons) {
        innerPolygonArea += static_cast<double>(
                                SpatialMeasureCalculator::computePolygonArea(innerPolygon)
                             );
    }

    return (outerPolygonArea - innerPolygonArea);
}

void Region::updatePerimeter() {
    if (outerBorderPolygon.size() > 0) {
        perimeter = static_cast<double>(
                        SpatialMeasureCalculator::computePolygonPerimeter(outerBorderPolygon)
                    );
    }
}

double Region::isTriangularMeasure() {
    std::vector<cv::Point> contourConvexHull;

    // Compute the convex hull of the outer border polygon
    convexHull(outerBorderPolygon, contourConvexHull, CONVEX_HULL_CLOCKWISE);

    // Find the minimum area triangle enclosing the convex hull
    MinEnclosingTriangleFinder().find(convertPoints(contourConvexHull), minAreaEnclosingTriangle);

    // Compute the area of the triangle
    double triangleArea = static_cast<double>(
                              SpatialMeasureCalculator::computePolygonArea(
                                  convertPoints(minAreaEnclosingTriangle)
                              )
                          );

    // Normalise the triangular measure
    return normalisedShapeMeasure(triangleArea);
}

double Region::isRectangularMeasure() {
    std::vector<cv::Point> minAreaEnclosingRect =
        minAreaEnclosingRectPoints(outerBorderPolygon);

    // Compute the area of the minimum area enclosing rectangle
    double rectangleArea = static_cast<double>(
                               SpatialMeasureCalculator::computePolygonArea(minAreaEnclosingRect)
                           );

    return normalisedShapeMeasure(rectangleArea);
}

double Region::isCircularMeasure() {
    minEnclosingCircle(outerBorderPolygon, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    // Compute the area of the minimum area enclosing circle
    double circleArea = static_cast<double>(
                            SpatialMeasureCalculator::computeCircleArea(
                                minAreaEnclosingCircleCentre,
                                minAreaEnclosingCircleRadius
                            )
                        );

    return normalisedShapeMeasure(circleArea);
}

void Region::updateCentrePoint() {
    if (outerBorderPolygon.size() == 1) {
        updateCentrePointWhenRegionDefinedBySinglePoint();
    } else {
        updateCentrePointWhenRegionDefinedByMultiplePoints();
    }
}

void Region::updateCentrePointWhenRegionDefinedBySinglePoint() {
    centre = outerBorderPolygon.back();
}

void Region::updateCentrePointWhenRegionDefinedByMultiplePoints() {
    cv::Moments polygonMoments = moments(outerBorderPolygon, false);

    centre.x = Numeric::division(polygonMoments.m10, polygonMoments.m00);
    centre.y = Numeric::division(polygonMoments.m01, polygonMoments.m00);
}

SpatialEntityPseudo3DType Region::type() {
    return SpatialEntityPseudo3DType::Region;
}


// Constants
const bool Region::CONTOUR_ORIENTED = false;
const bool Region::CONTOUR_CLOSED   = true;
