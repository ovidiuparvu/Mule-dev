#ifndef BINARYSUBSETTEST_HPP
#define BINARYSUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// BinarySubset

TEST(BinarySubset, IncorrectMissingFirstParameter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(area) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectMissingSecondParameter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(clusters) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectMissingParameters) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean() <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputBeforeStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean T (clusters, area) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputAfterStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean ( regions V clusters, area) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, MissingComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(clusters area) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, InvalidSpatialMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(clusters, height) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputBeforeEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(clusters, area true) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputAfterEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean(clusters, area) ^ geomean(clusters, area) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(clusters, area) <= 2]"));
}

#endif
