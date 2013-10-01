#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace multiscale;

const int KEY_ESC = 27;

const int RADIUS                    = 1;
const int LINE_THICKNESS            = 50;
const string WIN_MIN_AREA_TRIANGLE  = "Minimum area enclosing triangle";
const int NR_RAND_POLYGONS          = 50;
const int MAX_POLYGON_POINTS        = 100;
const int POLYGON_POINT_X_MAX       = 500;
const int POLYGON_POINT_Y_MAX       = 500;

const double POINT_IN_TRIANGLE_THRESH = 1E-4;


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

// Generate a new random set of points
vector<Point2f> generateRandomSetOf2DPoints(int nrOfPoints) {
    vector<Point2f> points;

    for (int i = 0; i < nrOfPoints; i++) {
        points.push_back(Point2f((rand() % POLYGON_POINT_X_MAX) + POLYGON_POINT_X_MAX,
                                 (rand() % POLYGON_POINT_Y_MAX) + POLYGON_POINT_Y_MAX));
    }

    return points;
}

// Print the polygon points
void printPolygon(const vector<Point2f> &points) {
    vector<Point2f> polygon;

    convexHull(points, polygon);

    // Print the polygon points
    cout << "Polygon points: ";

    for (const Point2f &point : polygon) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }

    cout << endl;
}

// Output the results for the minimum area enclosing triangle
void outputMinEnclosingTriangleFinderResults(const vector<Point2f> &minEnclosingTriangle, const vector<Point2f> &points) {
    Mat image = Mat::zeros(POLYGON_POINT_X_MAX * 3, POLYGON_POINT_Y_MAX * 3, CV_32FC3);
    Mat flippedImage = Mat::zeros(POLYGON_POINT_X_MAX * 3, POLYGON_POINT_Y_MAX * 3, CV_32FC3);

    // Draw minimum area enclosing triangle
    for (unsigned int i = 0; i < minEnclosingTriangle.size(); i++) {
        line(image, minEnclosingTriangle[i], minEnclosingTriangle[(i + 1) % minEnclosingTriangle.size()], Scalar(0, 255, 0), LINE_THICKNESS);
    }

    // Draw convex hull points
    for (const Point2f &point : points) {
        circle(image, point, RADIUS, Scalar(255, 0, 0), LINE_THICKNESS);
    }

    printPolygon(points);

    // Flip image wrt Ox axis and show it
    flip(image, flippedImage, 0);

    namedWindow(WIN_MIN_AREA_TRIANGLE, WINDOW_NORMAL);
    imshow(WIN_MIN_AREA_TRIANGLE, flippedImage);
}

// Check if all the points are enclosed by the minimal enclosing triangle
bool arePointsEnclosed(const vector<Point2f> &points, const vector<Point2f> &triangle) {
    double distance = 0;

    for (const Point2f &point : points) {
        distance = pointPolygonTest(triangle, point, true);

        if (distance < -(POINT_IN_TRIANGLE_THRESH)) {
            return false;
        }
    }

    return true;
}

// Check if all the triangle sides' middle points touch the convex hull of the given set of points
bool isTriangleTouchingPolygon(const vector<Point2f> &convexPolygon, const vector<Point2f> &triangle) {
    int nrOfPolygonPoints = convexPolygon.size();

    for (int i = 0; i < 3; i++) {
        bool isTouching = false;
        Point2f middlePoint = Geometry2D::middlePoint(triangle[i], triangle[(i + 1) % 3]);

        for (int j = 0; j < nrOfPolygonPoints; j++) {
            if (Geometry2D::isPointOnLineSegment(middlePoint, convexPolygon[j],
                                                 convexPolygon[(j + 1) % nrOfPolygonPoints])) {
                isTouching = true;
            }
        }

        if (!isTouching) {
            return false;
        }
    }

    return true;
}

// Check if at least one side of the triangle is flush with an edge of the polygon
bool isOneEdgeFlush(const vector<Point2f> &convexPolygon, const vector<Point2f> &triangle) {
    int nrOfPolygonPoints = convexPolygon.size();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < nrOfPolygonPoints; j++) {
            if ((Geometry2D::isPointOnLineSegment(convexPolygon[j], triangle[i],
                                                  triangle[(i + 1) % 3])) &&
                (Geometry2D::isPointOnLineSegment(convexPolygon[(j + 1) % nrOfPolygonPoints], triangle[i],
                                                  triangle[(i + 1) % 3]))) {
                return true;
            }
        }
    }

    return false;
}

// Check if the minimum enclosing triangle encloses all points
bool isValidTriangle(const vector<Point2f> &points, const vector<Point2f> &triangle) {
    vector<Point2f> convexPolygon;

    convexHull(points, convexPolygon, true);

    return (
        (arePointsEnclosed(points, triangle)) &&
        (isTriangleTouchingPolygon(convexPolygon, triangle)) &&
        (isOneEdgeFlush(convexPolygon, triangle))
    );
}

// Test the minimum area enclosing triangle algorithm
void testMinEnclosingTriangleFinder(const vector<Point2f> &points) {
    vector<Point2f> minEnclosingTriangle;
    double area = 0;

    // Find the minimum area enclosing triangle
    area = MinEnclosingTriangleFinder().find(points, minEnclosingTriangle);

    // Validate the found triangle
    assert(isValidTriangle(points, minEnclosingTriangle));

    cout << "The area of the minimum area enclosing triangle is: " << area << endl;

    outputMinEnclosingTriangleFinderResults(minEnclosingTriangle, points);
}

// Test the minimum area enclosing triangle algorithm using randomly generated sets of points
void testMinEnclosingTriangleFinderUsingRandomPolygons() {
    char key = 0;

    // Initialise the seed - milliseconds is enough as this program is not to be run in parallel
    srand(time(0));

    while (key != KEY_ESC) {
        int nrOfPoints = rand() % MAX_POLYGON_POINTS;

        nrOfPoints = (nrOfPoints == 0) ? 1
                                       : nrOfPoints;

        vector<Point2f> points = generateRandomSetOf2DPoints(nrOfPoints);

        testMinEnclosingTriangleFinder(points);

        key = waitKey();
    }
}

// Test the minimum area enclosing triangle algorithm
void testMinEnclosingTriangleFinder() {
    // testMinEnclosingTriangleFinder(vector<Point2f>{Point2f(-1, 0), Point2f(3, -6), Point2f(-7, -5)});
    // testMinEnclosingTriangleFinder(vector<Point2f>{Point2f(3, -6), Point2f(-7, -5)});
    // testMinEnclosingTriangleFinder(vector<Point2f>{Point2f(-7, -5)});
    // testMinEnclosingTriangleFinder(vector<Point2f>{});

    testMinEnclosingTriangleFinderUsingRandomPolygons();
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
        testMinEnclosingTriangleFinder();
        // testIfPointOnLineSegment();
        // testAngleOfLine();
        // testIfAngleIsBetween();
        // testIfAngleOrOppositeIsBetween(30, 200, 250);
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}
