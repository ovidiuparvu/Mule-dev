#ifndef LOGICPROPERTYTEST_HPP
#define LOGICPROPERTYTEST_HPP

#include "parsing/ParseInputString.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// LogicProperty

TEST(LogicProperty, ExtraInputBeforeLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [aaa count(regions) >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputInsideLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) aaa >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputAfterLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2 aaa]"), InvalidInputException);
}

TEST(LogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(regions) >= 2]"));
}

#endif
