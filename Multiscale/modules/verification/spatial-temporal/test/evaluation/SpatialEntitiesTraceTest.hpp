#ifndef SPATIALENTITIESTRACETEST_HPP
#define SPATIALENTITIESTRACETEST_HPP

#include "TraceEvaluationTest.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of spatial entities-only traces
    class SpatialEntitiesTraceTest : public TraceEvaluationTest {

        private:

           //! Initialise the trace
           virtual void InitialiseTrace() override;

    };

    void SpatialEntitiesTraceTest::InitialiseTrace() {
        trace.clear();

        std::vector<TimePoint> timePoints;

        // Add 12 timepoints to the collection of timepoints
        for (int i = 0; i < 12; i++) {
            timePoints.push_back(TimePoint(i));
        }

        // Add spatial entities to each timepoint
        for (int i = 0; i < 12; i++) {

            // Add regions to the timepoint
            for (int j = 0; j <= i; j++) {
                std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

                region->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>(1) / ((j + 1) * 10));
                region->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>(0.53));
                region->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>(100 + (j * 100.34)));
                region->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>(4000));
                region->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>(189));
                region->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>(500));
                region->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>(0.3));
                region->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>(0.7));
                region->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>(0.3));
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidX, 5.5);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidY, 8.3 * i);

                timePoints[i].addSpatialEntity(region, SubsetSpecificType::Regions);
            }

            // Add clusters to the timepoint
            for (int k = ((((i + 1) % 4) == 0) ? (i - 1) : 0); k < i; k++) {
                std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

                cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>((k * 2.4) + 1));
                cluster->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>(0.53));
                cluster->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>(100 + (k / 100.34)));
                cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>(4000));
                cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>(189));
                cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>(500));
                cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>(0.3));
                cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>(0.7));
                cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>(0.3));
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, 5.5);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, 8.3);

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

TEST_F(SpatialEntitiesTraceTest, BinaryNumericFilter) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(regions, centroidX < subtract(centroidY, 2.5))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= add(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) > div(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureLog) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) <= log(4.33333, 9.12312312)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= mod(4, 8)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= multiply(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) <= power(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(regions, area > 1)) > subtract(3, 6)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= power(6, 7)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusters, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(clusters, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(clusters, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusters, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusters, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [product(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(regions, area) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(regions, area) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [geomean(regions, area) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) > 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(regions) < 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) >= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(regions) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(regions) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) ^ (circleMeasure = 0.1))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) V (circleMeasure = 0.3))) = 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) => (circleMeasure = 0.1))) > 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) <=> (circleMeasure = 0.1))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= 30.2) ^ (circleMeasure = 0.1) ^ (~ distanceFromOrigin >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= 30.2) V (circleMeasure = 0.1) V (~ distanceFromOrigin >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= 30.2) => (circleMeasure = 0.1) => (~ distanceFromOrigin >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, (perimeter <= 30.2) <=> (circleMeasure = 0.1) <=> (~ distanceFromOrigin >= 4000))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) ^ (count(regions) >= 2)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) V (count(regions) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) => (count(regions) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) <=> (count(regions) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) ^ (count(regions) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) V (count(regions) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) => (count(regions) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(regions, area) >= 100) <=> (count(regions) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, ((perimeter >= 30.2)))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((perimeter >= 30.2)))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Difference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(avg(clusters, area)) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(regions, centroidX < subtract(centroidY, 2.5) ^ circleMeasure > rectangleMeasure)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, area >= 4.3)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(regions) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(regions) > 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(regions) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(regions) >= 4))]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(regions) >= 4))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties2) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [3, 7] ( kurt(regions, area) <= 0.00001 ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusters, area) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(clusters, area) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (perimeter <= 30.2))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~(count(clusters) >= 4.2)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusters, area) >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(regions, area) <= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [clusteredness(clusters) >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericStateVariable1) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariable2) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariable3) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ProbabilisticLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(regions) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, QuaternarySubsetCovar) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, QuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureClusteredness) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, clusteredness <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDensity) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, density <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureArea) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, area <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasurePerimeter) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(regions, perimeter <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureAngle) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= 0.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= 0.8)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= 30.2)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidX) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, centroidX <= 27.5)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidY) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(regions, centroidY <= 12.2)) < 1]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetOperationDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(difference(clusters, regions)) >= 11]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(intersection(clusters, clusters)) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(clusters, regions)) <= 21]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSpecificClusters) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetSpecificRegions) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(clusters, regions)) >= 4.3]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TernarySubsetMeasurePercentile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusters, area, 4.3) <= 0.5]"));
}

TEST_F(SpatialEntitiesTraceTest, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X[4] quartile(clusters, area, 4.3) <= 0.5]"), NumericException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusters, area, 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryTypeConstraint) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(clusters, type = 1)) > 7]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [1, 11] count(filter(regions, centroidX < trunc(centroidY))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= abs(-3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= ceil(0.3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [density(regions) <= floor(0.49)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) >= round(count(clusters))]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= sign(21.1)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= sqrt(2)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= trunc(1.1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(regions) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [clusteredness(regions) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [density(regions) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UntilLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(regions) >= 1) U [2, 3] (count(regions) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(regions) < 10) U [2, 8] (count(regions) >= 4) U [2, 6] (count(clusters) <= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(density(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(regions), count(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(regions)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(2) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d({A}) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(density(regions))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(regions), count(regions))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(density(regions)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, area > 5), area)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, perimeter, 50)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, perimeter, clusters, area)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusters)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, area > 5), area)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) >= 0) U [0, 10] (d(2) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) >= 0) U [0, 10] (d(4) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) >= 0) U [0, 10] (d(round(2)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(clusteredness(regions) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(regions))) >= 0) U [0, 10] (d(count(regions)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) >= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) >= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d(2) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d(4) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusters)) <= 0) U [0, 10] (d(count(clusters)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(clusteredness(regions) <= 0) U [0, 10] (d(add(count(regions), count(clusters))) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(regions))) <= 0) U [0, 10] (d(count(regions)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) <= 0) U [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, density, 80)) <= 0) U [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, OscillationValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round(count(clusters))) >= 0) ^ F [0, 10] ( (d(round(count(clusters))) <= 0) ^ F [0, 10] (d(round(count(clusters))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusters), count(regions))) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(add(count(clusters), count(regions))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusters)) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(count(clusters)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, area > 5 V perimeter < 10000), area)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, perimeter, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, perimeter, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, perimeter, 50)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) >= 0) ^ F [0, 10] ( (d(covar(clusters, perimeter, clusters, area)) <= 0) ^ F [0, 10] (d(covar(clusters, perimeter, clusters, area)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusters, perimeter) > 10) ^ (count(regions) < 1)) V (density(clusters) > 100)]"));
}

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusters, perimeter) > 10) ^ ((count(regions) < 1) V (density(clusters) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusters) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusters) > 10)]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, area > 5 ^ perimeter > 1000)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (area > 5) ^ ((perimeter > 1000) V (density > 100 V angle < 210)))) > 10)]"));
}


#endif
