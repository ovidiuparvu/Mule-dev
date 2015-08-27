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

#include "TimePointsNumericValuesInitializer.hpp"
#include "TimePointsSpatialEntitiesAttributesInitializer.hpp"
 
using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of complete traces containing both numeric state variables and spatial entities
    class CompleteTraceTest : public NonEmptyTraceEvaluationTest {

        private:
    
            //! Add values to time points
            virtual void AddValuesToTimePoints() override;
    
    };
    
    
    void CompleteTraceTest::AddValuesToTimePoints() {
        TimePointsNumericValuesInitializer numericValuesInitializer;
        TimePointsSpatialEntitiesAttributesInitializer spatialEntitiesAttributesInitializer;
            
        numericValuesInitializer.addValuesOfNumericStateVariablesToTimePoints(timePoints);
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

TEST_F(CompleteTraceTest, BinaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(filter(clusters, clusteredness > subtract(clusteredness, 0.00001)))) > 10]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= add(1, 0.0001)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) > div({B}, subtract({B}, 0.1))]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureLog) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= log({A}, 3)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= mod({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.33 [count(clusteredness(clusters)) >= multiply({A}, 1)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= power(2, 0)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(filter(clusters, clusteredness > 1))) = subtract({A}, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 5] add(count(clusteredness(clusters)), 2)) >= 7.99999]"));
}

/////////////////////////////////////////////////////////
//
//
// BinaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (sum(multiply(clusteredness(clusters), clusteredness(clusters))) > 1.82644628099)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [multiply(count(clusteredness(clusters)), 2) >= 1.99999]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [covar(clusteredness(clusters), clusteredness(clusters)) < 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X[4] percentile(clusteredness(clusters), 100) >= 0.363636363636]"));
}

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] quartile(clusteredness(clusters), 50) <= 0.0909090909091]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(clusteredness(clusters), 79.4) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 2] percentile(clusteredness(clusters), 90)) >= 0.181818181818]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 6] covar(clusteredness(clusters), clusteredness(clusters))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeMeasureDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) < 0.0833333333333]"));
}

TEST_F(CompleteTraceTest, ChangeMeasureRatio) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [r(max(clusteredness(clusters))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeTemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(d([0, 11] {C}(scaleAndSubsystem = Organ.Heart))) = -9]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(clusteredness(clusters))) <= 0.0909090909091]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) > subtract({B}, 1.99999)]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) < log({A}, 2)]"));
}

TEST_F(CompleteTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) >= add({A}, 0.0001)]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) <= trunc(subtract({B}, 1.0001))]"));
}

TEST_F(CompleteTraceTest, ComparatorEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(clusters)) = ceil(subtract({A}, 0.00001))]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0) ^ (clusteredness = 0.1)))) = 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0) V (clusteredness = 0.3)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0) => (clusteredness = 0.1)))) > 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0) <=> (clusteredness = 0.1)))) = 0]"));
}

TEST_F(CompleteTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 1e-05) ^ (clusteredness = 0.1) ^ (~ clusteredness >= 4000)))) < 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 1e-05) V (clusteredness = 0.1) V (~ clusteredness >= 4000)))) = 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 1e-05) => (clusteredness = 0.1) => (~ clusteredness >= 4000)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 1e-05) <=> (clusteredness = 0.1) <=> (~ clusteredness >= 4000)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0.0001) ^ (count(clusteredness(clusters)) >= div({A}, 2))]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0.0001) V (count(clusteredness(clusters)) = 0)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0.0001) => (count(clusteredness(clusters)) >= 1)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) >= 0.0001) <=> (count(clusteredness(clusters)) >= div({A}, div({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) > 0) ^ (count(clusteredness(clusters)) <= 1) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) > 0) V (count(clusteredness(clusters)) <= 1) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) > 0) => (count(clusteredness(clusters)) <= 1) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(clusteredness(clusters)) > 0) <=> (count(clusteredness(clusters)) <= 1) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, (clusteredness <= 0.0001)))) = 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ((clusteredness >= 0.0001))))) < 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ((((clusteredness >= 0.0001))))))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness > 1 V clusteredness <= 0))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(filter(clusters, clusteredness < subtract(clusteredness, -0.1) ^ clusteredness >= 0))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(filter(clusters, clusteredness >= -1.0))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(clusteredness(clusters)) > add(power({A}, 1), -1))]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(clusteredness(clusters)) >= ceil(div({A}, 2)))]"));
}


