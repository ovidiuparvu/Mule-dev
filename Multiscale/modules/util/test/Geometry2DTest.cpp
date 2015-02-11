#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <limits>
#include <vector>

using namespace multiscale;
using namespace multiscaletest;

const double DOUBLE_COMP_ERROR = 1E-6;


///////////////////////////////////////////////////////////////////////////////
//
// Tests
//
///////////////////////////////////////////////////////////////////////////////

TEST(Geometry2D, TangentsFromPointToPolygon) {
    std::vector<cv::Point2f> convexPolygon(
        { cv::Point2f(23, 32), cv::Point2f(22, 34), cv::Point2f(21, 34), cv::Point2f(23, 31) }
    );

    cv::Point2f referencePoint(25, 25);

    // Find the tangents from the reference point to the convex polygon
    cv::Point2f leftMostTangentPoint;
    cv::Point2f rightMostTangentPoint;

    Geometry2D::tangentsFromPointToPolygon(
        convexPolygon, referencePoint, leftMostTangentPoint, rightMostTangentPoint
    );

    // Check if the obtained tangent points are the expected ones
    EXPECT_NEAR(leftMostTangentPoint.x, 21, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(leftMostTangentPoint.y, 34, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.x, 23, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.y, 32, DOUBLE_COMP_ERROR);
}

TEST(Geometry2D, TangentsFromPointToPolygonReferenceAndTangentPointsAreCollinearWithPolygonPoint) {
    std::vector<cv::Point2f> convexPolygon(
        { cv::Point2f(9, 42), cv::Point2f(7, 44), cv::Point2f(6, 44), cv::Point2f(4, 42), cv::Point2f(7, 40) }
    );

    cv::Point2f referencePoint(25.5, 25.5);

    // Find the tangents from the reference point to the convex polygon
    cv::Point2f leftMostTangentPoint;
    cv::Point2f rightMostTangentPoint;

    Geometry2D::tangentsFromPointToPolygon(
        convexPolygon, referencePoint, leftMostTangentPoint, rightMostTangentPoint
    );

    // Check if the obtained tangent points are the expected ones
    EXPECT_NEAR(leftMostTangentPoint.x, 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(leftMostTangentPoint.y, 42, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.x, 9, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.y, 42, DOUBLE_COMP_ERROR);
}

TEST(Geometry2D, TangentsFromPointToLargerPolygonReferenceAndTangentPointsAreCollinearWithPolygonPoint) {
    std::vector<cv::Point2f> convexPolygon(
        { cv::Point2f(35, 28), cv::Point2f(31, 32), cv::Point2f(29, 32), cv::Point2f(27, 30), cv::Point2f(26, 25),
          cv::Point2f(27, 24), cv::Point2f(34, 24), cv::Point2f(35, 25) }
    );

    cv::Point2f referencePoint(25.5, 25.5);

    // Find the tangents from the reference point to the convex polygon
    cv::Point2f leftMostTangentPoint;
    cv::Point2f rightMostTangentPoint;

    Geometry2D::tangentsFromPointToPolygon(
        convexPolygon, referencePoint, leftMostTangentPoint, rightMostTangentPoint
    );

    // Check if the obtained tangent points are the expected ones
    EXPECT_NEAR(leftMostTangentPoint.x, 27, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(leftMostTangentPoint.y, 30, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.x, 26, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.y, 25, DOUBLE_COMP_ERROR);
}

TEST(Geometry2D, TangentsFromPointToPolygonFirstPointRightMostTangentPoint) {
    std::vector<cv::Point2f> convexPolygon(
        { cv::Point2f(9, 42), cv::Point2f(7, 44), cv::Point2f(6, 44), cv::Point2f(4, 42), cv::Point2f(7, 40) }
    );

    cv::Point2f referencePoint(25.5, 25.5);

    // Find the tangents from the reference point to the convex polygon
    cv::Point2f leftMostTangentPoint;
    cv::Point2f rightMostTangentPoint;

    Geometry2D::tangentsFromPointToPolygon(
        convexPolygon, referencePoint, leftMostTangentPoint, rightMostTangentPoint
    );

    // Check if the obtained tangent points are the expected ones
    EXPECT_NEAR(leftMostTangentPoint.x, 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(leftMostTangentPoint.y, 42, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.x, 9, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(rightMostTangentPoint.y, 42, DOUBLE_COMP_ERROR);
}

TEST(Geometry2D, PointOnLineSegment) {
    EXPECT_TRUE(Geometry2D::isPointOnLineSegment(cv::Point2f(2, 2), cv::Point2f(2, 2), cv::Point2f(10, 4)));
    EXPECT_TRUE(Geometry2D::isPointOnLineSegment(cv::Point2f(10, 4), cv::Point2f(2, 2), cv::Point2f(10, 4)));
    EXPECT_TRUE(Geometry2D::isPointOnLineSegment(cv::Point2f(6, 3), cv::Point2f(2, 2), cv::Point2f(10, 4)));
    EXPECT_FALSE(Geometry2D::isPointOnLineSegment(cv::Point2f(4, 3), cv::Point2f(2, 2), cv::Point2f(10, 4)));
    EXPECT_FALSE(Geometry2D::isPointOnLineSegment(cv::Point2f(6, 4), cv::Point2f(2, 2), cv::Point2f(10, 4)));
}

TEST(Geometry2D, TriangleArea) {
    EXPECT_NEAR(0, Geometry2D::areaOfTriangle(cv::Point2f(1, 2), cv::Point2f(2, 3), cv::Point2f(3, 4)),
                DOUBLE_COMP_ERROR);
    EXPECT_NEAR(9.5, Geometry2D::areaOfTriangle(cv::Point2f(5, 2), cv::Point2f(2, 3), cv::Point2f(3, 9)),
                DOUBLE_COMP_ERROR);
    EXPECT_NEAR(3.7, Geometry2D::areaOfTriangle(cv::Point2f(5, 5), cv::Point2f(2.4, 0), cv::Point2f(3, 4)),
                DOUBLE_COMP_ERROR);
    EXPECT_NEAR(24.5, Geometry2D::areaOfTriangle(cv::Point2f(0, 4.9), cv::Point2f(0, 0), cv::Point2f(10, 10)),
                DOUBLE_COMP_ERROR);
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
