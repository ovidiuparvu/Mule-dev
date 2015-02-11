#include "multiscale/util/Geometry2D.hpp"

#include <iostream>

using namespace multiscale;


// Print the points from the std::vector

void printPoints(const std::vector<cv::Point2f> &points) {
    std::cout << "=========== cv::Points ===========" << std::endl;

    for (const cv::Point2f &point : points) {
        std::cout << point.x << " " << point.y << std::endl;
    }
}

// Main function

int main() {
    std::vector<cv::Point2f> intersectionPoints;

    Geometry2D::lineSegmentCircleIntersection(
        cv::Point(4, 4), cv::Point(4, 5), cv::Point(5, 5), 2, intersectionPoints
    );
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineSegmentCircleIntersection(
        cv::Point(5, 4), cv::Point(4, 5), cv::Point(5, 5), 2, intersectionPoints
    );
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineCircleIntersection(
        cv::Point(4, 4), cv::Point(4, 5), cv::Point(5, 5), 1, intersectionPoints
    );
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    Geometry2D::lineCircleIntersection(
        cv::Point(4, 4), cv::Point(4, 5), cv::Point(5, 5), 0.5, intersectionPoints
    );
    printPoints(intersectionPoints);

    intersectionPoints.clear();

    return EXEC_SUCCESS_CODE;
}
