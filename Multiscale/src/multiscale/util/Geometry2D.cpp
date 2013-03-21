#include "multiscale/util/Geometry2D.hpp"

#include <algorithm>

using namespace multiscale;


double Geometry2D::distanceBtwPoints(const Point &a, const Point &b) {
    double xDiff = a.x - b.x;
    double yDiff = a.y - b.y;

    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double Geometry2D::distanceFromPointToLine(const Point &a, const Point &linePointB, const Point &linePointC) {
    double term1 = linePointC.x - linePointB.x;
    double term2 = linePointB.y - a.y;
    double term3 = linePointB.x - a.x;
    double term4 = linePointC.y - linePointB.y;

    double nominator = abs((term1 * term2) - (term3 * term4));
    double denominator = sqrt((term1 * term1) + (term4 * term4));

    return (nominator / denominator);
}

Point Geometry2D::middlePoint(const Point &a, const Point &b) {
    int middleX = (a.x + b.x) / 2;
    int middleY = (a.y + b.y) / 2;

    return Point(middleX, middleY);
}

void Geometry2D::orthogonalLineToAnotherLineEdgePoints(const Point &a1, const Point &b1, Point &a2 ,
                                                       Point &b2, int nrOfRows, int nrOfCols) {
    assert((a1.x != b1.x) || (a1.y != b1.y));

    if ((b1.x - a1.x) == 0) {   // Vertical line
        a2 = b1;
        b2 = b1;

        while (!isPointOnEdge(a2, nrOfRows, nrOfCols))
            a2.y--;

        while (!isPointOnEdge(b2, nrOfRows, nrOfCols))
            b2.y++;
    } else if (b1.y - a1.y == 0) {  // Horizontal line
        a2 = b1;
        b2 = b1;

        while (!isPointOnEdge(a2, nrOfRows, nrOfCols))
            a2.x--;

        while (!isPointOnEdge(b2, nrOfRows, nrOfCols))
            b2.x++;
    } else {                        // Otherwise
        double oldSlope = ((double)(b1.y - a1.y)) / (b1.x - a1.x);

        double newSlope = (-1) / (oldSlope);
        double intercept = b1.y - (newSlope * b1.x);

        a2 = b1;
        b2 = b1;

        while (!isPointOnEdge(a2, nrOfRows, nrOfCols)) {
            a2.x = a2.x - 1;
            a2.y = a2.x * newSlope + intercept;
        }

        while (!isPointOnEdge(b2, nrOfRows, nrOfCols)) {
            b2.x = b2.x + 1;
            b2.y = b2.x * newSlope + intercept;
        }
    }
}

bool Geometry2D::lineIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection) {
    int A1 = b1.y - a1.y;
    int B1 = a1.x - b1.x;
    int C1 = (a1.x * A1) + (a1.y * B1);

    int A2 = b2.y - a2.y;
    int B2 = a2.x - b2.x;
    int C2 = (a2.x * A2) + (a2.y * B2);

    int det = (A1 * B2) - (A2 * B1);

    if (det != 0) {
        intersection.x = ((C1 * B2) - (C2 * B1)) / (det);
        intersection.y = ((C2 * A1) - (C1 * A2)) / (det);

        return true;
    }

    return false;
}

bool Geometry2D::lineSegmentIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection) {
    if (lineIntersection(a1, b1, a2, b2, intersection)) {
        return (
                    isBetweenCoordinates<int, int>(intersection.x, a1.x, b1.x) &&
                    isBetweenCoordinates<int, int>(intersection.x, a2.x, b2.x) &&
                    isBetweenCoordinates<int, int>(intersection.y, a1.y, b1.y) &&
                    isBetweenCoordinates<int, int>(intersection.y, a2.y, b2.y)
               );
    }

    return false;
}

