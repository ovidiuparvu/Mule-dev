#ifndef DIFFERENCETEST_HPP
#define DIFFERENCETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Difference

TEST(Difference, IncorrectDifferenceSymbol) {
	EXPECT_THROW(parseInputString("P >= 0.3 [df(4) >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectOpeningBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [d[4) >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectClosingBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [d(4] >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBrackets) {
	EXPECT_THROW(parseInputString("P >= 0.3 [d[4] >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBracketsInverted) {
	EXPECT_THROW(parseInputString("P >= 0.3 [d)4( >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBracketsDoubled) {
	EXPECT_THROW(parseInputString("P >= 0.3 [d((4)) >= 4]"), InvalidInputException);
}

TEST(Difference, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [d(4) >= 4]"));
}

#endif
