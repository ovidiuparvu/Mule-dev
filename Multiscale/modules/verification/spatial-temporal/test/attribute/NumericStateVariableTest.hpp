#ifndef NUMERICSTATEVARIABLETEST_HPP
#define NUMERICSTATEVARIABLETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NumericStateVariable

TEST(NumericStateVariable, MissingLeftCurlyBrace) {
	EXPECT_THROW(parseInputString("P >= 0.3 [A} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingRightCurlyBrace) {
	EXPECT_THROW(parseInputString("P >= 0.3 [{A <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, ExtraLeftCurlyBrace) {
	EXPECT_THROW(parseInputString("P >= 0.3 [{{A} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, ExtraRightCurlyBrace) {
	EXPECT_THROW(parseInputString("P >= 0.3 [{A}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, InvertedCurlyBraces) {
	EXPECT_THROW(parseInputString("P >= 0.3 [}A{ <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, DoubleCurlyBraces) {
	EXPECT_THROW(parseInputString("P >= 0.3 [{{A}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, TripleCurlyBraces) {
	EXPECT_THROW(parseInputString("P >= 0.3 [{{{A}}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= 3]"));
}

#endif
