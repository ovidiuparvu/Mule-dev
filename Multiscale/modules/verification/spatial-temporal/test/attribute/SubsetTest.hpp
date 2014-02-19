#ifndef SUBSETTEST_HPP
#define SUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Subset

TEST(Subset, IncorrectInputWrongSubsetAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [clusters <= 3]"), InvalidInputException);
}

TEST(Subset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(clusters) <= 3]"));
}

#endif
