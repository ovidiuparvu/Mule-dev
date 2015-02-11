#include "multiscale/analysis/spatial/util/CircularityMeasure.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;

template <typename PointType>
double CircularityMeasure<PointType>::compute(const std::vector<cv::Point_<PointType>> &points) {
    std::vector<cv::Point2f> enclosingPolygon;

    // Obtain the convex hull of the set of points
    enclosingPolygon = Geometry2D::computeConvexHull(points, true);

    // Obtain the set of moments and compute the circularity measure
    cv::Moments contourMoments = moments(enclosingPolygon);

    double nominator = (contourMoments.m00 * contourMoments.m00);
    double denominator = (2 * Geometry2D::PI * (contourMoments.mu20 + contourMoments.mu02));

    return (Numeric::division(nominator, denominator));
}
