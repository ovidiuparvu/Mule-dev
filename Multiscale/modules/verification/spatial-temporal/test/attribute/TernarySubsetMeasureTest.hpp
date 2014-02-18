#ifndef TERNARYSUBSETMEASURETEST_HPP
#define TERNARYSUBSETMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// TernarySubsetMeasure

TEST(TernarySubsetMeasure, IncorrectTernarySubsetMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [midtile(clusters, area, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubsetMeasure, CorrectPercentile) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"));
}

TEST(TernarySubsetMeasure, CorrectQuartile) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [quartile(clusters, area, 4.3) <= 0.5]"));
}

#endif