/////////////////////////////////////////////////////////
//
//
// HeterogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HeterogeneousTimeSeriesComponentPeak) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(enteringValue(peak, [0, 11] {A})) = 4]"));
}

TEST_F(CompleteTraceTest, HeterogeneousTimeSeriesComponentValley) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(enteringValue(valley, [0, 11] count(clusteredness(clusters)))) = 2]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousHomogeneousTimeSeries
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousHomogeneousTimeSeries) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(timeSpan(plateau, [0, 11] {B})) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(values(ascent, [0, 11] count(clusteredness(clusters)))) = 1]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] {C}(scaleAndSubsystem = Organ.Heart))) = 7.5]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentPlateau) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(values(plateau, [0, 11] {B})) = 2.999]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentUniformAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(values(uniformAscent, [0, 11] count(clusteredness(clusters)))) = 11]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentUniformDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(values(uniformDescent, [0, 11] {C}(scaleAndSubsystem = Organ.Heart))) = 6.6]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesMeasureTimeSpan) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(timeSpan(ascent, [0, 11] count(clusteredness(clusters)))) = 2]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesMeasureValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] count(clusteredness(clusters)))) = 4.51]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusteredness(clusters)) >= multiply({B}, 0.334))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(clusteredness(clusters)) >= multiply({B}, 0.334)))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(clusteredness(clusters)) >= multiply({B}, 0.334)))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= 1.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d({A}) >=  count(clusteredness(clusters)) ) ^ ( covar(clusteredness(clusters), clusteredness(clusters)) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(CompleteTraceTest, MultipleLogicProperties2) {
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
            "           ) > 0 "
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
            "                   0.142857142857"
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

TEST_F(CompleteTraceTest, NextKLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X [3] (max(clusteredness(clusters)) > 0.282727272727)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X (max(clusteredness(clusters)) > 0.0909090909091)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, ~ (clusteredness > 0)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~(count(clusteredness(clusters)) >= add({A}, 0.2))]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 5] count(clusteredness(clusters))) = 7]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericMeasureCollection) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(clusteredness(clusters)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusteredness(clusters)) <= 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericStateVariableWithoutTypes) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableScaleAndSubsystemLeft) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableScaleAndSubsystemRight) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= {B}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableBothTypes) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {B}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableBothTypesAndDifferentTypeValues) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {C}(scaleAndSubsystem = Organ.Heart)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableOneNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{C}(scaleAndSubsystem = Organ.Heart) = 12]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongRhsType) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Kidney) <= {C}(scaleAndSubsystem = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongLongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongTypeLhs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Heart) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongScaleAndSubsystemLhsLargerValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{B}(scaleAndSubsystem = 213.121) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableScaleAndSubsystemNotInMultiscaleArchitectureGraph) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({D}(scaleAndSubsystem = Organ.Liver) < 5.01) ^ ({D}(scaleAndSubsystem = Organ.Liver) > 4.99))]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableScaleAndSubsystemInMultiscaleArchitectureGraph) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({B}(scaleAndSubsystem = Organ.Kidney) < 3.01) ^ ({B}(scaleAndSubsystem = Organ.Kidney) > 2.99))]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericStatisticalMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X count(clusteredness(clusters)) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// PrimarySpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, PrimarySpatialMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(clusteredness(clusters)) > 0.954535454545]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ProbabilisticLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= div({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// ScaleAndSubsystem
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ScaleAndSubsystem) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.4 [count(clusteredness(filter(clusters, scaleAndSubsystem = Organ.Heart))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SimilarityMeasureAntiSimilar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [opposite(d([0, 11] {A}), d([0, 11] {C} (scaleAndSubsystem = Organ.Heart)), 0)]"));
}

TEST_F(CompleteTraceTest, SimilarityMeasureSimilar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [similar(r([0, 11] count(clusteredness(clusters))), r([0, 11] multiply(count(clusteredness(clusters)), 2)), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SimilarityTemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [similar([0, 11] {B}, [0, 5] 3, 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SpatialMeasureClusteredness) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness <= 0))) > {A}]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, density <= div(1, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureArea) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, area <= div(1E+6, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasurePerimeter) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, perimeter <= div(1E+6, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureDistanceFromOrigin) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, distanceFromOrigin <= div(1E+6, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureAngle) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, angle <= div(360, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureTriangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, triangleMeasure <= div(1, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureRectangleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, rectangleMeasure <= div(1, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCircleMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, circleMeasure <= div(1, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidX) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, centroidX <= div(1E+6, 0.99)))) = 1]"));
}

