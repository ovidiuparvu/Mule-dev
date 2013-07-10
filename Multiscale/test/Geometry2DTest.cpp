#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace std;
using namespace multiscale;


// Compute the area of a triangle specified by three points
void testAreaOfTriangle() {
    cout << Geometry2D::areaOfTriangle(Point2f(1, 2), Point2f(2, 3), Point2f(3, 4)) << endl; // 0
    cout << Geometry2D::areaOfTriangle(Point2f(5, 2), Point2f(2, 3), Point2f(3, 9)) << endl; // 9.5
    cout << Geometry2D::areaOfTriangle(Point2f(5, 5), Point2f(2.4, 0), Point2f(3, 4)) << endl; // 3.7
    cout << Geometry2D::areaOfTriangle(Point2f(0, 4.9), Point2f(0, 0), Point2f(10, 10)) << endl; // 24.5
}

// Main function
int main(int argc, char** argv) {
    testAreaOfTriangle();

    return 0;
}
