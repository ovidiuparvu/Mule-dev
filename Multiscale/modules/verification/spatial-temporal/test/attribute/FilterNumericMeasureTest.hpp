#ifndef FILTERNUMERICMEASURETEST_HPP
#define FILTERNUMERICMEASURETEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// FilterNumericMeasure

TEST(FilterSubset, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(clusters, d(count(regions)) >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, CorrectSpatialMeasureRealValue) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]"));
}

TEST(FilterSubset, CorrectSpatialMeasures) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, area >= perimeter)) <= 3]"));
}

TEST(FilterSubset, CorrectMultiple) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, area >= 4.3 ^ perimeter < 2)) <= 3]"));
}

TEST(FilterSubset, CorrectMultipleComplex) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(clusters, area >= sqrt(add(power(subtract(10, centroidX), 2), power(subtract(10, centroidY), 2))))) <= 3]"));
}

#endif
