#ifndef NOTCONSTRAINTTEST_HPP
#define NOTCONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NotConstraint

TEST(NotConstraint, IncorrectOperator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, !(perimeter <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) ~)) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) (area = 2.4) ~)) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorBeforeConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2) (area = 2.4))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]"));
}

#endif
