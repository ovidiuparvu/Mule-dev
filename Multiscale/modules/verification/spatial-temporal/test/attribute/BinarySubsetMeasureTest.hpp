#ifndef BINARYSUBSETMEASURETEST_HPP
#define BINARYSUBSETMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// BinarySubsetMeasure

TEST(BinarySubsetMeasure, IncorrectBinarySubsetMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [arithmeticmean(clusters, area) ^ geomean(clusters, area) <= 2]"), InvalidInputException);
}

TEST(BinarySubsetMeasure, CorrectAvg) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [avg(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectGeomean) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectHarmean) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [harmean(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectKurt) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [kurt(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMax) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [max(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMedian) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [median(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMin) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [min(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMode) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [mode(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectProduct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [product(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectSkew) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [skew(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectStdev) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [stdev(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectSum) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [sum(clusters, area) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectVar) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [var(clusters, area) <= 2]"));
}

#endif
