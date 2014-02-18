#ifndef UNARYSUBSETTEST_HPP
#define UNARYSUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnarySubset

TEST(UnarySubset, IncorrectInputNoSubset) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count() <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputBeforeStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count [ (clusters) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputAfterStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count( [ clusters) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputBeforeEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(clusters } ) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputAfterEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(clusters ) } <= 2]"), InvalidInputException);
}

TEST(UnarySubset, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(clusters) <= 2]"));
}

#endif
