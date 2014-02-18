#ifndef NOTLOGICPROPERTYTEST_HPP
#define NOTLOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NotLogicProperty

TEST(NotLogicProperty, OperatorAfterLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorAfterLogicPropertyAndExtraLogicPorperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~ ({B} 4 >=)]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorBeforeLogicPropertyAndExtraLogicPorperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [~ ({A} 4 >=) ({B} 4 >=)]"), InvalidInputException);
}

TEST(NotLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [~({A} >= 4.2)]"));
}

#endif
