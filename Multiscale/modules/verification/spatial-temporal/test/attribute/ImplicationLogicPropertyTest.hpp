#ifndef IMPLICATIONLOGICPROPERTYTEST_HPP
#define IMPLICATIONLOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// ImplicationLogicProperty

TEST(ImplicationLogicProperty, ImplicationOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, ImplicationOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) =>]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, IncorrectInputBeforeImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, AdditionalOperatorBeforeImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, IncorrectInputAfterImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) => ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, AdditionalOperatorAfterImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) => V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) => (count(regions) >= 4)]"));
}

TEST(ImplicationLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) => (count(regions) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
}

#endif
