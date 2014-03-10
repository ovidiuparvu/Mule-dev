#ifndef COMPLETETRACETEST_HPP
#define COMPLETETRACETEST_HPP

#include "TraceEvaluationTest.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of complete traces containing both numeric state variables and spatial entities
    class CompleteTraceTest : public TraceEvaluationTest {

        private:

           //! Initialise the trace
           virtual void InitialiseTrace() override;

    };

    void CompleteTraceTest::InitialiseTrace() {
        trace.clear();

        std::vector<TimePoint> timePoints;

        // Add 12 timepoints containing the numeric state variable "B" to the collection of timepoints
        for (int i = 0; i < 12; i++) {
            timePoints.push_back(TimePoint(i));
            timePoints[i].addNumericStateVariable("B", 3);
        }

        // Add a second numeric state variable to the collection of timepoints
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
        timePoints[11].addNumericStateVariable("A", 12);

        // Add spatial entities to each timepoint
        for (int i = 0; i < 12; i++) {

            // Add regions to the timepoint
            for (int j = 0; j <= i; j++) {
                Region region;

                region.setClusteredness(static_cast<double>(1) / ((j + 1) * 10));
                region.setDensity(static_cast<double>(0.53));
                region.setArea(static_cast<double>(100 + (j * 100.34)));
                region.setPerimeter(static_cast<double>(4000));
                region.setAngle(static_cast<double>(189));
                region.setDistanceFromOrigin(static_cast<double>(500));
                region.setTriangleMeasure(static_cast<double>(0.3));
                region.setRectangleMeasure(static_cast<double>(0.7));
                region.setCircleMeasure(static_cast<double>(0.3));
                region.setCentroidX(5.5);
                region.setCentroidY(8.3);

                timePoints[i].addRegion(region);
            }

            // Add clusters to the timepoint
            for (int k = ((((i + 1) % 4) == 0) ? (i - 1) : 0); k < i; k++) {
                Cluster cluster;

                cluster.setClusteredness(static_cast<double>((k * 2.4) + 1));
                cluster.setDensity(static_cast<double>(0.53));
                cluster.setArea(static_cast<double>(100 + (k / 100.34)));
                cluster.setPerimeter(static_cast<double>(4000));
                cluster.setAngle(static_cast<double>(189));
                cluster.setDistanceFromOrigin(static_cast<double>(500));
                cluster.setTriangleMeasure(static_cast<double>(0.3));
                cluster.setRectangleMeasure(static_cast<double>(0.7));
                cluster.setCircleMeasure(static_cast<double>(0.3));
                cluster.setCentroidX(5.5);
                cluster.setCentroidY(8.3);

                timePoints[i].addCluster(cluster);
            }
        }

        // Add all timepoints to the trace
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

TEST_F(CompleteTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= add(2, 3)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) > {B}]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureLog) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= mod({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= multiply({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) <= power(2, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(regions, area > 1)) > subtract(3, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= power(6, {B})]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusters, area) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(regions, area) <= add({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(clusters, area) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusters, area) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusters, area) <= power({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(regions, area) <= sqrt({A})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(regions, area) <= div({B}, 1)]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [product(regions, area) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(regions, area) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(regions, area) <= subtract({A}, 0)]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(regions, area) <= multiply({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(regions, area) <= add({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [geomean(regions, area) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) > {B}]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(regions) < log({A}, 2)]"));
}

TEST_F(CompleteTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) >= add({A}, {B})]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(regions) <= trunc({B})]"));
}

TEST_F(CompleteTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) = ceil({B})]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= power({B}, 4)) ^ (circleMeasure = 0.1))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= power({B}, 4)) V (circleMeasure = 0.3))) = 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= power({B}, 4)) => (circleMeasure = 0.1))) > {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= power({B}, 4)) <=> (circleMeasure = 0.1))) <= {A}]"));
}

TEST_F(CompleteTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= power({B}, 4)) ^ (circleMeasure = 0.1) ^ (~ distanceFromOrigin >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= power({B}, 4)) V (circleMeasure = 0.1) V (~ distanceFromOrigin >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= power({B}, 4)) => (circleMeasure = 0.1) => (~ distanceFromOrigin >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= power({B}, 4)) <=> (circleMeasure = 0.1) <=> (~ distanceFromOrigin >= 4000))) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= multiply({A}, 25)) ^ (count(regions) >= div({A}, 2))]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= multiply({A}, 25)) V (count(regions) >= {A})]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= multiply({A}, 25)) => (count(regions) >= {A})]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= multiply({A}, 25)) <=> (count(regions) >= div({A}, div({A}, 2)))]"));
}

