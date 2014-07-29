#ifndef EMPTYTRACETEST_HPP
#define EMPTYTRACETEST_HPP

#include "TraceEvaluationTest.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of empty traces
    class EmptyTraceTest : public TraceEvaluationTest {

        private:

           //! Initialise the trace
           virtual void InitialiseTrace() override;

    };

    void EmptyTraceTest::InitialiseTrace() {
        // Empty trace
    }

};


/////////////////////////////////////////////////////////
//
//
// BinaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericFilter) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(regions, centroidX < subtract(centroidY, 2.5))) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= add(2, 3)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= div(2, 3)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasureLog) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasureMod) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= mod(4, 8)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= multiply(2, 3)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasurePower) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= power(2, 3)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= subtract(3, 6)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [harmean(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [kurt(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureMax) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [median(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureMin) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureMode) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [mode(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [product(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [skew(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [stdev(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureSum) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [sum(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinarySubsetMeasureVar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [var(clusters, area) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ComparatorGreaterThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) > 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorLessThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) < 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) >= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) = 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, CompoundConstraint) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1))) <= 3]"), SpatialTemporalException);
    }
}

TEST_F(EmptyTraceTest, CompoundConstraintMultiple) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1) " + binaryOperator + " (~ distanceFromOrigin >= 4000))) <= 3]"), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, CompoundLogicProperty) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) ]"), SpatialTemporalException);
    }
}

TEST_F(EmptyTraceTest, CompoundLogicPropertyMultiple) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) " + binaryOperator + " (count(clusters) <= 4) " + binaryOperator + " {B} = 3]"), SpatialTemporalException);
    }
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2)))) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((perimeter <= 30.2)))))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, Constraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, Difference) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [d(4) >= 4]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FilterNumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(regions, centroidX < subtract(centroidY, 2.5) ^ area > perimeter)) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FilterSubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FutureLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [2, 3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, GlobalLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [2, 3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(({A} >= 4))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(((({A} >= 4))))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, LogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, MultipleLogicProperties1) {
    EXPECT_THROW(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, MultipleLogicProperties2) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [3, 7] ( kurt(regions, area) <= 0.00001 ) ) ]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NextKLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X [3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NextLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NotConstraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NotLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [~({A} >= 4.2)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericNumericComparison) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} >= 4.2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericSpatialMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(regions, area) <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericSpatialNumericComparison) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) >= 4.2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericStateVariable1) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariable2) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariable3) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ProbabilisticLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, QuaternarySubsetCovar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, QuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SpatialMeasureClusteredness) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureDensity) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, density <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureArea) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, area <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasurePerimeter) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureAngle) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureCentroidX) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SpatialMeasureCentroidY) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetOperationDifference) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(difference(clusters, regions)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SubsetOperationIntersection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(intersection(clusters, clusters)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SubsetOperationUnion) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(union(clusters, regions)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetSpecificClusters) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SubsetSpecificRegions) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetSubsetOperation) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(difference(clusters, regions)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, Subset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TernarySubsetMeasurePercentile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [quartile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryTypeConstraint) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(filter(clusters, type = 0)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnarySpatialConstraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericFilter) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(regions, centroidX < trunc(centroidY))) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= abs(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= ceil(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= floor(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureRound) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= round(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureSign) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= sign(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= sqrt(count(clusters))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= trunc(count(clusters))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= abs(3.0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnarySubsetMeasureCount) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(clusters) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UntilLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, GlobalConstantValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FutureIncreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(2) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d({A}) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round({A})) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add({A}, {B})) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(regions)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) > 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, GlobalDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, OscillationValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round({A})) >= 0) ^ F [0, 10] ( (d(round({A})) <= 0) ^ F [0, 10] (d(round({A})) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add({A}, {B})) >= 0) ^ F [0, 10] ( (d(add({A}, {B})) <= 0) ^ F [0, 10] (d(add({A}, {B})) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(regions)) >= 0) ^ F [0, 10] ( (d(count(regions)) <= 0) ^ F [0, 10] (d(count(regions)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < 1)) V (density(clusters) > 100)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < 1) V (density(clusters) > 100))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusters) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusters) > 10)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ConstraintsCombinationUnary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintsCombinationBinary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintsCombinationNary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > 10)]"), SpatialTemporalException);
}


#endif
