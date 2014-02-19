#ifndef GLOBALLOGICPROPERTYTEST_HPP
#define GLOBALLOGICPROPERTYTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// GlobalLogicProperty

TEST(GlobalLogicProperty, WrongInputMissingStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimepointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4) [2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [ ({A} >= 4) 2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, MissingTimepointComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2.3, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3 ({A} >= 4)] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3] ({A} >= 4) ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [G [2, 3] ({A} >= 4)]"));
}

#endif
