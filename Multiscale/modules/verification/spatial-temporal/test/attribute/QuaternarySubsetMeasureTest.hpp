#ifndef QUATERNARYSUBSETMEASURETEST_HPP
#define QUATERNARYSUBSETMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// QuaternarySubsetMeasure

TEST(QuaternarySubsetMeasure, IncorrectQuaternarySubsetMeasure) {
	EXPECT_THROW(parseInputString("P >= 0.3 [correlation(clusters, area, regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, CorrectCovar) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"));
}

#endif
