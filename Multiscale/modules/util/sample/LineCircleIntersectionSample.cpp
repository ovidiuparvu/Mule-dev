#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace cv;
using namespace multiscale;
using namespace std;


// Print the points from the vector

void printPoints(const vector<Point2f> &points) {
    cout << "=========== Points ===========" << endl;

    for (const Point2f &point : points) {
        cout << point.x << " " << point.y << endl;
    }
}

// Main function

int main() {
    vector<Point2f> intersectionPoints;

    Geometry2D::lineSegmentCircleIntersection(Point(4, 4), Point(4, 5), Point(5, 5), 2, intersectionPoints);
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineSegmentCircleIntersection(Point(5, 4), Point(4, 5), Point(5, 5), 2, intersectionPoints);
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineCircleIntersection(Point(4, 4), Point(4, 5), Point(5, 5), 1, intersectionPoints);
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineCircleIntersection(Point(4, 4), Point(4, 5), Point(5, 5), 0.5, intersectionPoints);
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    return EXEC_SUCCESS_CODE;
}
