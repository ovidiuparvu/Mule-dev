#ifndef COMPARATORTEST_HPP
#define COMPARATORTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Comparator

TEST(Comparator, IncorrectEqual) {
	EXPECT_THROW(parseInputString("P <= 0.9 [count(regions) == 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent1) {
	EXPECT_THROW(parseInputString("P <= 0.9 [count(regions) <> 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent2) {
	EXPECT_THROW(parseInputString("P <= 0.9 [count(regions) != 3]"), InvalidInputException);
}

TEST(Comparator, CorrectGreaterThan) {
	EXPECT_TRUE(parseInputString("P <= 0.9 [count(regions) > 3]"));
}

TEST(Comparator, CorrectLessThan) {
	EXPECT_TRUE(parseInputString("P <= 0.9 [count(regions) < 3]"));
}

TEST(Comparator, CorrectGreaterThanOrEqual) {
	EXPECT_TRUE(parseInputString("P <= 0.9 [count(regions) >= 3]"));
}

TEST(Comparator, CorrectLessThanOrEqual) {
	EXPECT_TRUE(parseInputString("P <= 0.9 [count(regions) <= 3]"));
}

TEST(Comparator, CorrectEqual) {
	EXPECT_TRUE(parseInputString("P <= 0.9 [count(regions) = 3]"));
}

#endif
