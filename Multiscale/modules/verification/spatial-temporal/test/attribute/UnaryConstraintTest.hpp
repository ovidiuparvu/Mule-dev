#ifndef UNARYCONSTRAINTTEST_HPP
#define UNARYCONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// UnaryConstraint

TEST(UnaryConstraint, IncorrectSpatialMeasureBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, area ^ perimeter <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, area 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, area >= )) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingComparatorNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, density)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingSpatialMeasureNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, >=)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputMissingSpatialMeasureComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, 4.4)) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, IncorrectInputEmptyConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ())) <= 3]"), InvalidInputException);
}

TEST(UnaryConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}

#endif
