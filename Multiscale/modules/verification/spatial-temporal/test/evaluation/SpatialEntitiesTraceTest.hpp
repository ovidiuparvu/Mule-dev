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

#include "TimePointsSpatialEntitiesAttributesInitializer.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of spatial entities-only traces
    class SpatialEntitiesTraceTest : public NonEmptyTraceEvaluationTest {

        private:
    
            //! Add values to time points
            virtual void AddValuesToTimePoints() override;

    };
    
    
    void SpatialEntitiesTraceTest::AddValuesToTimePoints() {
        TimePointsSpatialEntitiesAttributesInitializer spatialEntitiesAttributesInitializer;
    
        spatialEntitiesAttributesInitializer.addSpatialEntitiesAttributesToTimePoints(timePoints);
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(filter(clusters, clusteredness < subtract(clusteredness, 0.0001)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= add(1, 0.0111)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) < div(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureLog) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= log(4.33333, 9.12312312)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= mod(1.00001, 8)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= multiply(2, 0.50001)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= power(2, 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(filter(clusters, clusteredness > 1))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median([0, 10] add(count(clusteredness(clusters)), 2)) < 7.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (sum(div(clusteredness(clusters), clusteredness(clusters))) = 10)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [div(count(clusteredness(clusters)), 2) > 0.49]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusteredness(clusters), 4.3) = 0]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusteredness(clusters), 4.3) > -0.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 10] percentile(clusteredness(clusters), 4.3)) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min([0, 4] covar(clusteredness(clusters), clusteredness(clusters))) > 0.000001]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ChangeMeasureDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) <= 0.0909090909091]"));
}

TEST_F(SpatialEntitiesTraceTest, ChangeMeasureRatio) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ChangeTemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(r([0, 11] min(clusteredness(clusters)))) <= 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) > 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) >= 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) <= 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) ^ (clusteredness = 0.1)))) <= 1]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) V (clusteredness = 0.3)))) = 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) => (clusteredness = 0.1)))) > 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) <=> (clusteredness = 0.1)))) < 1]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) ^ (clusteredness = 0.1) ^ (~ clusteredness > 1)))) < 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) V (clusteredness = 0.1) V (~ clusteredness > 1)))) <= 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) => (clusteredness = 0.1) => (~ clusteredness > 1)))) = 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001) <=> (clusteredness = 0.1) <=> (~ clusteredness > 1)))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) ^ (count(clusteredness(clusters)) >= 1)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) V (count(clusteredness(clusters)) < 1)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) => (count(clusteredness(clusters)) > 1)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) <=> (count(clusteredness(clusters)) <= 1)]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) ^ (count(clusteredness(clusters)) < 1) ^ 3 = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) V (count(clusteredness(clusters)) < 1) V 3 = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) => (count(clusteredness(clusters)) < 1) => 3 = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0) <=> (count(clusteredness(clusters)) < 1) <=> 3 = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness < 1e-05)))) = 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ((clusteredness < 1e-05))))) = 1]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ((((clusteredness < 1e-05))))))) >= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness > 1 V clusteredness < 1e-05))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(filter(clusters, clusteredness > -0.5 ^ clusteredness < 1e-05))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(filter(clusters, clusteredness > 0))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FutureLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(clusteredness(clusters)) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(clusteredness(clusters)) < 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// HeterogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, HeterogeneousTimeSeriesComponentPeak) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(enteringValue(peak, [0, 11] avg(clusteredness(clusters)))) > 0.590809090909]"));
}

