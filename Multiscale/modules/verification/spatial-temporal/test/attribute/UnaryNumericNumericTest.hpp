#ifndef UNARYNUMERICNUMERICTEST_HPP
#define UNARYNUMERICNUMERICTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnaryNumericNumeric

TEST(UnaryNumericNumeric, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs()]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs 2(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(2 3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3 2)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3) 2]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= abs(3.0)]"));
}

#endif
