#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/analysis/spatial/Region.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Region::Region(double clusterednessDegree, double density, double area, double distanceFromOrigin,
               double angleWrtOrigin, const vector<Point> &polygon) : SpatialEntityPseudo3D() {
    validateInputValues(clusterednessDegree, density, area, distanceFromOrigin, angleWrtOrigin, polygon);

    this->clusterednessDegree = clusterednessDegree;
    this->density = density;
    this->area = area;
    this->distanceFromOrigin = distanceFromOrigin;
    this->angle = angleWrtOrigin;

    this->polygon = polygon;
}

Region::~Region() {
    polygon.clear();
}

const vector<Point>& Region::getPolygon() {
    return polygon;
}

void Region::validateInputValues(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                                 double angleWrtOrigin, const vector<Point> &polygon) {
    if (!areValidInputValues(clusterednessDegree, density, area, distanceFromOrigin, angleWrtOrigin, polygon)) {
        MS_throw(InvalidInputException, ERR_INPUT);
    }
}

bool Region::areValidInputValues(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                                 double angleWrtOrigin, const vector<Point> &polygon) {
    for (const Point &point : polygon) {
        if ((point.x < 0) || (point.y < 0)) {
            return false;
        }
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

void Region::updateClusterednessDegree() {}

void Region::updateDensity() {}

void Region::updateArea() {}

void Region::updatePerimeter() {
    perimeter = arcLength(polygon, CONTOUR_CLOSED);
}

double Region::isTriangularMeasure() {
    vector<Point2f> minAreaEnclosingTriangle;
    vector<Point> contourConvexHull;

    convexHull(polygon, contourConvexHull, CONVEX_HULL_CLOCKWISE);

    double triangleArea = MinEnclosingTriangleFinder().find(convertPoints(contourConvexHull), minAreaEnclosingTriangle);

    return normalisedShapeMeasure(triangleArea);
}

double Region::isRectangularMeasure() {
    RotatedRect minAreaEnclosingRect = minAreaRect(polygon);

    // Compute the area of the minimum area enclosing rectangle
    double rectangleArea = minAreaEnclosingRect.size.height * minAreaEnclosingRect.size.width;

    return normalisedShapeMeasure(rectangleArea);
}

double Region::isCircularMeasure() {
    Point2f minAreaEnclosingCircleCentre;
    float minAreaEnclosingCircleRadius;

    minEnclosingCircle(polygon, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    // Compute the area of the minimum area enclosing circle
    double circleArea = Geometry2D::PI * minAreaEnclosingCircleRadius * minAreaEnclosingCircleRadius;

    return normalisedShapeMeasure(circleArea);
}

void Region::updateCentrePoint() {
    Moments polygonMoments = moments(polygon, false);

    centre.x = (polygonMoments.m10 / polygonMoments.m00);
    centre.y = (polygonMoments.m01 / polygonMoments.m00);
}

SpatialEntityPseudo3DType Region::type() {
    return SpatialEntityPseudo3DType::Region;
}


// Constants
const bool Region::CONTOUR_ORIENTED = false;
const bool Region::CONTOUR_CLOSED   = true;
