#ifndef UNTILLOGICPROPERTYTEST_HPP
#define UNTILLOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UntilLogicProperty

TEST(UntilLogicProperty, UntilOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) U [2, 3]]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputBeforeUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorBeforeUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputAfterUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorAfterUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeStartParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U ({A} >= 4) [A, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterStartParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, MissingTimepointsComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, A] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3.0] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, B] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3.0] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeEndParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3 ({A} >= 4) ] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterEndParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3] ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]"));
}

TEST(UntilLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]"));
}

#endif