TEST_F(SpatialEntitiesTraceTest, HeterogeneousTimeSeriesComponentValley) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [median(enteringValue(valley, [0, 11] count(clusteredness(clusters)))) < 2]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousHomogeneousTimeSeries
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, HomogeneousHomogeneousTimeSeries) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(values(plateau, [0, 11] count(clusteredness(clusters)))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesComponentAscent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(values(ascent, [0, 11] count(clusteredness(clusters)))) > 1]"));
}

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesComponentDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(timeSpan(descent, [0, 11] count(clusteredness(clusters)))) = 1]"));
}

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesComponentPlateau) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(values(plateau, [0, 11] count(clusteredness(clusters)))) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesComponentUniformAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(values(uniformAscent, [0, 11] count(clusteredness(clusters)))) = 11]"));
}

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesComponentUniformDescent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(values(uniformDescent, [0, 11] avg(clusteredness(clusters)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesMeasureTimeSpan) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(timeSpan(ascent, [0, 11] count(clusteredness(clusters)))) > 4]"));
}

TEST_F(SpatialEntitiesTraceTest, HomogeneousTimeSeriesMeasureValue) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(values(descent, [0, 11] count(clusteredness(clusters)))) = 2]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(clusteredness(clusters)) >= 0.99)]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [((count(clusteredness(clusters)) >= 0.99))]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [((((count(clusteredness(clusters)) >= 0.99))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= 0.99999]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(clusteredness(clusters)) ) ^ ( covar(clusteredness(clusters), clusteredness(clusters)) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties2) {
    EXPECT_TRUE(
        RunEvaluationTest(""
            "P <= 0.85934 ["
            "   (~ "
            "       F [2, 3] ( "
            "           max("
            "               clusteredness("
            "                   filter("
            "                       clusters, "
            "                       clusteredness <= 0.25"
            "                   )"
            "               )"
            "           ) >= 2 "
            "       ) "
            "   ) => ( "
            "       G [4, 5] ("
            "           X ("
            "               X [5] ( "
            "                   percentile("
            "                       clusteredness("
            "                           clusters"
            "                       ), "
            "                       0.4"
            "                   ) = 0.7 "
            "               )"
            "           )"
            "       ) "
            "   ) <=> ( "
            "       count("
            "           clusteredness("
            "               filter("
            "                   clusters, "
            "                   (clusteredness <= 2) ^ "
            "                   (clusteredness >= 6) V "
            "                   (clusteredness >= 30) => "
            "                   (clusteredness <= 2) <=> "
            "                   (clusteredness >= 4)"
            "               ) "
            "           )"
            "       ) >= 0"
            "   ) U [3, 7] ( "
            "       kurt("
            "           clusteredness("
            "               clusters"
            "           )"
            "       ) <= sqrt("
            "           sqrt("
            "               sqrt("
            "                   {A}"
            "               )"
            "           )"
            "       ) "
            "   ) "
            "]"
        )
    );
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusteredness(clusters)) >= 0.272717272727)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(clusteredness(clusters)) <= 0.0919090909091)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotConstraint) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ~ (clusteredness <= 0)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [~(count(clusteredness(clusters)) >= 1)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg([0, 3] count(clusteredness(clusters))) = 2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(clusteredness(clusters)) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(clusteredness(clusters)) < 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWithoutTypes) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableScaleAndSubsystemLeft) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableScaleAndSubsystemRight) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= {B}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableBothTypes) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {B}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableBothTypesAndDifferentTypeValues) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {C}(scaleAndSubsystem = Organ.Heart)]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableOneNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{C}(scaleAndSubsystem = Organ.Heart) = 12]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWrongRhsType) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {C}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWrongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWrongLongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWrongTypeLhs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Heart) <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableWrongTypeLhsLargerValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{B}(scaleAndSubsystem = 213.121) <= {B}]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableScaleAndSubsystemNotInMultiscaleArchitectureGraph) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({D}(scaleAndSubsystem = Organ.Liver) < 5.01) ^ ({D}(scaleAndSubsystem = Organ.Liver) > 4.99))]"));
}

