#ifndef UNARYSUBSETMEASURETEST_HPP
#define UNARYSUBSETMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnarySubsetMeasure

TEST(UnarySubsetMeasure, IncorrectUnarySubsetMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [number(clusters) <= 2]"), InvalidInputException);
}

TEST(UnarySubsetMeasure, CorrectCount) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(clusters) <= 2]"));
}

TEST(UnarySubsetMeasure, CorrectClusteredness) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [clusteredness(clusters) <= 2]"));
}

TEST(UnarySubsetMeasure, CorrectDensity) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [density(clusters) <= 2]"));
}

#endif
