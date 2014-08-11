#ifndef COMPLETETRACETEST_HPP
#define COMPLETETRACETEST_HPP

/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/

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

            // Add clusters to the timepoint
            for (int k = ((((i + 1) % 4) == 0) ? (i - 1) : 0); k <= i; k++) {
                std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

                cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>((k * 2.4) + 1));
                cluster->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>(1E+37 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>(1E+37 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>(1E+37 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>(1E+37 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>(360 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>(1 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>(1 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>(1 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, static_cast<double>(1E+37 - 0) / 2);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, static_cast<double>(1E+37 - 0) / 2);

                timePoints[i].addSpatialEntity(cluster, SubsetSpecificType::Clusters);
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
// BinaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(clusters, clusteredness > subtract(clusteredness, 2.5))) > 0]"));
}


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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) > div({B}, 1)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureLog) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= log({A}, 3)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= mod({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) <= multiply({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) <= power(2, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, clusteredness > 1)) > subtract(3, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 5] add(count(clusters), 2)) >= 7.99999]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [multiply(count(clusters), 2) >= 1.99999]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusteredness(clusters), clusteredness(clusters)) >= div({A}, div({A}, div({A}, 2)))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusteredness(clusters), clusteredness(clusters)) <= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusteredness(clusters), 4.3) <= div(count(clusters), add(multiply({B}, 1.5), 3))]"));
}

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] quartile(clusteredness(clusters), 50) <= div(count(clusters), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusteredness(clusters), 79.4) >= div(count(clusters), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 2] percentile(clusteredness(clusters), 79.4)) >= div(count(clusters), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 6] covar(clusteredness(clusters), clusteredness(clusters))) <= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeMeasureDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) >= 2]"));
}

TEST_F(CompleteTraceTest, ChangeMeasureRatio) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) > {B}]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusters) < log({A}, 2)]"));
}

TEST_F(CompleteTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) >= add({A}, {B})]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusters) <= trunc({B})]"));
}

TEST_F(CompleteTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) = ceil({B})]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) ^ (clusteredness = 0.1))) <= {A}]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) V (clusteredness = 0.3))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) => (clusteredness = 0.1))) > {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) <=> (clusteredness = 0.1))) <= {A}]"));
}

TEST_F(CompleteTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) ^ (clusteredness = 0.1) ^ (~ clusteredness >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) V (clusteredness = 0.1) V (~ clusteredness >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) => (clusteredness = 0.1) => (~ clusteredness >= 4000))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= power({B}, 4)) <=> (clusteredness = 0.1) <=> (~ clusteredness >= 4000))) <= 0]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= multiply({A}, 25)) ^ (count(clusters) >= div({A}, 2))]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= multiply({A}, 25)) V (count(clusters) = 0)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= multiply({A}, 25)) => (count(clusters) >= {A})]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= multiply({A}, 25)) <=> (count(clusters) >= div({A}, div({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) ^ (count(clusters) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) V (count(clusters) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) => (count(clusters) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) <=> (count(clusters) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= add(trunc(round(ceil(floor({B})))), 0)]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((clusteredness >= 30.2)))) <= subtract(trunc(round(ceil(floor({B})))), 0)]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((clusteredness >= 30.2)))))) <= add(trunc(round(ceil(floor({B})))), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= power(add({A}, count(clusters)), subtract(7, max(clusters, clusteredness))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Difference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [d(avg(clusters, clusteredness)) >= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(clusters, clusteredness < subtract(clusteredness, 2.5) ^ clusteredness > clusteredness)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, clusteredness >= 4.3)) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(clusters) >= add(power({A}, 1), -4))]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(clusters) > add({A}, {A}))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= multiply({B}, 2))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(clusters) >= multiply({B}, 2)))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(clusters) >= multiply({B}, 2)))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) >= multiply({B}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d({A}) >=  count(clusters) ) ^ ( covar(clusters, clusteredness, clusters, clusteredness) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(CompleteTraceTest, MultipleLogicProperties2) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(clusters, clusteredness <= 10), clusteredness) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(clusters, clusteredness, 0.4) = 0.7 ))) ) <=> ( (subsetClusteredness(filter(clusters, (clusteredness <= 2) ^ (clusteredness >= 6) V (clusteredness >= 30) => (clusteredness <= 2) <=> (clusteredness >= 4)) ) >= 2) U [3, 7] ( kurt(clusters, clusteredness) <= sqrt(sqrt(sqrt({A}))) ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusters, clusteredness) > subtract(subtract({A}, {B}), {B}))]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(clusters, clusteredness) >= multiply({B}, 0.2))]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (clusteredness <= 30.2))) <= {B}]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusters, clusteredness) >= subtract(8.5, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(clusters, clusteredness) >= add(2, {B})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) >= multiply(2.1, {B})]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) >= div({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SpatialMeasureClusteredness) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDensity) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, density <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureArea) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, area <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasurePerimeter) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureAngle) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidX) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidX <= 30.2)) > subtract({A}, 3)]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidY) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidY <= 30.2)) > subtract({A}, 3)]"));
}



