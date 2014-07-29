#ifndef UNARYTYPECONSTRAINTTEST_HPP
#define UNARYTYPECONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnaryTypeConstraint

TEST(UnaryTypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, typee = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, ttype = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputBeforeTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, 0 ^ type = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type += 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type = type)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterFilterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, type >= 23 - 0.3)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, type = 0)) <= 3]"));
}

#endif
