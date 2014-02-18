#ifndef ORLOGICPROPERTYTEST_HPP
#define ORLOGICPROPERTYTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// OrLogicProperty

TEST(OrLogicProperty, OrOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, OrOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) V]"), InvalidInputException);
}

TEST(OrLogicProperty, IncorrectInputBeforeOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, AdditionalOperatorBeforeOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, IncorrectInputAfterOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) V ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, AdditionalOperatorAfterOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) V => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) V (count(regions) >= 4)]"));
}

TEST(OrLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) V (count(regions) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
}

#endif
