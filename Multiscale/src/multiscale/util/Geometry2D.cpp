#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale;

double Geometry2D::computeDistance(Point a, Point b) {
    double xDiff = a.x - b.x;
    double yDiff = a.y - b.y;

    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double Geometry2D::computeAngle(Point a, Point b, Point c) {
    Point2f ab(b.x - a.x, b.y - a.y);
    Point2f cb(b.x - c.x, b.y - c.y);

    double dotProduct   = (ab.x * cb.x + ab.y * cb.y);
    double crossProduct = (ab.x * cb.y - ab.y * cb.x);

    double alpha = atan2(crossProduct, dotProduct);

    return abs(((alpha * 180) / PI));
}

vector<Point> Geometry2D::findPointsOnEdge(const vector<Point> &points,
                                           unsigned int nrOfRows,
                                           unsigned int nrOfCols) {
    vector<Point> pointsOnEdge;

    for (Point p : points) {
        if (isPointOnEdge(p, nrOfRows, nrOfCols)) {
            pointsOnEdge.push_back(p);
        }
    }

    return pointsOnEdge;
}

bool Geometry2D::isPointOnEdge(Point p, int nrOfRows, int nrOfCols) {
    return (
              ((p.x == MATRIX_START_INDEX) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.x == nrOfRows) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.y == MATRIX_START_INDEX) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows)) ||
              ((p.y == nrOfCols) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows))
           );
}
