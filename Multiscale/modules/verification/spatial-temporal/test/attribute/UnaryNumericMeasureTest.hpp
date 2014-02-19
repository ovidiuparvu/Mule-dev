#ifndef UNARYNUMERICMEASURETEST_HPP
#define UNARYNUMERICMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnaryNumericMeasure

TEST(UnaryNumericMeasure, IncorrectUnaryNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [density(regions) <= frac(count(clusters))]"), InvalidInputException);
}

TEST(UnaryNumericMeasure, CorrectAbs) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= abs(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectCeil) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= ceil(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectFloor) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= floor(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectRound) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= round(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectSign) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= sign(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectSqrt) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= sqrt(count(clusters))]"));
}

TEST(UnaryNumericMeasure, CorrectTrunc) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [density(regions) <= trunc(count(clusters))]"));
}

#endif
