#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


double CircularityMeasure::compute(const std::vector<cv::Point2f> &points) {
    std::vector<cv::Point2f> enclosingPolygon;

    // Obtain the convex hull of the set of points
    convexHull(points, enclosingPolygon, true, true);

    // Obtain the set of moments and compute the circularity measure
    cv::Moments contourMoments = moments(enclosingPolygon);

    double nominator = (contourMoments.m00 * contourMoments.m00);
    double denominator = (2 * Geometry2D::PI * (contourMoments.mu20 + contourMoments.mu02));

    return (Numeric::almostEqual(denominator, 0)) ? 0
                                                  : (nominator / denominator);
}

double CircularityMeasure::compute(const std::vector<cv::Point> &points) {
    std::vector<cv::Point> enclosingPolygon;

    // Obtain the convex hull of the set of points
    convexHull(points, enclosingPolygon, true, true);

    // Obtain the set of moments and compute the circularity measure
    cv::Moments contourMoments = moments(enclosingPolygon);

    double nominator = (contourMoments.m00 * contourMoments.m00);
    double denominator = (2 * Geometry2D::PI * (contourMoments.mu20 + contourMoments.mu02));

    return (Numeric::almostEqual(denominator, 0)) ? 0
                                                  : (nominator / denominator);
}
