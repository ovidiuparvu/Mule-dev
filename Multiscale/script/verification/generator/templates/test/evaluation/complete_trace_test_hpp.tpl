#ifndef COMPLETETRACETEST_HPP
#define COMPLETETRACETEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > subtract(/*{{ spatial_measures[0].name }}*/, 0.00001)))) > /*{{ nr_of_time_points|int - 2 }}*/]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > div({B}, subtract({B}, 0.1))]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureLog) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= log({A}, 3)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= mod({A}, {B})]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.33 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({A}, 1)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= power(2, 0)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].max_value }}*/))) = subtract({A}, {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 5] add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 7.99999]"));
}

/////////////////////////////////////////////////////////
//
//
// BinaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (sum(multiply(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > /*{{ (spatial_measures[0].max_value|float ** 2) + ((spatial_measures[0].max_value|float ** 2) * ((nr_of_time_points|int - 2) ** 2) / ((nr_of_time_points|int - 1) ** 2)) }}*/)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [multiply(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2) >= 1.99999]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, div({A}, div({A}, 2)))]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X[4] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 100) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 4 / (nr_of_time_points|int - 1) }}*/]"));
}

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50) <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 1 / (nr_of_time_points|int - 1) }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 79.4) = /*{{ spatial_measures[0].min_value }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 2] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 90)) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 2 / (nr_of_time_points|int - 1) }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 6] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeMeasureDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < /*{{ (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / nr_of_time_points|int }}*/]"));
}

TEST_F(CompleteTraceTest, ChangeMeasureRatio) {
/*{% if spatial_measures[0].min_value|float == 0 %}*/
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [r(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0]"));
/*{% else %}*/
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [r(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) */ < /*{{ spatial_measures[0].max_value|float / spatial_measures[0].min_value|float }}*/]"));
/*{% endif %}*/
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / (nr_of_time_points|int - 1) }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > subtract({B}, 1.99999)]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < log({A}, 2)]"));
}

TEST_F(CompleteTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= add({A}, 0.0001)]"));
}

TEST_F(CompleteTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= trunc(subtract({B}, 1.0001))]"));
}

TEST_F(CompleteTraceTest, ComparatorEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = ceil(subtract({A}, 0.00001))]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/) ^ (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/)))) = 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/) V (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) * 3 }}*/)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/) => (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/)))) > 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/) <=> (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/)))) = 0]"));
}

TEST_F(CompleteTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (1100000) }}*/) ^ (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/) ^ (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) < 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (1100000) }}*/) V (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/) V (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) = 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (1100000) }}*/) => (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/) => (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (1100000) }}*/) <=> (/*{{ spatial_measures[0].name }}*/ = /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110) }}*/) <=> (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, 2))]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/) V (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/) => (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/) <=> (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, div({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/) V (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/) => (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/) <=> (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/)))) = 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/))))) < 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 1) / (110000) }}*/))))))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].max_value }}*/ V /*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, -0.1) ^ /*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].min_value }}*/))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].min_value|float - 1 }}*/))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > add(power({A}, 1), -1))]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, GlobalLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= ceil(div({A}, 2)))]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(enteringValue(valley, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 2]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(values(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] {C}(scaleAndSubsystem = Organ.Heart))) = 7.5]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentPlateau) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(values(plateau, [0, 11] {B})) = 2.999]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesComponentUniformAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(values(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 11]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(timeSpan(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 2]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeSeriesMeasureValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 4.51]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({B}, 0.334))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({B}, 0.334)))]"));
}

TEST_F(CompleteTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({B}, 0.334)))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d({A}) >=  count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) ) ^ ( covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(CompleteTraceTest, MultipleLogicProperties2) {
    EXPECT_TRUE(
        RunEvaluationTest(""
            "P <= 0.85934 ["
            "   (~ "
            "       F [2, 3] ( "
            "           max("
            "               /*{{ spatial_measures[0].name }}*/("
            "                   filter("
            "                       /*{{ spatial_entities[0].name }}*/s, "
            "                       /*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 4 }}*/"
            "                   )"
            "               )"
            "           ) > /*{{ spatial_measures[0].min_value }}*/ "
            "       ) "
            "   ) => ( "
            "       G [4, 5] ("
            "           X ("
            "               X [5] ( "
            "                   percentile("
            "                       /*{{ spatial_measures[0].name }}*/("
            "                           /*{{ spatial_entities[0].name }}*/s"
            "                       ), "
            "                       0.4"
            "                   ) = 0.7 "
            "               )"
            "           )"
            "       ) "
            "   ) <=> ( "
            "       count("
            "           /*{{ spatial_measures[0].name }}*/("
            "               filter("
            "                   /*{{ spatial_entities[0].name }}*/s, "
            "                   (/*{{ spatial_measures[0].name }}*/ <= 2) ^ "
            "                   (/*{{ spatial_measures[0].name }}*/ >= 6) V "
            "                   (/*{{ spatial_measures[0].name }}*/ >= 30) => "
            "                   (/*{{ spatial_measures[0].name }}*/ <= 2) <=> "
            "                   (/*{{ spatial_measures[0].name }}*/ >= 4)"
            "               ) "
            "           )"
            "       ) >= 0"
            "   ) U [3, 7] ( "
            "       kurt("
            "           /*{{ spatial_measures[0].name }}*/("
            "               /*{{ spatial_entities[0].name }}*/s"
            "           )"
            "       ) <= sqrt("
            "           sqrt("
            "               sqrt("
            "                   /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 7 }}*/"
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X [3] (max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ (spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 3 / (nr_of_time_points|int - 1)) + 0.01 }}*/)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X (max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ (spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / (nr_of_time_points|int - 1)) }}*/)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value }}*/)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= add({A}, 0.2))]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 7]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericMeasureCollection) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value }}*/]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// PrimarySpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, PrimarySpatialMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ (spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 21 / (2 * (nr_of_time_points|int - 1))) - 0.00001 }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ProbabilisticLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// ScaleAndSubsystem
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ScaleAndSubsystem) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.4 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem = Organ.Heart))) > 0]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [similar(r([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))), r([0, 11] multiply(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)), 0)]"));
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

