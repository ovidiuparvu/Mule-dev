#ifndef NUMERICSTATEVARIABLETRACETEST_HPP
#define NUMERICSTATEVARIABLETRACETEST_HPP

#include "parsing/InputStringParserAndEvaluator.hpp"

// TODO: Remove
#include <iostream>

using namespace multiscale;
using namespace multiscaletest::verification;


// The spatial temporal trace used for this unit test

SpatialTemporalTrace getNumericStateVariableTrace() {
    SpatialTemporalTrace trace;

    // Initialise trace
    std::vector<TimePoint> timePoints = std::vector<TimePoint>(11);

    for (int i = 0; i <= 10; i++) {
        timePoints[i].addNumericStateVariable("B", 3);
    }

    timePoints[0].addNumericStateVariable("A", 4);
    timePoints[1].addNumericStateVariable("A", 5);
    timePoints[2].addNumericStateVariable("A", 6);
    timePoints[3].addNumericStateVariable("A", 10);
    timePoints[4].addNumericStateVariable("A", 8);
    timePoints[5].addNumericStateVariable("A", 6);
    timePoints[6].addNumericStateVariable("A", 4);
    timePoints[7].addNumericStateVariable("A", 1);
    timePoints[8].addNumericStateVariable("A", 5);
    timePoints[9].addNumericStateVariable("A", 7);
    timePoints[10].addNumericStateVariable("A", 9);

    for (int i = 0; i <= 10; i++) {
        trace.addTimePoint(timePoints[i]);
    }

    return trace;
}


// Test for a numeric state variable-only trace


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, BinaryNumericMeasureAdd) {
    SpatialTemporalTrace trace = getNumericStateVariableTrace();

    std::cout << "Trace length: " << trace.length() << std::endl;

    EXPECT_TRUE(parseAndEvaluateInputString("P >= 0.3 [{A} <= add(2, 3)]", trace));
}

TEST(NumericStateVariableTrace, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(parseAndEvaluateInputString("P >= 0.3 [{A} <= div(2, 3)]", getNumericStateVariableTrace()));
}

TEST(NumericStateVariableTrace, BinaryNumericMeasureLog) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinaryNumericMeasureMod) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= mod(4, 8)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinaryNumericMeasureMultiply) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= multiply(2, 3)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinaryNumericMeasurePower) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= power(2, 3)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinaryNumericMeasureSubtract) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= subtract(3, 6)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, BinaryNumericNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= add(2, 3)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, BinarySubsetMeasureAvg) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [avg(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureGeomean) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureHarmean) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [harmean(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureKurt) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [kurt(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureMax) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [max(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureMedian) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [median(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureMin) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [min(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureMode) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [mode(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureProduct) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [product(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureSkew) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [skew(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureStdev) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [stdev(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureSum) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [sum(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, BinarySubsetMeasureVar) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [var(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, BinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(clusters, area) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, ComparatorGreaterThan) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) > 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ComparatorLessThan) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) < 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ComparatorGreaterThanOrEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) >= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ComparatorLessThanOrEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ComparatorEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) = 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, CompoundConstraint) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1))) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
    }
}

TEST(NumericStateVariableTrace, CompoundConstraintMultiple) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1) " + binaryOperator + " (~ distanceFromOrigin >= 4000))) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, CompoundLogicProperty) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) ]", getNumericStateVariableTrace()), SpatialTemporalException);
    }
}

TEST(NumericStateVariableTrace, CompoundLogicPropertyMultiple) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) " + binaryOperator + " (count(clusters) <= 4) " + binaryOperator + " {B} = 3]", getNumericStateVariableTrace()), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, ConstraintEnclosedByParentheses) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2)))) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ((((perimeter <= 30.2)))))) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, Constraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, Difference) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [d(4) >= 4]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, FilterSubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, FutureLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [F [2, 3] ({A} >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, GlobalLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [G [2, 3] ({A} >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, LogicPropertyEnclosedByParentheses) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(({A} >= 4))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(((({A} >= 4))))]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, LogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) >= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, MultipleLogicProperties1) {
    EXPECT_THROW(parseAndEvaluateInputString("P = 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, MultipleLogicProperties2) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [10, 400] ( kurt(regions, area) <= 0.00001 ) ) ]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NextKLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [X [3] ({A} >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NextLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [X ({A} >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NotConstraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NotLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [~({A} >= 4.2)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NumericMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(count(clusters) >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NumericNumericComparison) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} >= 4.2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NumericSpatialMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(regions, area) <= add(2, 3)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NumericSpatialNumericComparison) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [clusteredness(clusters) >= 4.2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, NumericStateVariable1) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, NumericStateVariable2) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{a2#0f-} <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, NumericStateVariable3) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, ProbabilisticLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) >= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, QuaternarySubsetCovar) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, QuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, SpatialMeasureClusteredness) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureDensity) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, density <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureArea) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, area <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasurePerimeter) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureDistanceFromOrigin) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureAngle) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, angle <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureTriangleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureRectangleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureCircleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureCentroidX) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SpatialMeasureCentroidY) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, SubsetSpecificClusters) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, SubsetSpecificRegions) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, Subset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, TernarySubsetMeasurePercentile) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [quartile(clusters, area, 4.3) <= 0.5]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, TernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryConstraint
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UnaryConstraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UnaryNumericMeasureAbs) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= abs(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureCeil) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= ceil(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureFloor) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= floor(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureRound) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= round(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureSign) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= sign(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureSqrt) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= sqrt(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnaryNumericMeasureTrunc) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= trunc(count(clusters))]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UnaryNumericNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= abs(3.0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UnarySubsetMeasureCount) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnarySubsetMeasureClusteredness) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [clusteredness(clusters) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UnarySubsetMeasureDensity) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(clusters) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 2]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, UntilLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, UntilLogicPropertyMultiple) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, GlobalConstantValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(2) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d({A}) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(round({A})) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(add({A}, {B})) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalConstantValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, FutureIncreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(2) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d({A}) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(round({A})) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(add({A}, {B})) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(count(regions)) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, FutureIncreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) > 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, GlobalDecreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(2) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d({A}) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(count(regions)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, OscillationValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(round({A})) >= 0) ^ F [0, 10] ( (d(round({A})) <= 0) ^ F [0, 10] (d(round({A})) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(add({A}, {B})) >= 0) ^ F [0, 10] ( (d(add({A}, {B})) <= 0) ^ F [0, 10] (d(add({A}, {B})) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(count(regions)) >= 0) ^ F [0, 10] ( (d(count(regions)) <= 0) ^ F [0, 10] (d(count(regions)) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, OscillationsValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]", getNumericStateVariableTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, EnclosingWithParenthesesDifferently1) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < 1)) V (density(clusters) > 100)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, EnclosingWithParenthesesDifferently2) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < 1) V (density(clusters) > 100))]", getNumericStateVariableTrace()), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, TimeIntervalExceedsTraceTime) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 1000] (count(clusters) > 10)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariableTrace, ConstraintsCombinationUnary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > 10)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ConstraintsCombinationBinary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > 10)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

TEST(NumericStateVariableTrace, ConstraintsCombinationNary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > 10)]", getNumericStateVariableTrace()), SpatialTemporalException);
}

#endif
