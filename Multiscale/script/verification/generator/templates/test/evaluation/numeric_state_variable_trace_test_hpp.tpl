#ifndef NUMERICSTATEVARIABLETRACETEST_HPP
#define NUMERICSTATEVARIABLETRACETEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

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
        trace.clear();

        std::vector<TimePoint> timePoints;

        for (int i = 0; i <= 11; i++) {
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
        timePoints[11].addNumericStateVariable("A", 12);

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

TEST_F(NumericStateVariableTraceTest, BinaryNumericFilter) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5))) > 0]"));
}


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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= mod(4, 8)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= multiply(2, 3)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= power(2, 3)]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= subtract(3, 6)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg([0, 3] multiply({A}, 2)) <= add(9, 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryNumericTemporal) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subtract({A}, 2) >= add(2, -0.111111)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalQuantileMeasurePercentile) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= {B}]"));
}

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [mode([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinaryStatisticalSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 7] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 0]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ChangeMeasureDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d({A}) >= 1]"));
}

TEST_F(NumericStateVariableTraceTest, ChangeMeasureRatio) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [r({B}) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d({A}) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > {A}]"));
}

TEST_F(NumericStateVariableTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < {A}]"));
}

TEST_F(NumericStateVariableTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [{A} <= 3]"));
}

TEST_F(NumericStateVariableTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [{A} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) V (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) => (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1) ^ (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) V (/*{{ spatial_measures[0].name }}*/ = 0.1) V (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) => (/*{{ spatial_measures[0].name }}*/ = 0.1) => (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= {A}]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= {A}) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1) <=> (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) ^ (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [({A} >= 4) V (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) => (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) <=> (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}

TEST_F(NumericStateVariableTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) ^ (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ^ (count(/*{{ spatial_entities[0].name }}*/s) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [({A} >= 4) V (count(/*{{ spatial_entities[0].name }}*/s) >= 4) V (count(/*{{ spatial_entities[0].name }}*/s) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [({A} >= 4) => (count(/*{{ spatial_entities[0].name }}*/s) >= 4) => (count(/*{{ spatial_entities[0].name }}*/s) <= 4) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) <=> (count(/*{{ spatial_entities[0].name }}*/s) >= 4) <=> (count(/*{{ spatial_entities[0].name }}*/s) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ <= 30.2)))))) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Difference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [d({A}) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5) ^ /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].name }}*/)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [2, 3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [({A} >= 4)]"));
}

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(({A} >= 4))]"));
}

TEST_F(NumericStateVariableTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(((({A} >= 4))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, LogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(/*{{ spatial_entities[0].name }}*/s) ) ^ ( covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(NumericStateVariableTraceTest, MultipleLogicProperties2) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 10), /*{{ spatial_measures[0].name }}*/) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 0.4) = 0.7 ))) ) <=> ( (subsetClusteredness(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 2) ^ (/*{{ spatial_measures[0].name }}*/ >= 6) V (/*{{ spatial_measures[0].name }}*/ >= 30) => (/*{{ spatial_measures[0].name }}*/ <= 2) <=> (/*{{ spatial_measures[0].name }}*/ >= 4)) ) >= 2) U [3, 7] ( kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A} ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~({A} >= 4.2)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= {A})]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericSpatialMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= add({A}, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) >= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, NumericStateVariable1) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= 3]"));
}

TEST_F(NumericStateVariableTraceTest, NumericStateVariable2) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= 3]"));
}

TEST_F(NumericStateVariableTraceTest, NumericStateVariable3) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ProbabilisticLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SpatialMeasure/*{{ spatial_measures[0].name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= {A}]"));
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST_F(NumericStateVariableTraceTest, SpatialMeasure/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= 30.2)) <= {A}]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SubsetOperationDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) > 10]"));
}

TEST_F(NumericStateVariableTraceTest, SubsetOperationIntersection) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) >= 3]"));
}

TEST_F(NumericStateVariableTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 21]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SubsetSpecific/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= {B}]"));
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST_F(NumericStateVariableTraceTest, SubsetSpecific/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entity.name }}*/s) <= {B}]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, SubsetSubsetOperation) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) >= 4.3]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryTypeConstraint) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, type = 0)) > 7]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryNumericFilter) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < trunc(/*{{ spatial_measures[0].name }}*/))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= abs(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= ceil(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= floor(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureRound) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= round(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureSign) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= sign(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= sqrt(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(NumericStateVariableTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= trunc(count(/*{{ spatial_entities[0].name }}*/s))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnaryNumericNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A} <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [harmean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMin) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureMode) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [product(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureSum) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, BinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= {A}]"));
}

TEST_F(NumericStateVariableTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= {A}]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= {B}]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, UntilLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}

TEST_F(NumericStateVariableTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Constant value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) = 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) = 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueReal) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(2) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d({A}) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round({A})) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add({A}, {B})) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) > 0)]"));
}

TEST_F(NumericStateVariableTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) > 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(2) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueNumericStateVariable) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d({A}) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueUnaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(round({A})) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d(2) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) >= 0) U [0, 10] (d({B}) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(sign(-4)) >= 0) U [0, 10] (d(round({A})) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) >= 0) U [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) >= 0) U [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 80)) >= 0) U [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) <= 0) U [0, 10] (d(2) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({A}) <= 0) U [0, 10] (d({B}) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(sign(-4)) <= 0) U [0, 10] (d(round({A})) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= 0) U [0, 10] (d(add({A}, {B})) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power({A}, {B})) <= 0) U [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply({A}, 2)) <= 0) U [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 80)) <= 0) U [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0)]"));
}

TEST_F(NumericStateVariableTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Oscillations
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, OscillationValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d({A}) >= 0) ^ F [0, 10] ( (d({A}) <= 0) ^ F [0, 10] (d({A}) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round({A})) >= 0) ^ F [0, 10] ( (d(round({A})) <= 0) ^ F [0, 10] (d(round({A})) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add({A}, {B})) >= 0) ^ F [0, 10] ( (d(add({A}, {B})) <= 0) ^ F [0, 10] (d(add({A}, {B})) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) ^ F [0, 10] ( (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) ^ F [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0) ^ F [0, 10] ( (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) <= 0) ^ F [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0) ^ F [0, 10] ( (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0) ^ F [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0) ) )]"));
}

TEST_F(NumericStateVariableTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0) ^ F [0, 10] ( (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0) ^ F [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) > {B}) ^ (count(/*{{ spatial_entities[0].name }}*/s) < 1)) V (subsetDensity(/*{{ spatial_entities[0].name }}*/s) > 100)]"));
}

TEST_F(NumericStateVariableTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) > {B}) ^ ((count(/*{{ spatial_entities[0].name }}*/s) < 1) V (subsetDensity(/*{{ spatial_entities[0].name }}*/s) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(/*{{ spatial_entities[0].name }}*/s) > {B})]"));
}

TEST_F(NumericStateVariableTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(/*{{ spatial_entities[0].name }}*/s) > {B})]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5)) > {B})]"));
}

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > {B} ^ /*{{ spatial_measures[0].name }}*/ > 1000)) > 10)]"));
}

TEST_F(NumericStateVariableTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ > {B}) ^ ((/*{{ spatial_measures[0].name }}*/ > 1000) V (/*{{ spatial_measures[0].name }}*/ > 100 V /*{{ spatial_measures[0].name }}*/ < 210)))) > 10)]"));
}


#endif
