#ifndef SPATIALENTITIESTRACETEST_HPP
#define SPATIALENTITIESTRACETEST_HPP

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

TEST_F(SpatialEntitiesTraceTest, BinaryNumericFilter) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(clusters, clusteredness < subtract(clusteredness, 2.5))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= add(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) < div(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureLog) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) >= log(4.33333, 9.12312312)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= mod(4, 8)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= multiply(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= power(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, clusteredness > 1)) > subtract(3, 4.2)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median([0, 10] add(count(clusters), 2)) <= power(2, 3.5)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [div(count(clusters), 2) >= 0.49)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusteredness(clusters), clusteredness(clusters)) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(clusteredness(clusters), clusteredness(clusters)) >= 0.00034]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusteredness(clusters), 4.3) <= 0.5]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X[4] quartile(clusteredness(clusters), 4.3) <= 0.5]"), NumericException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusteredness(clusters), 4.3) >= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 10] percentile(clusteredness(clusters), 4.3)) >= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min([0, 4] covar(clusteredness(clusters), clusteredness(clusters))) >= 0.00034]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ChangeMeasureDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) <= 2.7]"));
}

TEST_F(SpatialEntitiesTraceTest, ChangeMeasureRatio) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) <= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) > 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusters) < 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) >= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusters) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusters) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) ^ (clusteredness = 0.1))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) V (clusteredness = 0.3))) = 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) => (clusteredness = 0.1))) > 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) <=> (clusteredness = 0.1))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) ^ (clusteredness = 0.1) ^ (~ clusteredness >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) V (clusteredness = 0.1) V (~ clusteredness >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) => (clusteredness = 0.1) => (~ clusteredness >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, (clusteredness <= 30.2) <=> (clusteredness = 0.1) <=> (~ clusteredness >= 4000))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) ^ (count(clusters) >= 2)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) V (count(clusters) <= 4)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) => (count(clusters) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) <=> (count(clusters) <= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) ^ (count(clusters) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) V (count(clusters) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) => (count(clusters) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 100) <=> (count(clusters) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((clusteredness >= 30.2)))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ((((clusteredness >= 30.2)))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Difference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(avg(clusters, clusteredness)) >= 0.99]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(clusters, clusteredness < subtract(clusteredness, 2.5) ^ clusteredness > clusteredness)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(clusters, clusteredness >= 4.3)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(clusters) >= 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(clusters) > 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(clusters) >= 4))]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(clusters) >= 4))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(clusters) ) ^ ( covar(clusters, clusteredness, clusters, clusteredness) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties2) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(clusters, clusteredness <= 10), clusteredness) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(clusters, clusteredness, 0.4) = 0.7 ))) ) <=> ( (subsetClusteredness(filter(clusters, (clusteredness <= 2) ^ (clusteredness >= 6) V (clusteredness >= 30) => (clusteredness <= 2) <=> (clusteredness >= 4)) ) >= 2) U [3, 7] ( kurt(clusters, clusteredness) <= 0.00001 ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusters, clusteredness) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(clusters, clusteredness) >= 1)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, ~ (clusteredness <= 30.2))) <= 3]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusters, clusteredness) >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(clusters, clusteredness) >= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) >= 4.2]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) >= 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, density <= div(subtract(1E+37, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureArea) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, area <= div(subtract(1E+37, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasurePerimeter) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, perimeter <= div(subtract(1E+37, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, distanceFromOrigin <= div(subtract(1E+37, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureAngle) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, angle <= div(subtract(360, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, triangleMeasure <= div(subtract(1, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, rectangleMeasure <= div(subtract(1, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, circleMeasure <= div(subtract(1, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidX) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidX <= div(subtract(1E+37, 0),  3))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidY) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, centroidY <= div(subtract(1E+37, 0),  3))) < 1]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetOperationDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(difference(clusters, clusters)) >= 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(intersection(clusters, clusters)) >= 5]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(clusters, clusters)) > 10]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(clusters, clusters)) >= 4.3]"));
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
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(clusters, clusteredness <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [1, 11] count(filter(clusters, clusteredness < round(clusteredness))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= abs(-3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= ceil(0.3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusters) <= floor(0.49)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) >= round(count(clusters))]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= sign(21.1)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= sqrt(2)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= trunc(1.1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(clusters, clusteredness) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMin) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(clusters, clusteredness) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [product(clusters, clusteredness) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(clusters, clusteredness) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(clusters, clusteredness) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(clusters, clusteredness) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(clusters, clusteredness) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusters) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(clusters) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(clusters) <= 2]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusters) >= 1) U [2, 3] (count(clusters) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(clusters) < 10) U [2, 8] (count(clusters) >= 4) U [2, 6] (count(clusters) <= 4)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(subsetDensity(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(clusters), count(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusters)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, clusteredness > 5), clusteredness)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, clusteredness, 50)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(subsetDensity(clusters))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(clusters), count(clusters))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(subsetDensity(clusters)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(clusters, clusteredness > 5), clusteredness)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusters, clusteredness, 50)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) > 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(clusters, clusteredness > 5), clusteredness)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusters, clusteredness, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(clusters) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(clusters))) >= 0) U [0, 10] (d(count(clusters)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) >= 0) U [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, clusteredness, 80)) >= 0) U [0, 10] (d(quartile(clusters, clusteredness, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(clusters) <= 0) U [0, 10] (d(add(count(clusters), count(clusters))) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusters), count(clusters))) <= 0) U [0, 10] (d(count(clusters)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(clusters), 2)) <= 0) U [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusters, clusteredness, 80)) <= 0) U [0, 10] (d(quartile(clusters, clusteredness, 50)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusters), count(clusters))) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(add(count(clusters), count(clusters))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusters)) >= 0) ^ F [0, 10] ( (d(count(clusters)) <= 0) ^ F [0, 10] (d(count(clusters)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0) ^ F [0, 10] ( (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) <= 0) ^ F [0, 10] (d(avg(filter(clusters, clusteredness > 5 V clusteredness < 10000), clusteredness)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusters, clusteredness, 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusters, clusteredness, 50)) <= 0) ^ F [0, 10] (d(quartile(clusters, clusteredness, 50)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0) ^ F [0, 10] ( (d(covar(clusters, clusteredness, clusters, clusteredness)) <= 0) ^ F [0, 10] (d(covar(clusters, clusteredness, clusters, clusteredness)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusters, clusteredness) > 10) ^ (count(clusters) < 1)) V (subsetDensity(clusters) > 100)]"));
}

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusters, clusteredness) > 10) ^ ((count(clusters) < 1) V (subsetDensity(clusters) > 100))]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, clusteredness > 5)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, clusteredness > 5 ^ clusteredness > 1000)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(clusters, (clusteredness > 5) ^ ((clusteredness > 1000) V (clusteredness > 100 V clusteredness < 210)))) > 10)]"));
}


#endif