bool Geometry2D::lineCircleIntersection(Point a, Point b, const Point &circleOrigin,
                                        double radius, vector<Point2f> &intersectionPoints) {
    translate(a, Point(-circleOrigin.x, -circleOrigin.y));
    translate(b, Point(-circleOrigin.x, -circleOrigin.y));

    double A = b.y - a.y;
    double B = a.x - b.x;
    double C = (a.x * A) + (a.y * B);

    double A2 = A * A;
    double B2 = B * B;
    double C2 = C * C;
    double R2 = radius * radius;

    double delta = (4 * B2 * C2) - (4 * (A2 + B2) * (C2 - (R2 * A2)));

    if (delta > 0) {            /*!< Two intersection points */
        lineCircleTwoIntersectionPoints(circleOrigin, A, B, C, delta, intersectionPoints);

        return true;
    } else if (delta == 0) {    /*!< One intersection point */
        lineCircleOneIntersectionPoint(circleOrigin, A, B, C, delta, intersectionPoints);

        return true;
    }

    return false;
}

bool Geometry2D::lineSegmentCircleIntersection(const Point &a, const Point &b, const Point &circleOrigin,
                                                      double radius, vector<Point2f> &intersectionPoints) {
    if (lineCircleIntersection(a, b, circleOrigin, radius, intersectionPoints)) {
        for (vector<Point2f>::iterator it = intersectionPoints.begin(); it != intersectionPoints.end(); ) {
            if (isBetweenCoordinates<float, int>((*it).x, a.x, b.x) &&
                isBetweenCoordinates<float, int>((*it).y, a.y, b.y)
               ) {
                ++it;
            } else {
                intersectionPoints.erase(it);
            }
        }

        return (intersectionPoints.size() > 0);
    }

    return false;
}

double Geometry2D::angleBtwPoints(const Point &a, const Point &b, const Point &c) {
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

bool Geometry2D::isPointOnEdge(const Point &p, int nrOfRows, int nrOfCols) {
    return (
              ((p.x <= MATRIX_START_INDEX) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.x >= nrOfRows) && (p.y > MATRIX_START_INDEX) && (p.y < nrOfCols)) ||
              ((p.y <= MATRIX_START_INDEX) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows)) ||
              ((p.y >= nrOfCols) && (p.x > MATRIX_START_INDEX) && (p.x < nrOfRows))
           );
}

template <typename T, typename U>
bool Geometry2D::isBetweenCoordinates(T c, U c1, U c2) {
    return ((std::min(c1, c2) <= c) && (c <= std::max(c1, c2)));
}

int Geometry2D::sgn(int number) {
    return (number < 0) ? -1
                        : 1;
}

void Geometry2D::translate(Point &point, const Point &translation) {
    point.x += translation.x;
    point.y += translation.y;
}

void Geometry2D::inverseTranslate(Point2f &point, const Point &translation) {
    point.x -= translation.x;
    point.y -= translation.y;
}

void Geometry2D::lineCircleTwoIntersectionPoints(const Point &circleOrigin, double A, double B,
                                                 double C, double delta, vector<Point2f> &intersectionPoints) {
    double y1 = ((2 * B * C) + (sqrt(delta))) / (2 * ((A * A) + (B * B)));
    double y2 = ((2 * B * C) - (sqrt(delta))) / (2 * ((A * A) + (B * B)));

    double x1 = (C - (B * y1)) / (A);
    double x2 = (C - (B * y2)) / (A);

    Point2f firstIntersectionPoint(x1, y1);
    Point2f secondIntersectionPoint(x2, y2);

    inverseTranslate(firstIntersectionPoint, Point(-circleOrigin.x, -circleOrigin.y));
    inverseTranslate(secondIntersectionPoint, Point(-circleOrigin.x, -circleOrigin.y));

    intersectionPoints.push_back(firstIntersectionPoint);
    intersectionPoints.push_back(secondIntersectionPoint);
}

void Geometry2D::lineCircleOneIntersectionPoint(const Point &circleOrigin, double A, double B,
                                                double C, double delta, vector<Point2f> &intersectionPoints) {
    double y = (B * C) / ((A * A) + (B * B));
    double x = (C - (B * y)) / (A);

    Point2f intersectionPoint(x, y);

    inverseTranslate(intersectionPoint, Point(-circleOrigin.x, -circleOrigin.y));

    intersectionPoints.push_back(intersectionPoint);
}
