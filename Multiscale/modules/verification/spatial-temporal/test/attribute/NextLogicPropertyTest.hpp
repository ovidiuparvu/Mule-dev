#ifndef NEXTLOGICPROPERTYTEST_HPP
#define NEXTLOGICPROPERTYTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NextLogicProperty

TEST(NextLogicProperty, IncorrectInputAfterNextSymbol) {
	EXPECT_THROW(parseInputString("P >= 0.3 [X {B} ({A} >= 4)]"), InvalidInputException);
}

TEST(NextLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [X ({A} >= 4)]"));
}

#endif
