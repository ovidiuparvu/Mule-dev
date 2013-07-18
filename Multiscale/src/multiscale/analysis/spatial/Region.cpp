#include "multiscale/analysis/spatial/Region.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Region::Region(double area, double distanceFromOrigin, double angle, const vector<Point> &polygon) {
    this->area = area;
    this->distanceFromOrigin = distanceFromOrigin;
    this->angle = angle;

    this->polygon = polygon;
}

Region::~Region() {
    polygon.clear();
}

double Region::getAngle() const {
    return angle;
}

double Region::getArea() const {
    return area;
}

double Region::getDistanceFromOrigin() const {
    return distanceFromOrigin;
}

const vector<Point>& Region::getPolygon() const {
    return polygon;
}

string Region::fieldNamesToString() {
    return "Area,Distance from origin,Angle(degrees)";
}

string Region::toString() {
    return StringManipulator::toString<double>(area) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(distanceFromOrigin) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(angle);
}
