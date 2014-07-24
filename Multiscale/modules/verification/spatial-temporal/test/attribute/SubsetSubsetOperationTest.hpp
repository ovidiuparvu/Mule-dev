#ifndef SUBSETSUBSETOPERATIONTEST_HPP
#define SUBSETSUBSETOPERATIONTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// SubsetSubsetOperation

TEST(SubsetSubsetOperation, IncorrectInputWrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(division(clusters, clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union2(clusters, clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(regions V clusters, clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingFirstArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(, clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSeparatorComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(regions clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingCommaAndArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSecondArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(regions, )) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(regions, clusters => regions)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(regions, clusters) [0, 10]) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(union(clusters, regions)) <= 3]"));
}

#endif