TEST_F(CompleteTraceTest, SpatialMeasure/*{{ spatial_measures[0].name|first_to_upper }}*/) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= /*{{ spatial_measures[0].min_value }}*/))) > {A}]"));
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST_F(CompleteTraceTest, SpatialMeasure/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= div(/*{{ spatial_measure.max_value }}*/, 0.99)))) = 1]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SpatialMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].max_value|float - 0.0001 }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > add(multiply({B}, 0.31), 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetOperationDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) = 0]"));
}

/*{% if spatial_entities[1] %}*/
TEST_F(CompleteTraceTest, SubsetOperationDifference/*{{ spatial_entities[1].name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(difference(/*{{ spatial_entities[1].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) = 24]"));
}
/*{% endif %}*/

TEST_F(CompleteTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(intersection(/*{{ spatial_entities[0].name }}*/s, filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > /*{{ (spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * (nr_of_time_points|int - 2) / (nr_of_time_points|int - 1)) - 0.0001 }}*/)))) >= 2]"));
}

/*{% if spatial_entities[1] %}*/
TEST_F(CompleteTraceTest, SubsetOperationIntersection/*{{ spatial_entities[1].name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[1].name }}*/s))) = 0]"));
}
/*{% endif %}*/

TEST_F(CompleteTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(union(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < 20), filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 20)))) > 10]"));
}

/*{% if spatial_entities[1] %}*/
TEST_F(CompleteTraceTest, SubsetOperationUnion/*{{ spatial_entities[1].name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[1].name }}*/s))) = 33]"));
}
/*{% endif %}*/


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSpecific/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"));
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST_F(CompleteTraceTest, SubsetSpecific/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entity.name }}*/s)) = 2]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) = count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 11] min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = /*{{ spatial_measures[0].min_value }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericComparison) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericMeasureCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeSeriesComponent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [median(enteringValue(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 5]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeSeriesMeasureEnteringTime) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(enteringTime(descent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) < 10]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(enteringTime(peak, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 6]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= floor(/*{{ spatial_measures[0].name }}*/)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= abs(subtract(3.99, {B}))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = sqrt(ceil(0.3))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= floor(1.2)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureRound) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = round(-0.005)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = sign(21.1)]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= sqrt(sqrt(multiply(1, 1)))]"));
}

TEST_F(CompleteTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > trunc(1.9999)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (max(ceil(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = /*{{ spatial_measures[0].max_value|float|round(0, method='ceil') }}*/)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = abs(-1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < /*{{ spatial_measures[0].min_value }}*/))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureGeomean) {
/*{% if spatial_measures[0].min_value|float == 0 %}*/
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value }}*/]"), NumericException);
/*{% else %}*/
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value }}*/]"));
/*{% endif %}*/
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureProduct) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [product(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= /*{{ spatial_measures[0].min_value|float + 0.0001 }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= add(/*{{ spatial_measures[0].min_value }}*/, 0.9999)]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= /*{{ spatial_measures[0].min_value|float + 0.0001 }}*/]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < /*{{ spatial_measures[0].min_value|float + 0.000001 }}*/]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 1]"));
}

/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 6.01]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryScaleAndSubsystemConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryScaleAndSubsystemConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem < Organism.Human))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UntilLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 2] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 3)]"));
}

TEST_F(CompleteTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 2] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 3) <=> {A} = 3]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueUnaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < /*{{ spatial_measures[0].name }}*/)), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0)]"));
}

TEST_F(CompleteTraceTest, GlobalConstantValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0)]"));
}

TEST_F(CompleteTraceTest, FutureIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) > 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"));
}

TEST_F(CompleteTraceTest, GlobalDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) < 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0) U [0, 10] (d(add({A}, {B})) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0) U [0, 10] (d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (X d(count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].min_value }}*/ V /*{{ spatial_measures[0].name }}*/ < /*{{ spatial_measures[0].max_value|float + 1 }}*/)))) < 0)]"));
}

TEST_F(CompleteTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 80)) >= 0) U [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) < 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) U [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) < 0) U [0, 10] (d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0) U [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0)]"));
}

TEST_F(CompleteTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 80)) < 0) U [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 0) ^ F [0, 10] ( (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) <= 0) ^ F [0, 10] (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0) ^ F [0, 10] ( (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) <= 0) ^ F [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueUnaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) ^ F [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) ^ F [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"));
}

TEST_F(CompleteTraceTest, OscillationsValueBinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0) ^ F [0, 10] ( (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) <= 0) ^ F [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/)) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100)]"));
}

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/) ^ ((count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > add(add({A}, {A}), {B}))]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 4 }}*/))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 4 }}*/ ^ /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 50 }}*/))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 4 }}*/) ^ ((/*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 50 }}*/) V (/*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 5 }}*/ V /*{{ spatial_measures[0].name }}*/ < /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) * 10 }}*/))))) > add(add({A}, {A}), {B}))]"));
}


#endif
