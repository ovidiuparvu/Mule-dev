#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/MinimumAreaEnclosingTriangle.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace multiscale;

#define RADIUS                  1
#define WIN_MIN_AREA_TRIANGLE   "Minimum area enclosing triangle"
#define NR_RAND_POLYGONS        50
#define MAX_POLYGON_POINTS      10
#define POLYGON_POINT_X_MAX     50
#define POLYGON_POINT_Y_MAX     50


// Compute the area of a triangle specified by three points
void testAreaOfTriangle(const Point2f &a, const Point2f &b, const Point2f &c) {
    cout << "The area of the triangle determined by the points "
             << "(" << a.x << ", " << a.y << "), "
             << "(" << b.x << ", " << b.y << ") and "
             << "(" << c.x << ", " << c.y << ") is: "
             << Geometry2D::areaOfTriangle(a, b, c) << endl;
}

// Compute the area of a triangle specified by three points
void testAreaOfTriangle() {
    testAreaOfTriangle(Point2f(1, 2), Point2f(2, 3), Point2f(3, 4)); // 0
    testAreaOfTriangle(Point2f(5, 2), Point2f(2, 3), Point2f(3, 9)); // 9.5
    testAreaOfTriangle(Point2f(5, 5), Point2f(2.4, 0), Point2f(3, 4)); // 3.7
    testAreaOfTriangle(Point2f(0, 4.9), Point2f(0, 0), Point2f(10, 10)); // 24.5
}

// Compute the angle of the line specified by two points
void testAngleOfLine(const Point2f &a, const Point2f &b) {
    cout << "The angle of the line determined by the points "
         << "(" << a.x << ", " << a.y << ") and "
         << "(" << b.x << ", " << b.y << ") is: "
         << Geometry2D::angleOfLineWrtOxAxis(a, b) << endl;
}

// Compute the angle of the line specified by two points
void testAngleOfLine() {
    testAngleOfLine(Point2f(0, 0), Point2f(2, 2)); // 0.785398163
    testAngleOfLine(Point2f(1, 2), Point2f(8, 4)); // 0.278285768
    testAngleOfLine(Point2f(0, 0), Point2f(0, 2)); // 1.57079633
    testAngleOfLine(Point2f(-1, 7), Point2f(2, 2)); // 2.11050995
    testAngleOfLine(Point2f(2, 0), Point2f(0, 0)); // 3.14
    testAngleOfLine(Point2f(0, 0), Point2f(2, 0)); // 0
}

// Print the polygon points
void printPolygonPoints(vector<Point2f> &polygon) {
    // Print the polygon points
    cout << "Polygon points: ";

    for (Point2f &point : polygon) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }

    cout << endl;
}

// Output the results for the minimum area enclosing triangle
void outputMinimumAreaEnclosingTriangleResults(const vector<Point2f> &minimumAreaEnclosingTriangle, vector<Point2f> &convexHullResult) {
    Mat image = Mat::zeros(100, 100, CV_32FC3);
    Mat flippedImage = Mat::zeros(100, 100, CV_32FC3);

    // Draw minimum area enclosing triangle
    for (unsigned int i = 0; i < minimumAreaEnclosingTriangle.size(); i++) {
        line(image, minimumAreaEnclosingTriangle[i], minimumAreaEnclosingTriangle[(i + 1) % minimumAreaEnclosingTriangle.size()], Scalar(0, 255, 0));
    }

    // Draw convex hull points
    for (Point2f &point : convexHullResult) {
        circle(image, point, RADIUS, Scalar(255, 0, 0));
    }

    printPolygonPoints(convexHullResult);

    // Flip image wrt Ox axis and show it
    flip(image, flippedImage, 0);

    namedWindow(WIN_MIN_AREA_TRIANGLE, WINDOW_NORMAL);
    imshow(WIN_MIN_AREA_TRIANGLE, flippedImage);

    waitKey();
}

// Test the minimum area enclosing triangle algorithm
void testMinimumAreaEnclosingTriangle(const vector<Point2f> &polygon) {
    vector<Point2f> minimumAreaEnclosingTriangle;
    double area = 0;

    // Get convex hull of polygon
    vector<Point2f> convexHullResult;

    convexHull(polygon, convexHullResult, true, true);

    if (convexHullResult.size() > 3) {
        // Find the minimum area enclosing triangle
        MinimumAreaEnclosingTriangle::find(convexHullResult, minimumAreaEnclosingTriangle, area);

        cout << "The area of the minimum area enclosing triangle is: " << area << endl;

        outputMinimumAreaEnclosingTriangleResults(minimumAreaEnclosingTriangle, convexHullResult);
    }
}

// Test the minimum area enclosing triangle algorithm using randomly generated polygons
void testMinimumAreaEnclosingTriangleUsingRandomPolygons() {
    vector<Point2f> points;

    // Initialise the seed - milliseconds is enough as this program is not to be run in parallel
    srand(time(0));

    for (int i = 0; i < NR_RAND_POLYGONS; i++) {
        points.clear();

        int nrOfPoints = rand() % MAX_POLYGON_POINTS;
        nrOfPoints = (nrOfPoints > 3) ? nrOfPoints : (nrOfPoints + 3);

        for (int j = 0; j < nrOfPoints; j++) {
            points.push_back(Point2f(rand() % POLYGON_POINT_X_MAX, rand() % POLYGON_POINT_Y_MAX));
        }

        testMinimumAreaEnclosingTriangle(points);
    }
}

