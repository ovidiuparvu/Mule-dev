#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


double CircularityMeasure::compute(const vector<Point2f> &points) {
    vector<Point2f> enclosingPolygon;

    // Obtain the convex hull of the set of points
    convexHull(points, enclosingPolygon, true, true);

    // Obtain the set of moments and compute the circularity measure
    Moments contourMoments = moments(enclosingPolygon);

    double nominator = (contourMoments.m00 * contourMoments.m00);
    double denominator = (2 * PI * (contourMoments.mu20 + contourMoments.mu02));

    return (denominator != 0) ? nominator / denominator
                              : 0;
}

double CircularityMeasure::compute(const vector<Point> &points) {
    vector<Point> enclosingPolygon;

    // Obtain the convex hull of the set of points
    convexHull(points, enclosingPolygon, true, true);

    // Obtain the set of moments and compute the circularity measure
    Moments contourMoments = moments(enclosingPolygon);

    double nominator = (contourMoments.m00 * contourMoments.m00);
    double denominator = (2 * PI * (contourMoments.mu20 + contourMoments.mu02));

    return (denominator != 0) ? nominator / denominator
                              : 0;
}
