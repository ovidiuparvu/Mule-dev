#ifndef TERNARYSUBSETTEST_HPP
#define TERNARYSUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// TernarySubset

TEST(TernarySubset, IncorrectInputMissingParameterOne) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(area, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParameterTwo) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParameterThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, area) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersOneTwo) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersOneThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(area) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersTwoThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingAllParameters) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile() <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputBeforeStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile ^ quartile(clusters, area, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputAfterStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile ( _ clusters, area, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, MissingFirstComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters area, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, InvalidSpatialMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, height, 4.3) <= 2]"), InvalidInputException);
}

TEST(TernarySubset, MissingSecondComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, area 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputBeforeEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5, 1.2]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputAfterEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [percentile(clusters, area 4.3) V true <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"));
}

#endif
