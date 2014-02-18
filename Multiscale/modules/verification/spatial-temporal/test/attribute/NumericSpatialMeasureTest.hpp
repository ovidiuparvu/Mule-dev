#ifndef NUMERICSPATIALMEASURETEST_HPP
#define NUMERICSPATIALMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NumericSpatialMeasure

TEST(NumericSpatialMeasure, IncorrectAlternative) {
	EXPECT_THROW(parseInputString("P >= 0.3 [regions <= add a(2, 3)]"), InvalidInputException);
}

TEST(NumericSpatialMeasure, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(regions, area) <= add(2, 3)]"));
}

#endif
