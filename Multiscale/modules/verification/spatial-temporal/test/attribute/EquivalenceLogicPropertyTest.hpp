#ifndef EQUIVALENCELOGICPROPERTYTEST_HPP
#define EQUIVALENCELOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// EquivalenceLogicProperty

TEST(EquivalenceLogicProperty, EquivalenceOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [<=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, EquivalenceOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) <=>]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, IncorrectInputBeforeEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) <=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, AdditionalOperatorBeforeEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ <=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, IncorrectInputAfterEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) <=> ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, AdditionalOperatorAfterEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) <=> V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) <=> (count(regions) >= 4)]"));
}

TEST(EquivalenceLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) <=> (count(regions) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}

#endif
