#ifndef CONSTRAINTTEST_HPP
#define CONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Constraint

TEST(Constraint, ExtraInputBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, area, perimeter <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(Constraint, ExtraInputAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2, true)) <= 3]"), InvalidInputException);
}

TEST(Constraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}

#endif
