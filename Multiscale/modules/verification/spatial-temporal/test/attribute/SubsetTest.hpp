#ifndef SUBSETTEST_HPP
#define SUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Subset

TEST(Subset, IncorrectInputWrongSubsetAlternativeRegion) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(region) <= 3]"), InvalidInputException);
}

TEST(Subset, IncorrectInputWrongSubsetAlternativeCluster) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(cluster) <= 3]"), InvalidInputException);
}

TEST(Subset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(clusters) <= 3]"));
}

#endif