TEST_F(CompleteTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) ^ (count(regions) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) V (count(regions) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) => (count(regions) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) <=> (count(regions) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= add(trunc(round(ceil(floor({B})))), 0)]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, ((perimeter >= 30.2)))) <= subtract(trunc(round(ceil(floor({B})))), 0)]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((perimeter >= 30.2)))))) <= add(trunc(round(ceil(floor({B})))), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= power(add({A}, count(regions)), subtract(7, max(regions, area))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Difference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(avg(clusters, area)) >= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(regions) >= add(power({A}, 1), -4))]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(regions) > add({A}, {A}))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(regions) >= multiply({B}, 2))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(regions) >= multiply({B}, 2)))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(regions) >= multiply({B}, 2)))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) >= multiply({B}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P = 0.1234 [( d({A}) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(CompleteTraceTest, MultipleLogicProperties2) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [3, 7] ( kurt(regions, area) <= sqrt(sqrt(sqrt({A}))) ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusters, area) >= add({A}, {B}))]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(clusters, area) >= multiply({B}, 1.5))]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~(count(clusters) >= add({A}, 0.2))]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusters, area) >= subtract(8.5, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(regions, area) <= add(2, {B})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) >= multiply(2.1, {B})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericStateVariable1) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariable2) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariable3) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ProbabilisticLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) >= div({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, QuaternarySubsetCovar) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= div({A}, div({A}, div({A}, 2)))]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, QuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= div({A}, div({A}, div({A}, 2)))]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SpatialMeasureClusteredness) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, clusteredness <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDensity) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, density <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureArea) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, area <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasurePerimeter) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, perimeter <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureAngle) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= 0.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 0.8)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidX) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, centroidX <= 27.5)) < subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidY) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, centroidY <= 12.2)) < subtract({A}, 3.1747)]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSpecificClusters) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add({B}, 0)]"));
}

TEST_F(CompleteTraceTest, SubsetSpecificRegions) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= add(count(regions), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add(count(regions), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TernarySubsetMeasurePercentile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusters, area, 4.3) <= div(count(regions), add(multiply({B}, 1.5), 3))]"));
}

TEST_F(CompleteTraceTest, TernarySubsetMeasureQuartile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] quartile(clusters, area, 50) <= div(count(regions), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 79.4) <= div(count(regions), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= subtract(60, multiply({B}, 6.59)))) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= abs(subtract(0, {B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= sqrt(ceil(0.3))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= ceil(floor({B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= add(round(count(clusters)), 0)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= add(sign(21.1), 0.4363)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= sqrt(sqrt(multiply({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= add(trunc(1.1), -0.0001)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= abs(add({B}, 0.0001))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= subtract({B}, 0.99983)]"));
}

TEST_F(CompleteTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [clusteredness(regions) <= subtract({B}, 0.99983)]"));
}

TEST_F(CompleteTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= subtract({B}, 0.99983)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= subtract({B}, 0.99983)]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UntilLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(regions) >= 1) U [2, 3] (count(regions) >= add({A}, -3.00032))]"));
}

TEST_F(CompleteTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(regions) < multiply(add({B}, 1.9994), 2)) U [2, 8] (count(regions) >= add({A}, 0.00032)) U [2, 6] (count(clusters) <= add({A}, 0.00032))]"));
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalConstantValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round(density(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(regions), count(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > add({A}, {B})), area)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FutureIncreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(2) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d({A}) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(density(regions))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(regions), count(regions))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(regions)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusters)) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) >= 0) U [0, 10] (d(2) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({A}) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueNumericStateVariable2) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(count(clusters)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) >= 0) U [0, 10] (d(round(2)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(regions))) >= 0) U [0, 10] (d(count(regions)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d({A}) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d({B}) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d(count(clusters)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(clusteredness(regions) <= 0) U [0, 10] (d(add(count(regions), count(clusters))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(regions))) <= 0) U [0, 10] (d(count(regions)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) <= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) <= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, OscillationValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round(count(clusters))) >= 0) ^ F [0, 10] ( (d(round(count(clusters))) <= 0) ^ F [0, 10] (d(round(count(clusters))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusters), count(regions))) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(add(count(clusters), count(regions))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusters)) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(count(clusters)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < subtract({A}, {B}))) V (density(clusters) > 100)]"));
}

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < subtract({A}, {B})) V (density(clusters) > 100))]"));
}

/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusters) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusters) > add(add({A}, {A}), {B}))]"));
}

/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > add(add({A}, {A}), {B}))]"));
}

#endif