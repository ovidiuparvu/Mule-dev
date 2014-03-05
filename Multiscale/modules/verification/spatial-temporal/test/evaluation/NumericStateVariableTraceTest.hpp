#ifndef NUMERICSTATEVARIABLETRACETEST_HPP
#define NUMERICSTATEVARIABLETRACETEST_HPP

#include "TraceEvaluationTest.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of numeric state variable-only traces
    class NumericStateVariableTraceTest : public TraceEvaluationTest {

        private:

           //! Initialise the trace
           virtual void InitialiseTrace() override;

    };

    void NumericStateVariableTraceTest::InitialiseTrace() {
        std::vector<TimePoint> timePoints;

        for (int i = 0; i <= 10; i++) {
            timePoints.push_back(TimePoint(i));
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

        for (TimePoint &timePoint : timePoints) {
            trace.addTimePoint(timePoint);
        }
    }

};


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= add(2, 3)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= div(2, 3)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureLog) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureMod) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= mod(4, 8)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= multiply(2, 3)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasurePower) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= power(2, 3)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= subtract(3, 6)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryNumericNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [harmean(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [kurt(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMax) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [median(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMin) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMode) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [mode(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [product(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [skew(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [stdev(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureSum) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [sum(clusters, area) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureVar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [var(clusters, area) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ComparatorGreaterThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) > 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ComparatorLessThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) < 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) >= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ComparatorEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(regions) = 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, CompoundConstraint) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1))) <= 3]"), SpatialTemporalException);
    }
}

TEST_F(NumericStateVariableTraceTest, CompoundConstraintMultiple) {
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

TEST_F(NumericStateVariableTraceTest, CompoundLogicProperty) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(regions) >= 4) ]"), SpatialTemporalException);
    }
}

TEST_F(NumericStateVariableTraceTest, CompoundLogicPropertyMultiple) {
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

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((perimeter <= 30.2)))) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((perimeter <= 30.2)))))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Constraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Difference) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [d(4) >= 4]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FilterSubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FutureLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [2, 3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [2, 3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(({A} >= 4))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(((({A} >= 4))))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, LogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, MultipleLogicProperties1) {
    EXPECT_THROW(RunEvaluationTest("P = 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, MultipleLogicProperties2) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [10, 400] ( kurt(regions, area) <= 0.00001 ) ) ]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NextKLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X [3] ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NextLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X ({A} >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NotConstraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NotLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [~({A} >= 4.2)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 4)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericNumericComparison) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} >= 4.2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericSpatialMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(regions, area) <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericSpatialNumericComparison) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) >= 4.2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericStateVariable1) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, NumericStateVariable2) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, NumericStateVariable3) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ProbabilisticLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, QuaternarySubsetCovar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, QuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SpatialMeasureClusteredness) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureDensity) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, density <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureArea) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, area <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasurePerimeter) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureAngle) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureCentroidX) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SpatialMeasureCentroidY) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SubsetSpecificClusters) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, SubsetSpecificRegions) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(regions) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Subset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, TernarySubsetMeasurePercentile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [quartile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, TernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryConstraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= abs(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= ceil(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= floor(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureRound) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= round(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureSign) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= sign(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= sqrt(count(clusters))]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(regions) <= trunc(count(clusters))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryNumericNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= abs(3.0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureCount) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) <= 2]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [density(clusters) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UntilLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(2) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d({A}) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round({A})) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add({A}, {B})) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(regions)) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) > 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(regions)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, OscillationValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round({A})) >= 0) ^ F [0, 10] ( (d(round({A})) <= 0) ^ F [0, 10] (d(round({A})) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add({A}, {B})) >= 0) ^ F [0, 10] ( (d(add({A}, {B})) <= 0) ^ F [0, 10] (d(add({A}, {B})) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueUnarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(regions)) >= 0) ^ F [0, 10] ( (d(count(regions)) <= 0) ^ F [0, 10] (d(count(regions)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueBinarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueTernarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < 1)) V (density(clusters) > 100)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < 1) V (density(clusters) > 100))]"), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusters) > 10)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusters) > 10)]"), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationUnary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > 10)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationBinary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > 10)]"), SpatialTemporalException);
}

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationNary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > 10)]"), SpatialTemporalException);
}

#endif