TEST_F(SpatialEntitiesTraceTest, NumericStateVariableScaleAndSubsystemInMultiscaleArchitectureGraph) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({B}(scaleAndSubsystem = Organ.Kidney) < 3.01) ^ ({B}(scaleAndSubsystem = Organ.Kidney) > 2.99))]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericStatisticalMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X min([0, 5] count(clusteredness(clusters))) <= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// PrimarySpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, PrimarySpatialMeasureCollection) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(clusteredness(clusters)) > 0.964545454545]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ProbabilisticLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.4 [count(clusteredness(clusters)) >= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// ScaleAndSubsystem
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ScaleAndSubsystem) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.4 [count(clusteredness(filter(clusters, scaleAndSubsystem = Organ.Kidney))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SimilarityMeasureAntiSimilar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [opposite([0, 11] count(clusteredness(clusters)), [0, 11] subtract(0, count(clusteredness(clusters))), 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, SimilarityMeasureSimilar) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [similar(r([0, 11] count(clusteredness(clusters))), r([0, 11] multiply(avg(clusteredness(clusters)), 2)), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SimilarityTemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [similar([0, 11] count(clusteredness(clusters)), [0, 11] 6, 6)]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness = 0))) = 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, density > 0.5))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureArea) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, area > 500000.0))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasurePerimeter) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, perimeter > 500000.0))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, distanceFromOrigin > 500000.0))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureAngle) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, angle > 180.0))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, triangleMeasure > 0.5))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, rectangleMeasure > 0.5))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, circleMeasure > 0.5))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidX) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, centroidX > 500000.0))) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCentroidY) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, centroidY > 500000.0))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SpatialMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(clusteredness(clusters)) > 0.0908090909091]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Subset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetOperationDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(difference(clusters, filter(clusters, clusteredness < 0)))) >= 1]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationDifferenceRegion) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(difference(regions, clusters))) > 24]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationIntersection) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(intersection(clusters, filter(clusters, clusteredness <= 0)))) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationIntersectionRegion) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(intersection(clusters, filter(regions, clusteredness > 0.0)))) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(union(filter(clusters, clusteredness < 20), filter(clusters, clusteredness >= 20)))) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationUnionRegion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(union(clusters, regions))) >= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSpecificClusters) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetSpecificRegions) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(regions)) < 2]"));
}



/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(union(clusters, clusters))) >= 4.3]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 11] max(clusteredness(clusters))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TemporalNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusteredness(clusters)) >= 0.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(clusteredness(clusters)) = 1)]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TemporalNumericMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 11] count(clusteredness(clusters))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeSeriesComponent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [median(enteringValue(uniformAscent, [0, 11] count(clusteredness(clusters)))) < 5]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeSeriesMeasureEnteringTime) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(enteringTime(descent, [0, 11] count(clusteredness(clusters)))) < 2]"));
}

TEST_F(SpatialEntitiesTraceTest, TimeSeriesMeasureEnteringValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(enteringValue(uniformDescent, [0, 11] max(clusteredness(clusters)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeSeriesTimeSeriesComponent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(enteringTime(peak, [0, 11] count(clusteredness(clusters)))) = 6]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericFilter) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(filter(clusters, clusteredness <= ceil(clusteredness)))) < 11]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= abs(-1)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = ceil(0.3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = floor(0.49)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = round(0.50001)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= sign(21.1)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= sqrt(0.9)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= trunc(1.1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 11] count(clusteredness(clusters))) < 11]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (max(floor(clusteredness(clusters))) = 1.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= 0.9999]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySpatialConstraint) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness <= -0.1))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusteredness(clusters)) < 1e-05]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureCount) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) > 1]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureGeomean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusteredness(clusters)) > 0]"), NumericException);
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(clusteredness(clusters)) > 1e-05]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureKurt) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [kurt(clusteredness(clusters)) > 0.1]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureMax) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(clusteredness(clusters)) = -1.0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusteredness(clusters)) >= 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureMin) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(clusteredness(clusters)) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(clusteredness(clusters)) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureProduct) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [product(clusteredness(clusters)) < 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(clusteredness(clusters)) = 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureStdev) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [stdev(clusteredness(clusters)) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(clusteredness(clusters)) > 0]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(clusteredness(clusters)) < 0.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 5] count(clusteredness(clusters))) > 6]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryScaleAndSubsystemConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryScaleAndSubsystemConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(filter(clusters, scaleAndSubsystem = Organ.Heart))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UntilLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(d(count(clusteredness(clusters))) >= 0) U [0, 3] {A} = 4]"));
}