TEST_F(CompleteTraceTest, SpatialMeasureCentroidY) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, centroidY <= div(1E+6, 0.99)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SpatialMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] max(clusteredness(clusters)) > 0.9999]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) > add(multiply({B}, 0.31), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetOperationDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(difference(clusters, clusters))) = 0]"));
}

TEST_F(CompleteTraceTest, SubsetOperationDifferenceRegion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(difference(regions, clusters))) = 24]"));
}

TEST_F(CompleteTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(intersection(clusters, filter(clusters, clusteredness > 0.908990909091)))) >= 2]"));
}

TEST_F(CompleteTraceTest, SubsetOperationIntersectionRegion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(intersection(clusters, regions))) = 0]"));
}

TEST_F(CompleteTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(union(filter(clusters, clusteredness < 20), filter(clusters, clusteredness >= 20)))) > 10]"));
}

TEST_F(CompleteTraceTest, SubsetOperationUnionRegion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(union(clusters, regions))) = 33]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSpecificClusters) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= 1]"));
}

TEST_F(CompleteTraceTest, SubsetSpecificRegions) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(regions)) = 2]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(clusteredness(union(clusters, clusters))) = count(clusteredness(clusters))]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 11] min(clusteredness(clusters))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericComparison) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusteredness(clusters)) >= 0]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(clusteredness(clusters)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 11] count(clusteredness(clusters))) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeSeriesComponent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [median(enteringValue(uniformAscent, [0, 11] count(clusteredness(clusters)))) > 5]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeSeriesMeasureEnteringTime) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(enteringTime(descent, [0, 11] count(clusteredness(clusters)))) < 10]"));
}

TEST_F(CompleteTraceTest, TimeSeriesMeasureEnteringValue) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(enteringValue(uniformDescent, [0, 11] {C}(scaleAndSubsystem = Organ.Heart))) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeSeriesTimeSeriesComponent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(enteringTime(peak, [0, 11] count(clusteredness(clusters)))) = 6]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(filter(clusters, clusteredness >= floor(clusteredness)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= abs(subtract(3.99, {B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = sqrt(ceil(0.3))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= floor(1.2)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureRound) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = round(-0.005)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = sign(21.1)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) <= sqrt(sqrt(multiply(1, 1)))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) > trunc(1.9999)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 11] count(clusteredness(clusters))) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (max(ceil(clusteredness(clusters))) = 1.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = abs(-1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(clusteredness(filter(clusters, clusteredness < 0))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(clusteredness(clusters)) = 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) >= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureGeomean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(clusteredness(clusters)) <= 0]"), NumericException);
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(clusteredness(clusters)) > 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(clusteredness(clusters)) <= 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(clusteredness(clusters)) = 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(clusteredness(clusters)) <= 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(clusteredness(clusters)) > 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(clusteredness(clusters)) > 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureProduct) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [product(clusteredness(clusters)) >= 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(clusteredness(clusters)) <= 0.0001]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(clusteredness(clusters)) <= add(0, 0.9999)]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(clusteredness(clusters)) >= 0.0001]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(clusteredness(clusters)) < 1e-06]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(clusteredness(clusters)) = 1]"));
}

