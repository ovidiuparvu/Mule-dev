#ifndef LOGICPROPERTYPARENTHESESTEST_HPP
#define LOGICPROPERTYPARENTHESESTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// LogicProperty enclosed by parentheses

TEST(LogicPropertyEnclosedByParentheses, MissingParenthesisRight) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, MissingParenthesisLeft) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} >= 4)]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesisLeft) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(({A} >= 4)]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesisRight) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, InvertedParentheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [){A} >= 4(]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesesBothSides) {
    EXPECT_THROW(parseInputString("P >= 0.3 [((((({A} >= 4)))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ParenthesesInWrongOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [((())(({A} >= 4)))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4)]"));
}

TEST(LogicPropertyEnclosedByParentheses, CorrectDoubled) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [(({A} >= 4))]"));
}

TEST(LogicPropertyEnclosedByParentheses, CorrectQuadrupled) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [(((({A} >= 4))))]"));
}

#endif