TEST_F(SpatialEntitiesTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(d(count(clusteredness(clusters))) >= 0) U [0, 3] (count(clusteredness(clusters)) > 0) <=> (count(clusteredness(clusters)) = 3)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(count(clusteredness(clusters)))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(clusteredness(clusters)), 2)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueUnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusteredness(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusteredness(filter(clusters, clusteredness < 0)), clusteredness(clusters))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusteredness(clusters), 50)) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(count(clusteredness(clusters)))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(clusteredness(clusters)), 1)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(clusteredness(clusters))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusteredness(clusters), 50)) > 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusteredness(clusters), 50)) < 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(2) > 0) U [0, 10] (d(2) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d({A}) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueNumericStateVariable2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) >= 0) U [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) > 0) U [0, 10] (d(add(count(clusteredness(clusters)), 2)) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusteredness(clusters)), 1)) > 0) U [0, 10] (d(power(count(clusteredness(clusters)), 1)) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) U [0, 10] (d(avg(clusteredness(filter(clusters, clusteredness > -1.0 V clusteredness < 2.0)))) < 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusteredness(clusters), 80)) >= 0) U [0, 10] (d(quartile(clusteredness(clusters), 50)) < 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(2) < 0) U [0, 10] (d(4) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d({C}(scaleAndSubsystem = Organ.Heart)) < 0) U [0, 10] (d({C}(scaleAndSubsystem = Organ.Heart)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) <= 0) U [0, 10] (d(count(clusteredness(clusters))) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) < 0) U [0, 10] (d(add(count(clusteredness(clusters)), 2)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusteredness(clusters)), 1)) < 0) U [0, 10] (d(power(count(clusteredness(clusters)), 1)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(clusteredness(clusters), clusteredness(clusters))) < 0) U [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusteredness(clusters), 80)) < 0) U [0, 10] (d(quartile(clusteredness(clusters), 50)) >= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, OscillationsValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueNumericStateVariableStartingLater) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] ( ({A} > 1) ^ (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(abs(count(clusteredness(clusters)))) >= 0) ^ F [0, 10] ( (d(abs(count(clusteredness(clusters)))) <= 0) ^ F [0, 10] (d(abs(count(clusteredness(clusters)))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusteredness(clusters)), 2)) >= 0) ^ F [0, 10] ( (d(add(count(clusteredness(clusters)), 2)) <= 0) ^ F [0, 10] (d(add(count(clusteredness(clusters)), 2)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusteredness(clusters))) >= 0) ^ F [0, 10] ( (d(count(clusteredness(clusters))) <= 0) ^ F [0, 10] (d(count(clusteredness(clusters))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) ^ F [0, 10] ( (d(covar(clusteredness(clusters), clusteredness(clusters))) <= 0) ^ F [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusteredness(clusters), 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusteredness(clusters), 50)) <= 0) ^ F [0, 10] (d(quartile(clusteredness(clusters), 50)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusteredness(clusters)) > 0.5)) ^ (count(clusteredness(clusters)) > 100)]"));
}

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusteredness(clusters)) > 0.5) ^ ((count(clusteredness(clusters)) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusteredness(clusters)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusteredness(clusters)) > 10)]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, clusteredness > 0.25))) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, clusteredness > 0.25 ^ clusteredness > 50.0))) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, (clusteredness > 0.25) ^ ((clusteredness > 50.0) V (clusteredness > 5.0 V clusteredness < 10.0))))) > 10)]"));
}


#endif