// Test the minimum area enclosing triangle algorithm
void testMinimumAreaEnclosingTriangle() {
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(2, 2), Point2f(2, 6), Point2f(5, 2), Point2f(5, 6)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(1, 2), Point2f(1, 3), Point2f(7, 10), Point2f(13, 3), Point2f(13, 2)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(5, 24), Point2f(9, 10), Point2f(7, 38), Point2f(15, 18), Point2f(15, 44), Point2f(22, 14), Point2f(19, 38), Point2f(29, 18), Point2f(39, 30)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(0, 25), Point2f(1, 34), Point2f(5, 42), Point2f(21, 49), Point2f(46, 49), Point2f(48, 48), Point2f(47, 20), Point2f(45, 9), Point2f(34, 0), Point2f(33, 0), Point2f(12, 1), Point2f(2, 6), Point2f(1, 11)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(2, 15), Point2f(2, 25), Point2f(5, 49), Point2f(24, 48), Point2f(48, 41), Point2f(49, 18), Point2f(49, 4), Point2f(47, 1), Point2f(10, 5)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(0, 26), Point2f(4, 41), Point2f(6, 45), Point2f(14, 49), Point2f(32, 48), Point2f(38, 46), Point2f(49, 42), Point2f(49, 35), Point2f(45, 17), Point2f(41, 2), Point2f(38, 0), Point2f(8, 0), Point2f(2, 9)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});

//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(0, 28), Point2f(1, 40), Point2f(8, 46), Point2f(45, 48), Point2f(46, 26), Point2f(44, 0), Point2f(39, 0), Point2f(17, 1), Point2f(7, 8), Point2f(2, 22)});
    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(8, 30), Point2f(8, 34), Point2f(47, 39), Point2f(44, 14), Point2f(16, 24)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(4, 47), Point2f(44, 43), Point2f(49, 31), Point2f(31, 23)});

//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});
//    testMinimumAreaEnclosingTriangle(vector<Point2f>{Point2f(7, 21), Point2f(10, 41), Point2f(38, 29), Point2f(22, 3)});

//    testMinimumAreaEnclosingTriangleUsingRandomPolygons();
}

// Test if an angle lies between two other angles
void testIfAngleIsBetween(double angle1, double angle2, double angle3) {
    cout << angle1 << " is between " << angle2 << " and " << angle3 << ": " << (Geometry2D::isAngleBetween(angle1, angle2, angle3) ? "true" : "false") << endl;
}

// Test if an angle lies between two other angles
void testIfAngleIsBetween(const Point2f& p1, const Point2f &p2, const Point2f &q1, const Point2f &q2, const Point2f &r1, const Point2f &r2) {
    double angle1 = Geometry2D::angleOfLineWrtOxAxis(p1, p2);
    double angle2 = Geometry2D::angleOfLineWrtOxAxis(q1, q2);
    double angle3 = Geometry2D::angleOfLineWrtOxAxis(r1, r2);

    if (abs(angle2 - angle3) > 180) {
        if (angle2 <= 1E-7) {
            angle2 = 360;
        } else if (angle3 <= 1E-7) {
            angle3 = 360;
        }
    }

    testIfAngleIsBetween(angle1, angle2, angle3);
}

// Test if an angle lies between two other angles
void testIfAngleIsBetween() {
    testIfAngleIsBetween(Point2f(5, 6), Point2f(8, 9), Point2f(2, 6), Point2f(5, 6), Point2f(5, 2), Point2f(5, 6));
    testIfAngleIsBetween(Point2f(5, 2), Point2f(6, 1), Point2f(5, 6), Point2f(5, 2), Point2f(2, 2), Point2f(5, 2));
    testIfAngleIsBetween(Point2f(2, 2), Point2f(1, 1), Point2f(5, 2), Point2f(2, 2), Point2f(2, 6), Point2f(2, 2));
    testIfAngleIsBetween(Point2f(2, 6), Point2f(1, 7), Point2f(2, 2), Point2f(2, 6), Point2f(5, 6), Point2f(2, 6));
}

// Test if an angle or its opposite angle lies between two other angles
void testIfAngleOrOppositeIsBetween(double angle1, double angle2, double angle3) {
    cout << angle1 << " or its opposite are between " << angle2 << " and " << angle3 << ": " << (Geometry2D::isOppositeAngleBetween(angle1, angle2, angle3) ? "true" : "false") << endl;
}

// Test if a point lies on a line segment
void testIfPointOnLineSegment(const Point2f &p, const Point2f &lineSegmentStart, const Point2f &lineSegmentEnd) {
    cout << "Point (" << p.x << ", " << p.y << ") is between points ("
         << lineSegmentStart.x << ", " << lineSegmentStart.y << ") and ("
         << lineSegmentEnd.x << ", " << lineSegmentEnd.y << "): "
         << (Geometry2D::isPointOnLineSegment(p, lineSegmentStart, lineSegmentEnd) ? "true" : "false")
         << endl;
}

// Test if a point lies on a line segment
void testIfPointOnLineSegment() {
    testIfPointOnLineSegment(Point2f(2, 2), Point2f(2, 2), Point2f(10, 4));
    testIfPointOnLineSegment(Point2f(10, 4), Point2f(2, 2), Point2f(10, 4));
    testIfPointOnLineSegment(Point2f(6, 3), Point2f(2, 2), Point2f(10, 4));
    testIfPointOnLineSegment(Point2f(4, 3), Point2f(2, 2), Point2f(10, 4));
    testIfPointOnLineSegment(Point2f(6, 4), Point2f(2, 2), Point2f(10, 4));
}

// Main function
int main(int argc, char** argv) {
    try {
        testMinimumAreaEnclosingTriangle();
        // testIfPointOnLineSegment();
        // testAngleOfLine();
        // testIfAngleIsBetween();
        // testIfAngleOrOppositeIsBetween(30, 200, 250);
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}
