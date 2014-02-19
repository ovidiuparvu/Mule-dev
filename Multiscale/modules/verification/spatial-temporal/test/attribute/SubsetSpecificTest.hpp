#ifndef SUBSETSPECIFICTEST_HPP
#define SUBSETSPECIFICTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// SubsetSpecific

TEST(SubsetSpecific, IncorrectInputWrongSubsetAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(groups) <= 3]"), InvalidInputException);
}

TEST(SubsetSpecific, CorrectClusters) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(clusters) <= 3]"));
}

TEST(SubsetSpecific, CorrectRegions) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(regions) <= 3]"));
}

#endif