/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 5] count(clusteredness(clusters))) < 6.01]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryScaleAndSubsystemConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryScaleAndSubsystemConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(clusteredness(filter(clusters, scaleAndSubsystem < Organism.Human))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UntilLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(d(count(clusteredness(clusters))) >= 0) U [0, 2] (count(clusteredness(clusters)) = 3)]"));
}

TEST_F(CompleteTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(d(count(clusteredness(clusters))) >= 0) U [0, 2] (count(clusteredness(clusters)) = 3) <=> {A} = 3]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(count(clusteredness(clusters)))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(clusteredness(clusters)), 2)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueUnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusteredness(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusteredness(filter(clusters, clusteredness < clusteredness)), clusteredness(clusters))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusteredness(clusters), 50)) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(count(clusteredness(clusters)))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(clusteredness(clusters)), 1)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(clusteredness(clusters))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(clusteredness(clusters), 50)) > 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalDecreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(clusteredness(clusters), 50)) < 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(2) > 0) U [0, 10] (d(2) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d({A}) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueNumericStateVariable2) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) >= 0) U [0, 10] (d(count(clusteredness(clusters))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(count(clusteredness(clusters)) >= 0) U [0, 10] (d(add({A}, {B})) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusteredness(clusters)), 1)) > 0) U [0, 10] (d(power(count(clusteredness(clusters)), 1)) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) U [0, 10] (X d(count(clusteredness(filter(clusters, clusteredness >= 0 V clusteredness < 2.0)))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusteredness(clusters), 80)) >= 0) U [0, 10] (d(quartile(clusteredness(clusters), 50)) < 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(d(2) < 0) U [0, 10] (d(4) > 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({C}(scaleAndSubsystem = Organ.Heart)) < 0) U [0, 10] (d({C}(scaleAndSubsystem = Organ.Heart)) > 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) <= 0) U [0, 10] (d(count(clusteredness(clusters))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(clusteredness(clusters))) <= 0) U [0, 10] (d(add(count(clusteredness(clusters)), 2)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(clusteredness(clusters)), 1)) < 0) U [0, 10] (d(power(count(clusteredness(clusters)), 1)) > 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(clusteredness(clusters), clusteredness(clusters))) < 0) U [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(clusteredness(clusters), 80)) < 0) U [0, 10] (d(quartile(clusteredness(clusters), 50)) >= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, OscillationsValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueNumericStateVariableStartingLater) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( ({A} > 1) ^ (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(abs(count(clusteredness(clusters)))) >= 0) ^ F [0, 10] ( (d(abs(count(clusteredness(clusters)))) <= 0) ^ F [0, 10] (d(abs(count(clusteredness(clusters)))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(clusteredness(clusters)), 2)) >= 0) ^ F [0, 10] ( (d(add(count(clusteredness(clusters)), 2)) <= 0) ^ F [0, 10] (d(add(count(clusteredness(clusters)), 2)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(clusteredness(clusters))) >= 0) ^ F [0, 10] ( (d(count(clusteredness(clusters))) <= 0) ^ F [0, 10] (d(count(clusteredness(clusters))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) ^ F [0, 10] ( (d(covar(clusteredness(clusters), clusteredness(clusters))) <= 0) ^ F [0, 10] (d(covar(clusteredness(clusters), clusteredness(clusters))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(clusteredness(clusters), 50)) >= 0) ^ F [0, 10] ( (d(quartile(clusteredness(clusters), 50)) <= 0) ^ F [0, 10] (d(quartile(clusteredness(clusters), 50)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(clusteredness(clusters)) > 0.5)) ^ (count(clusteredness(clusters)) > 100)]"));
}

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(clusteredness(clusters)) > 0.5) ^ ((count(clusteredness(clusters)) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(clusteredness(clusters)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(clusteredness(clusters)) > add(add({A}, {A}), {B}))]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, clusteredness > 0.25))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, clusteredness > 0.25 ^ clusteredness > 50.0))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(clusteredness(filter(clusters, (clusteredness > 0.25) ^ ((clusteredness > 50.0) V (clusteredness > 5.0 V clusteredness < 10.0))))) > add(add({A}, {A}), {B}))]"));
}


#endif