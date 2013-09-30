#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/analysis/spatial/Region.hpp"
#include "multiscale/exception/RegionException.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Region::Region(double clusterednessDegree, double density, double area, double distanceFromOrigin,
               double angleWrtOrigin, const vector<Point> &polygon) : SpatialCollection2D() {
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

double Region::getDensity() {
    updateMeasuresIfRequired();

    return density;
}

const vector<Point>& Region::getPolygon() {
    return polygon;
}

string Region::fieldNamesToString() {
    return "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)";
}

void Region::validateInputValues(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                                 double angleWrtOrigin, const vector<Point> &polygon) {
    if (!areValidInputValues(clusterednessDegree, density, area, distanceFromOrigin, angleWrtOrigin, polygon)) {
        throw RegionException(ERR_INPUT);
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
        (clusterednessDegree > 0) &&
        (density > 0) &&
        (area > 0) &&
        (distanceFromOrigin > 0) &&
        (Numeric::lessOrEqual(0, angleWrtOrigin)) &&
        (Numeric::lessOrEqual(angleWrtOrigin, 360))
    );
}

void Region::updateSpatialCollectionSpecificValues() {}

void Region::updateClusterednessDegree() {}

void Region::updateArea() {}

void Region::updatePerimeter() {
    perimeter = arcLength(polygon, CONTOUR_CLOSED);
}

double Region::isTriangularMeasure() {
    vector<Point2f> minAreaEnclosingTriangle;
    vector<Point> contourConvexHull;

    convexHull(polygon, contourConvexHull, CONVEX_HULL_CLOCKWISE);

    double triangleArea = MinEnclosingTriangleFinder().find(convertPoints(contourConvexHull), minAreaEnclosingTriangle);

    return (Numeric::almostEqual(triangleArea, 0)) ? 0
                                                   : (area / triangleArea);
}

double Region::isRectangularMeasure() {
    RotatedRect minAreaEnclosingRect = minAreaRect(polygon);

    // Compute the area of the minimum area enclosing rectangle
    double rectangleArea = minAreaEnclosingRect.size.height * minAreaEnclosingRect.size.width;

    return (Numeric::almostEqual(rectangleArea, 0)) ? 0
                                                    : (area / rectangleArea);
}

double Region::isCircularMeasure() {
    Point2f minAreaEnclosingCircleCentre;
    float minAreaEnclosingCircleRadius;

    minEnclosingCircle(polygon, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    // Compute the area of the minimum area enclosing circle
    double circleArea = PI * minAreaEnclosingCircleRadius * minAreaEnclosingCircleRadius;

    return (Numeric::almostEqual(circleArea, 0)) ? 0
                                                 : (area / circleArea);
}

void Region::updateCentrePoint() {
    RotatedRect minAreaEnclosingRect = minAreaRect(polygon);

    centre = minAreaEnclosingRect.center;
}

string Region::fieldValuesToString() {
    return StringManipulator::toString<double>(clusterednessDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(density) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(area) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(perimeter) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(distanceFromOrigin) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(angle) + OUTPUT_SEPARATOR +
           shapeAsString() + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(triangularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(rectangularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(circularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.x) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.y);
}
