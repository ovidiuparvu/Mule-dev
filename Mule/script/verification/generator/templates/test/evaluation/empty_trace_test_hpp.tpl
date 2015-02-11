#ifndef EMPTYTRACETEST_HPP
#define EMPTYTRACETEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

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
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5)))) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= add(1, 0.0001)]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min([0, 3] power({B}, 1.3)) <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericSpatial) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [0, 11] (sum(multiply(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1375.76)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryNumericTemporal) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [power({B}, 1.3) <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.0005]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg([0, 1] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, BinaryStatisticalSpatial) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [mode([0, 10] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.0005]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ChangeMeasureDifference) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ChangeMeasureRatio) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [r(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 4]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ChangeTemporalNumericCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(d([0, 11] {C}(type = Organ.Heart))) = -9]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ComparatorGreaterThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorLessThan) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ComparatorEqual) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 3]"), SpatialTemporalException);
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
        EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1)))) <= 3]"), SpatialTemporalException);
    }
}

TEST_F(EmptyTraceTest, CompoundConstraintMultiple) {
    const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) <= 3]"), SpatialTemporalException);
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
        EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0) ]"), SpatialTemporalException);
    }
}

TEST_F(EmptyTraceTest, CompoundLogicPropertyMultiple) {
    const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});

    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 0) " + binaryOperator + " {B} = 3]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2))))) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ <= 30.2))))))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, Constraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 10000 V /*{{ spatial_measures[0].name }}*/ <= 1))) = 1]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FilterNumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5) ^ /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].name }}*/))) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, FilterSubset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 0))) <= 1]"), SpatialTemporalException);
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
// HeterogeneousTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, HeterogeneousTimeseriesComponentPeak) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(enteringValue(peak, [0, 11] {A})) = 4]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HeterogeneousTimeseriesComponentValley) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(enteringValue(valley, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousHomogeneousTimeseries
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, HomogeneousHomogeneousTimeseries) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(timeSpan(plateau, [0, 11] {B})) = 12]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, HomogeneousTimeseriesComponentAscent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(values(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HomogeneousTimeseriesComponentDescent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] {C}(type = Organ.Heart))) = 7.5]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HomogeneousTimeseriesComponentPlateau) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(values(plateau, [0, 11] {B})) = 2.999]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HomogeneousTimeseriesComponentUniformAscent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max(values(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 11]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HomogeneousTimeseriesComponentUniformDescent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(values(uniformDescent, [0, 11] {C}(type = Organ.Heart))) = 6.6]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeseriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, HomogeneousTimeseriesMeasureTimeSpan) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(timeSpan(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, HomogeneousTimeseriesMeasureValue) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 4.51]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, MultipleLogicProperties1) {
    EXPECT_THROW(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) ) ^ ( covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, MultipleLogicProperties2) {
    EXPECT_THROW(
        RunEvaluationTest(""
            "P <= 0.85934 ["
            "   (~ "
            "       F [2, 3] ( "
            "           max("
            "               /*{{ spatial_measures[0].name }}*/("
            "                   filter("
            "                       /*{{ spatial_entities[0].name }}*/s, "
            "                       /*{{ spatial_measures[0].name }}*/ <= 10"
            "                   )"
            "               )"
            "           ) >= 2 "
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
            "       ) >= 1"
            "   ) U [3, 7] ( "
            "       kurt("
            "           /*{{ spatial_measures[0].name }}*/("
            "               /*{{ spatial_entities[0].name }}*/s"
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
        ), 
        SpatialTemporalException
    );
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
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= -0.22)))) <= 1]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 4]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericMeasureCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= add(2, 3)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericSpatialMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 0.5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericStateVariableWithoutTypes) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableTypeLeft) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableTypeRight) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= {B}(type = Organ.Kidney)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableBothTypes) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {B}(type = Organ.Kidney)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableBothTypesAndDifferentTypeValues) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {C}(type = Organ.Heart)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableOneNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{C}(type = Organ.Heart) = 12]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableWrongRhsType) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {C}(type = Organ.Kidney)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableWrongName) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableWrongLongName) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableWrongTypeLhs) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Heart) <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableWrongTypeLhsLargerValue) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{B}(type = 213121) <= {B}]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableSemanticTypeNotInTypeSemanticsTable) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] (({D}(type = Organ.Liver) < 5.01) ^ ({D}(type = Organ.Liver) > 4.99))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, NumericStateVariableTypeInTypeSemanticsTable) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [G [0, 11] (({B}(type = Organ.Kidney) < 3.01) ^ ({B}(type = Organ.Kidney) > 2.99))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// NumericStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, NumericStatisticalMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X min([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// PrimarySpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, PrimarySpatialMeasureCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 12]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ProbabilisticLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SemanticType
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SemanticType) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.4 [{C}(type = Organ.Heart) = 12]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SimilarityMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SimilarityMeasureAntiSimilar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [opposite(d([0, 11] {A}), d([0, 11] {C}), 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SimilarityMeasureSimilar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [similar(r([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))), r([0, 11] multiply(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)), 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SimilarityTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SimilarityTemporalNumericCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [similar([0, 11] {B}, [0, 5] 3, 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SpatialMeasure/*{{ spatial_measures[0].name|first_to_upper }}*/) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), SpatialTemporalException);
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST_F(EmptyTraceTest, SpatialMeasure/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= 30.2))) <= 3]"), SpatialTemporalException);
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SpatialMeasureCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 27.3999]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, Subset) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetOperationDifference) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SubsetOperationIntersection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, SubsetOperationUnion) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetSpecific/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"), SpatialTemporalException);
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST_F(EmptyTraceTest, SubsetSpecific/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entity.name }}*/s)) <= 3]"), SpatialTemporalException);
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, SubsetSubsetOperation) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TemporalNumericCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max([0, 11] min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TemporalNumericComparison) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} >= 4.2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TemporalNumericMeasure) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TemporalNumericMeasureCollection) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 11]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TimeseriesComponent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [median(enteringValue(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 5]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TimeseriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TimeseriesMeasureEnteringTime) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max(enteringTime(descent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) < 10]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, TimeseriesMeasureEnteringValue) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(enteringValue(uniformDescent, [0, 11] {C})) = 3]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// TimeseriesTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TimeseriesTimeseriesComponent) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(enteringTime(peak, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 6]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericFilter) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= round(/*{{ spatial_measures[0].name }}*/)))) > 0]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= ceil(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= floor(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureRound) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureSign) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= sign(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= sqrt(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= trunc(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max([0, 11] {A}) <= abs(3.0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericSpatial) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [F [0, 11] (max(ceil(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 28)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryNumericTemporal) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [{A} <= abs(1.0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnarySpatialConstraint) {
    EXPECT_THROW(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 1))) >= 1]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureAvg) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureCount) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureGeomean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureHarmean) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [harmean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureKurt) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [kurt(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureMax) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureMedian) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [median(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureMin) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureMode) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureProduct) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [product(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureSkew) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [skew(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureStdev) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [stdev(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureSum) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UnaryStatisticalMeasureVar) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [var(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), SpatialTemporalException);
}

/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryStatisticalSpatial) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 6.01]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UnaryTypeConstraint) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, type < 1))) = 1]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, UntilLogicProperty) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 4) <=> {B} = 3]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < 1)), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalConstantValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) = 0)]"), SpatialTemporalException);
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
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, FutureIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) > 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, GlobalDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, GlobalDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) < 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(2) > 0) U [0, 10] (d(2) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d({A}) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueNumericStateVariable2) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({A}) > 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0) U [0, 10] (d(add({A}, {B})) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0) U [0, 10] (d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (d(avg(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000)))) < 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, IncreasingUntilDecreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 80)) >= 0) U [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) < 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(2) < 0) U [0, 10] (d(4) >= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d({C}(type = Organ.Heart)) < 0) U [0, 10] (d({C}(type = Organ.Heart)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) U [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 0) U [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) < 0) U [0, 10] (d(power(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 1)) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0) U [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, DecreasingUntilIncreasingValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 80)) < 0) U [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, OscillationsValueNumericStateVariable) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueNumericStateVariableStartingLater) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( ({A} > 1) ^ (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 0) ^ F [0, 10] ( (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) <= 0) ^ F [0, 10] (d(abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0) ^ F [0, 10] ( (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) <= 0) ^ F [0, 10] (d(add(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueUnaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) ^ F [0, 10] (d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueBinaryStatisticalNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0) ^ F [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, OscillationsValueBinaryStatisticalQuantileNumeric) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0) ^ F [0, 10] ( (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) <= 0) ^ F [0, 10] (d(quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50)) >= 0) ) )]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [((avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10)) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10) ^ ((count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100))]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [5, 10] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10)]"), SpatialTemporalException);
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(EmptyTraceTest, ConstraintsCombinationUnary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5))) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintsCombinationBinary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 ^ /*{{ spatial_measures[0].name }}*/ > 1000))) > 10)]"), SpatialTemporalException);
}

TEST_F(EmptyTraceTest, ConstraintsCombinationNary) {
    EXPECT_THROW(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ > 5) ^ ((/*{{ spatial_measures[0].name }}*/ > 1000) V (/*{{ spatial_measures[0].name }}*/ > 100 V /*{{ spatial_measures[0].name }}*/ < 210))))) > 10)]"), SpatialTemporalException);
}


#endif
