#ifndef FILTERSUBSETTEST_HPP
#define FILTERSUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// FilterSubset

TEST(FilterSubset, IncorrectInputMisspelledFilter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(fillter[(clusters, area >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter[(clusters, area >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(regions, clusters, area >= 4.3) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputMissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters area >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, area >= 4.3, area <= 2)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(regions, clusters)) = 2 V <= 3]"), InvalidInputException);
}

TEST(FilterSubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]"));
}

#endif
