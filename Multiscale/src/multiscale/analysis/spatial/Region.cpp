#include "multiscale/analysis/spatial/Region.hpp"

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

inline double Region::getAngle() const {
    return angle;
}

inline double Region::getArea() const {
    return area;
}

inline double Region::getDistanceFromOrigin() const {
    return distanceFromOrigin;
}

inline const vector<Point>& Region::getPolygon() const {
    return polygon;
}
