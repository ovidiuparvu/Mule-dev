#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale;

double Geometry2D::distanceBtwPoints(Point a, Point b) {
    double xDiff = a.x - b.x;
    double yDiff = a.y - b.y;

    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double Geometry2D::angleBtwPoints(Point a, Point b, Point c) {
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

unsigned int Geometry2D::minimumDistancePointIndex(const vector<Point> &contour, const Point &origin) {
    double minDistance = numeric_limits<int>::max();
    double distance = 0.0;
    int nrOfPoints = contour.size();
    int minimumDistancePointIndex = -1;

    for (int i = 0; i < nrOfPoints; i++) {
        distance = distanceBtwPoints(contour[i], origin);

        if (distance < minDistance) {
            minDistance = distance;

            minimumDistancePointIndex = i;
        }
    }

    return minimumDistancePointIndex;
}

bool Geometry2D::isPointOnEdge(Point p, int nrOfRows, int nrOfCols) {
    return (
              ((p.x == MATRIX_START_INDEX) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.x == nrOfRows) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.y == MATRIX_START_INDEX) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows)) ||
              ((p.y == nrOfCols) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows))
           );
}
