#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/MinimumAreaEnclosingTriangle.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace multiscale;

#define RADIUS                  2
#define WIN_MIN_AREA_TRIANGLE   "Minimum area enclosing triangle"


// Compute the area of a triangle specified by three points
void testAreaOfTriangle(const Point &a, const Point &b, const Point &c) {
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
void testAngleOfLine(const Point &a, const Point &b) {
    cout << "The angle of the line determined by the points "
         << "(" << a.x << ", " << a.y << ") and "
         << "(" << b.x << ", " << b.y << ") is: "
         << Geometry2D::angleOfLineWrtOxAxis(a, b) << endl;
}

// Compute the angle of the line specified by two points
void testAngleOfLine() {
    testAngleOfLine(Point(0, 0), Point(2, 2)); // 0.785398163
    testAngleOfLine(Point(1, 2), Point(8, 4)); // 0.278285768
    testAngleOfLine(Point(0, 0), Point(0, 2)); // 1.57079633
    testAngleOfLine(Point(-1, 7), Point(2, 2)); // 2.11050995
    testAngleOfLine(Point(2, 0), Point(0, 0)); // 3.14
    testAngleOfLine(Point(0, 0), Point(2, 0)); // 0
}

// Output the results for the minimum area enclosing triangle
void outputMinimumAreaEnclosingTriangleResults(const vector<Point> &minimumAreaEnclosingTriangle, vector<Point> &convexHullResult) {
    Mat image(50, 50, CV_32FC3);

    // Draw convex hull points
    for (Point &point : convexHullResult) {
        circle(image, point, RADIUS, Scalar(255, 0, 0));
    }

    // Draw minimum area enclosing triangle
    for (unsigned int i = 0; i < minimumAreaEnclosingTriangle.size(); i++) {
        line(image, minimumAreaEnclosingTriangle[i], minimumAreaEnclosingTriangle[(i + 1) % minimumAreaEnclosingTriangle.size()], Scalar(0, 255, 0));
    }

    namedWindow(WIN_MIN_AREA_TRIANGLE, WINDOW_NORMAL);
    imshow(WIN_MIN_AREA_TRIANGLE, image);

    waitKey();
}

// Test the minimum area enclosing triangle algorithm
void testMinimumAreaEnclosingTriangle(const vector<Point> &polygon) {
    vector<Point> minimumAreaEnclosingTriangle;
    double area = 0;

    // Get convex hull of polygon
    vector<Point> convexHullResult;

    convexHull(polygon, convexHullResult, true, true);

    // Find the minimum area enclosing triangle
    MinimumAreaEnclosingTriangle::find(convexHullResult, minimumAreaEnclosingTriangle, area);

    assert(minimumAreaEnclosingTriangle.size() == 3);

    cout << "The area of the minimum area enclosing triangle is: " << area << endl;

    outputMinimumAreaEnclosingTriangleResults(minimumAreaEnclosingTriangle, convexHullResult);
}

// Test the minimum area enclosing triangle algorithm
void testMinimumAreaEnclosingTriangle() {
    testMinimumAreaEnclosingTriangle(vector<Point>{Point(2, 2), Point(2, 6), Point(5, 2), Point(5, 6)});
    testMinimumAreaEnclosingTriangle(vector<Point>{Point(5, 24), Point(9, 10), Point(7, 38), Point(15, 18), Point(15, 44), Point(22, 14), Point(19, 38), Point(29, 18), Point(39, 30)});
}

// Main function
int main(int argc, char** argv) {
    try {
        testMinimumAreaEnclosingTriangle();
        // testAngleOfLine();
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}
