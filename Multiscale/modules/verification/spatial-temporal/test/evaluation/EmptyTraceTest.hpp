#ifndef EMPTYTRACETEST_HPP
#define EMPTYTRACETEST_HPP

#include "parsing/InputStringParserAndEvaluator.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// Test for an empty trace


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, BinaryNumericMeasureAdd) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= add(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasureDiv) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= div(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasureLog) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasureMod) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= mod(4, 8)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasureMultiply) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= multiply(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasurePower) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= power(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinaryNumericMeasureSubtract) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= subtract(3, 6)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, BinaryNumericNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= add(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, BinarySubsetMeasureAvg) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [avg(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureGeomean) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureHarmean) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [harmean(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureKurt) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [kurt(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureMax) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [max(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureMedian) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [median(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureMin) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [min(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureMode) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [mode(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureProduct) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [product(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureSkew) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [skew(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureStdev) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [stdev(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureSum) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [sum(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, BinarySubsetMeasureVar) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [var(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, BinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(clusters, area) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, ComparatorGreaterThan) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) > 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ComparatorLessThan) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) < 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ComparatorGreaterThanOrEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) >= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ComparatorLessThanOrEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ComparatorEqual) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(regions) = 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, CompoundConstraint) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1))) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
    }
}

TEST(EmptyTrace, CompoundConstraintMultiple) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1) " + binaryOperator + " (~ distanceFromOrigin >= 4000))) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, CompoundLogicProperty) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) ]", SpatialTemporalTrace()), SpatialTemporalException);
    }
}

TEST(EmptyTrace, CompoundLogicPropertyMultiple) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) " + binaryOperator + " (count(clusters) <= 4) " + binaryOperator + " {B} = 3]", SpatialTemporalTrace()), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, ConstraintEnclosedByParentheses) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2)))) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ((((perimeter <= 30.2)))))) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, Constraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, Difference) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [d(4) >= 4]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, FilterSubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, FutureLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [F [2, 3] ({A} >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, GlobalLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [G [2, 3] ({A} >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, LogicPropertyEnclosedByParentheses) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(({A} >= 4))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(((({A} >= 4))))]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, LogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) >= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, MultipleLogicProperties1) {
    EXPECT_THROW(parseAndEvaluateInputString("P = 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, MultipleLogicProperties2) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [10, 400] ( kurt(regions, area) <= 0.00001 ) ) ]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NextKLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [X [3] ({A} >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NextLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [X ({A} >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NotConstraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NotLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [~({A} >= 4.2)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NumericMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [(count(clusters) >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NumericNumericComparison) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} >= 4.2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NumericSpatialMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [geomean(regions, area) <= add(2, 3)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NumericSpatialNumericComparison) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [clusteredness(clusters) >= 4.2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, NumericStateVariable1) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, NumericStateVariable2) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{a2#0f-} <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, NumericStateVariable3) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, ProbabilisticLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) >= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, QuaternarySubsetCovar) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, QuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, SpatialMeasureClusteredness) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureDensity) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, density <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureArea) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, area <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasurePerimeter) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureDistanceFromOrigin) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureAngle) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, angle <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureTriangleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureRectangleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureCircleMeasure) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureCentroidX) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SpatialMeasureCentroidY) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, SubsetSpecificClusters) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, SubsetSpecificRegions) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(regions) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, Subset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, TernarySubsetMeasurePercentile) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [quartile(clusters, area, 4.3) <= 0.5]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, TernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryConstraint
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UnaryConstraint) {
    EXPECT_THROW(parseAndEvaluateInputString("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UnaryNumericMeasureAbs) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= abs(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureCeil) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= ceil(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureFloor) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= floor(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureRound) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= round(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureSign) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= sign(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureSqrt) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= sqrt(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnaryNumericMeasureTrunc) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(regions) <= trunc(count(clusters))]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UnaryNumericNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [{A} <= abs(3.0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UnarySubsetMeasureCount) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnarySubsetMeasureClusteredness) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [clusteredness(clusters) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UnarySubsetMeasureDensity) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [density(clusters) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [count(clusters) <= 2]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, UntilLogicProperty) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, UntilLogicPropertyMultiple) {
    EXPECT_THROW(parseAndEvaluateInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, GlobalConstantValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(2) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d({A}) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(round({A})) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(add({A}, {B})) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalConstantValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, FutureIncreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(2) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d({A}) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(round({A})) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(add({A}, {B})) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(count(regions)) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, FutureIncreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) > 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, GlobalDecreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(2) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d({A}) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(count(regions)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, IncreasingUntilDecreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, DecreasingUntilIncreasingValueReal) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, OscillationValueNumericStateVariable) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueUnaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(round({A})) >= 0) ^ F [0, 10] ( (d(round({A})) <= 0) ^ F [0, 10] (d(round({A})) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueBinaryNumeric) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(add({A}, {B})) >= 0) ^ F [0, 10] ( (d(add({A}, {B})) <= 0) ^ F [0, 10] (d(add({A}, {B})) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueUnarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(count(regions)) >= 0) ^ F [0, 10] ( (d(count(regions)) <= 0) ^ F [0, 10] (d(count(regions)) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueBinarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueTernarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, OscillationsValueQuaternarySubset) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]", SpatialTemporalTrace()), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, EnclosingWithParenthesesDifferently1) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < 1)) V (density(clusters) > 100)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, EnclosingWithParenthesesDifferently2) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < 1) V (density(clusters) > 100))]", SpatialTemporalTrace()), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, TimeIntervalExceedsTraceTime) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 1000] (count(clusters) > 10)]", SpatialTemporalTrace()), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST(EmptyTrace, ConstraintsCombinationUnary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > 10)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ConstraintsCombinationBinary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > 10)]", SpatialTemporalTrace()), SpatialTemporalException);
}

TEST(EmptyTrace, ConstraintsCombinationNary) {
    EXPECT_THROW(parseAndEvaluateInputString("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > 10)]", SpatialTemporalTrace()), SpatialTemporalException);
}

#endif
