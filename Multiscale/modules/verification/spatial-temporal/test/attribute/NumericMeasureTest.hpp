#ifndef NUMERICMEASURETEST_HPP
#define NUMERICMEASURETEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NumericMeasure

TEST(NumericMeasure, WrongAlternative) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean]"), InvalidInputException);
}

TEST(NumericMeasure, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [(count(clusters) >= 4)]"));
}

#endif
