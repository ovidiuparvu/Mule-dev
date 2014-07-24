#ifndef TYPECONSTRAINTTEST_HPP
#define TYPECONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// TypeConstraint

TEST(TypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, typee = 0)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, ttype = 0)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, IncorrectInputBeforeTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, 0 ^ type = 0)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, IncorrectInputAfterTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type += 0)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, IncorrectInputAfterComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type = type)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, IncorrectInputAfterFilterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type >= 23 - 0.3)) <= 3]"), InvalidInputException);
}

TEST(TypeConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, type = 0)) <= 3]"));
}

#endif
