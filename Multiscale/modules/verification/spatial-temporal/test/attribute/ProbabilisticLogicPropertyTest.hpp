#ifndef PROBABILISTICLOGICPROPERTYTEST_HPP
#define PROBABILISTICLOGICPROPERTYTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// ProbabilisticLogicProperty

TEST(ProbabilisticLogicProperty, IncorrectProbabilitySymbol) {
	EXPECT_THROW(parseInputString("PT >= 0.3 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectComparator) {
	EXPECT_THROW(parseInputString("P > 0.3 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLow) {
	EXPECT_THROW(parseInputString("P >= -0.1 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLowMinor) {
	EXPECT_THROW(parseInputString("P >= -0.000000001 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHigh) {
	EXPECT_THROW(parseInputString("P >= 2.9 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHighMinor) {
	EXPECT_THROW(parseInputString("P >= 1.000000001 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [T]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftMissing) {
	EXPECT_THROW(parseInputString("P >= 0.3 count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightMissing) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftRightExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[count(regions) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesInverted) {
	EXPECT_THROW(parseInputString("P >= 0.3 ]count(regions) >= 2["), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesClosing) {
	EXPECT_THROW(parseInputString("P >= 0.3 []count(regions) >= 2[]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParantheses) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[[count(regions) >= 2]][]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMin) {
	EXPECT_TRUE(parseInputString("P >= 0.0 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMax) {
	EXPECT_TRUE(parseInputString("P >= 1.0 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityLow) {
	EXPECT_TRUE(parseInputString("P >= 0.00000001 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityHigh) {
	EXPECT_TRUE(parseInputString("P >= 0.99999999 [count(regions) >= 2]"));
}

#endif
