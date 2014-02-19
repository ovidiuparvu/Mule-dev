#ifndef NUMERICSPATIALNUMERICCOMPARISONTEST_HPP
#define NUMERICSPATIALNUMERICCOMPARISONTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// NumericSpatialNumericComparison

TEST(NumericSpatialNumericComparison, NumericMeasureFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 >= d(4)]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, NumericMeasureFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 d(4) >=]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, ComparatorFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4 d(4)]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, ComparatorFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= d(4) 4]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, IncorrectOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(4) 4 >=]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [clusteredness(clusters) >= 4.2]"));
}

#endif
