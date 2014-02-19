#ifndef NUMERICNUMERICCOMPARISONTEST_HPP
#define NUMERICNUMERICCOMPARISONTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NumericNumericComparison

TEST(NumericNumericComparison, NumericMeasureFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 >= {A}"), InvalidInputException);
}

TEST(NumericNumericComparison, NumericMeasureFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 {A} >=]"), InvalidInputException);
}

TEST(NumericNumericComparison, ComparatorFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4 {A}]"), InvalidInputException);
}

TEST(NumericNumericComparison, ComparatorFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= {A} 4]"), InvalidInputException);
}

TEST(NumericNumericComparison, IncorrectOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} 4 >=]"), InvalidInputException);
}

TEST(NumericNumericComparison, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} >= 4.2]"));
}

#endif
