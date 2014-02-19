#ifndef CONSTRAINTPARENTHESESTEST_HPP
#define CONSTRAINTPARENTHESESTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Constraint enclosed by parentheses

TEST(ConstraintEnclosedByParentheses, MissingParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, MissingParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2)))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, InvertedParentheses) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, )perimeter <= 30.2()) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesesBothSides) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (((perimeter <= 30.2))))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ParenthesesInWrongOrder) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (((())(perimeter <= 30.2))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectDoubled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2)))) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectQuadrupled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, ((((perimeter <= 30.2)))))) <= 3]"));
}

#endif
