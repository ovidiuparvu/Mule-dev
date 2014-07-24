#ifndef SUBSETOPERATIONTEST_HPP
#define SUBSETOPERATIONTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// SubsetOperation

TEST(SubsetOperation, IncorrectInputWrongSubsetOperationAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(multiplication(clusters, clusters)) <= 3]"), InvalidInputException);
}

TEST(SubsetOperation, CorrectDifference) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(difference(clusters, regions)) <= 3]"));
}

TEST(SubsetOperation, CorrectIntersection) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(intersection(clusters, regions)) <= 3]"));
}

TEST(SubsetOperation, CorrectUnion) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(union(clusters, regions)) <= 3]"));
}

#endif
