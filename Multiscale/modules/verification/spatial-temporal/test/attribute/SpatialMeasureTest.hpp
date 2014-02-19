#ifndef SPATIALMEASURETEST_HPP
#define SPATIALMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// SpatialMeasure


TEST(SpatialMeasure, IncorrectSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, height <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(SpatialMeasure, CorrectClusteredness) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectDensity) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, density <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectArea) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, area <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectPerimeter) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectDistanceFromOrigin) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectAngle) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, angle <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectTriangleMeasure) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectRectangleMeasure) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectCircleMeasure) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectCentroidX) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) <= 3]"));
}

TEST(SpatialMeasure, CorrectCentroidY) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) <= 3]"));
}

#endif
