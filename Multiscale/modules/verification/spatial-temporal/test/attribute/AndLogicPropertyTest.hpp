#ifndef ANDLOGICPROPERTYTEST_HPP
#define ANDLOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// AndLogicProperty

TEST(AndLogicProperty, AndOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AndOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) ^]"), InvalidInputException);
}

TEST(AndLogicProperty, IncorrectInputBeforeAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) ^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AdditionalOperatorBeforeAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ ^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, IncorrectInputAfterAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ^ ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AdditionalOperatorAfterAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ^ => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) ^ (count(regions) >= 4)]"));
}

TEST(AndLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) ^ (count(regions) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
}

#endif