/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetOperationDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(difference(clusters, clusters)) < 1]"));
}

TEST_F(CompleteTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(intersection(clusters, filter(clusters, clusteredness > 22))) >= 2]"));
}

TEST_F(CompleteTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(filter(clusters, clusteredness < 20), filter(clusters, clusteredness >= 20))) > 10]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add(count(clusters), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(clusters, clusters)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add(count(clusters), add(multiply({B}, 1.5), 3))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryTypeConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(clusters, type = 0)) > 7]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= subtract(60, multiply({B}, 6.59)))) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(clusters, clusteredness <= round(clusteredness))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) <= abs(subtract(3.99, {B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= sqrt(ceil(0.3))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= ceil(floor({B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) >= add(round(count(clusters)), -0.005)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add(sign(21.1), 0.4363)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= sqrt(sqrt(multiply({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) > add(trunc(1.1), -0.0001)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= abs(add({B}, 0.0001))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusters, clusteredness) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(clusters, clusteredness) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(clusters, clusteredness) >= add({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(clusters, clusteredness) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusters, clusteredness) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusters, clusteredness) <= power({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(clusters, clusteredness) >= sqrt({A})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(clusters, clusteredness) <= subtract({B}, 5)]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [product(clusters, clusteredness) <= {A}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(clusters, clusteredness) <= {B}]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(clusters, clusteredness) <= subtract({A}, 0)]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(clusters, clusteredness) >= multiply({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(clusters, clusteredness) <= add({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [geomean(clusters, clusteredness) >= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= subtract({B}, 0.99983)]"));
}

TEST_F(CompleteTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) >= subtract({B}, 3)]"));
}

TEST_F(CompleteTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(clusters) >= subtract({B}, 3.099983)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 1) U [2, 3] (count(clusters) >= add({A}, -3.00032))]"));
}

TEST_F(CompleteTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(clusters) < multiply(add({B}, 1.9994), 2)) U [2, 8] (count(clusters) >= add({A}, 0.00032)) U [2, 6] (count(clusters) <= add({A}, 0.00032))]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(subsetClusteredness(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(clusters), count(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusters)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, clusteredness > add({A}, {B})), clusteredness)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, clusteredness, 50)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) = 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(subsetClusteredness(clusters))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(clusters), count(clusters))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(clusters)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, clusteredness > 5), clusteredness)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, clusteredness, 50)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) > 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, clusteredness > 5), clusteredness)) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, clusteredness, 50)) <= 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(clusters) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(clusters))) >= 0) U [0, 10] (d(count(clusters)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) >= 0) U [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, clusteredness, 80)) >= 0) U [0, 10] (d(quartile(clusters, clusteredness, 50)) <= 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(clusters) <= 0) U [0, 10] (d(add(count(clusters), count(clusters))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(clusters))) <= 0) U [0, 10] (d(count(clusters)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) <= 0) U [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, clusteredness, 80)) <= 0) U [0, 10] (d(quartile(clusters, clusteredness, 50)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusters), count(clusters))) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(add(count(clusters), count(clusters))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusters)) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(count(clusters)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, clusteredness, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, clusteredness, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, clusteredness, 50)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0) ^ F [0, 10] ( (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0) ^ F [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusters, clusteredness) > 10) ^ (count(clusters) < subtract({A}, {B}))) V (subsetClusteredness(clusters) > 100)]"));
}

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusters, clusteredness) > 10) ^ ((count(clusters) < subtract({A}, {B})) V (subsetClusteredness(clusters) > 100))]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, clusteredness > 5)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, clusteredness > 5 ^ clusteredness > 1000)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (clusteredness > 5) ^ ((clusteredness > 1000) V (clusteredness > 100 V clusteredness < 210)))) > add(add({A}, {A}), {B}))]"));
}


#endif