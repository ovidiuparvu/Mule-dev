#ifndef SPATIALENTITIESTRACETEST_HPP
#define SPATIALENTITIESTRACETEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
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

            // Add /*{{ spatial_entities[0].name }}*/s to the timepoint
            for (int k = ((((i + 1) % 4) == 0) ? (i - 1) : 0); k < i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entities[0].name }}*/ = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();

                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((k * 2.4) + 1));
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>((/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 2));
            /*{% endfor %}*/

                timePoints[i].addSpatialEntity(/*{{ spatial_entities[0].name }}*/, SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureAdd) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= add(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureDiv) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) > div(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureLog) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= log(4.33333, 9.12312312)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMod) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= mod(4, 8)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureMultiply) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= multiply(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= power(2, 3)]"));
}

TEST_F(SpatialEntitiesTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 1)) > subtract(3, 6)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= power(6, 7)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMin) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureProduct) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [product(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.432]"));
}

TEST_F(SpatialEntitiesTraceTest, BinarySubsetMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, BinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThan) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) > 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThan) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) < 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorGreaterThanOrEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) >= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorLessThanOrEqual) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ComparatorEqual) {
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) V (/*{{ spatial_measures[0].name }}*/ = 0.3))) = 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) => (/*{{ spatial_measures[0].name }}*/ = 0.1))) > 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1) ^ (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) V (/*{{ spatial_measures[0].name }}*/ = 0.1) V (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) => (/*{{ spatial_measures[0].name }}*/ = 0.1) => (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= 3]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1) <=> (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) ^ (count(/*{{ spatial_entities[0].name }}*/s) >= 2)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) V (count(/*{{ spatial_entities[0].name }}*/s) <= 4)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) => (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) <=> (count(/*{{ spatial_entities[0].name }}*/s) <= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) ^ (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ^ (count(/*{{ spatial_entities[0].name }}*/s) <= 4) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) V (count(/*{{ spatial_entities[0].name }}*/s) >= 4) V (count(/*{{ spatial_entities[0].name }}*/s) <= 4) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) => (count(/*{{ spatial_entities[0].name }}*/s) >= 4) => (count(/*{{ spatial_entities[0].name }}*/s) <= 4) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 100) <=> (count(/*{{ spatial_entities[0].name }}*/s) >= 4) <=> (count(/*{{ spatial_entities[0].name }}*/s) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ >= 30.2)))) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ >= 30.2)))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Difference
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Difference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0.99]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterNumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, 2.5) ^ /*{{ spatial_measures[0].name }}*/ > /*{{ spatial_measures[0].name }}*/)) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, FutureLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, GlobalLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) > 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParentheses) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesDoubled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((count(/*{{ spatial_entities[0].name }}*/s) >= 4))]"));
}

TEST_F(SpatialEntitiesTraceTest, LogicPropertyEnclosedByParenthesesQuadrupled) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [((((count(/*{{ spatial_entities[0].name }}*/s) >= 4))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, LogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties1) {
    EXPECT_FALSE(RunEvaluationTest("P > 0.1234 [( d(4) >=  count(/*{{ spatial_entities[0].name }}*/s) ) ^ ( covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST_F(SpatialEntitiesTraceTest, MultipleLogicProperties2) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.85934 [~( F [2, 3] ( max(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 10), /*{{ spatial_measures[0].name }}*/) >= 2 ) ) => ( G [4, 5] (X (X [5] ( percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 0.4) = 0.7 ))) ) <=> ( (subsetClusteredness(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 2) ^ (/*{{ spatial_measures[0].name }}*/ >= 6) V (/*{{ spatial_measures[0].name }}*/ >= 30) => (/*{{ spatial_measures[0].name }}*/ <= 2) <=> (/*{{ spatial_measures[0].name }}*/ >= 4)) ) >= 2) U [3, 7] ( kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 0.00001 ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextKLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X [3] (max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 1)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NotLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [~(count(/*{{ spatial_entities[0].name }}*/s) >= 4.2)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialMeasure) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, NumericSpatialNumericComparison) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) >= 4.2]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, QuaternarySubsetCovar) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, QuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SpatialMeasure/*{{ spatial_measures[0].name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) < 1]"));
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST_F(SpatialEntitiesTraceTest, SpatialMeasure/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= 30.2)) < 1]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetOperationDifference) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) >= 11]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationIntersection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

TEST_F(SpatialEntitiesTraceTest, SubsetOperationUnion) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 21]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSpecific/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST_F(SpatialEntitiesTraceTest, SubsetSpecific/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entity.name }}*/s) <= 3]"));
}

/*{% endfor %}*/


/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, SubsetSubsetOperation) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) >= 4.3]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, Subset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TernarySubsetMeasurePercentile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"));
}

TEST_F(SpatialEntitiesTraceTest, TernarySubsetMeasureQuartile) {
    EXPECT_THROW(RunEvaluationTest("P >= 0.3 [X[4] quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), NumericException);
}


/////////////////////////////////////////////////////////
//
//
// TernarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryTypeConstraint) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, type = 1)) > 7]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySpatialConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericFilter) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [1, 11] count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < round(/*{{ spatial_measures[0].name }}*/))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureAbs) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= abs(-3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureCeil) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= ceil(0.3)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureFloor) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= floor(0.49)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureRound) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) >= round(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSign) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= sign(21.1)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureSqrt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= sqrt(2)]"));
}

TEST_F(SpatialEntitiesTraceTest, UnaryNumericMeasureTrunc) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= trunc(1.1)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnaryNumericNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureClusteredness) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}

TEST_F(SpatialEntitiesTraceTest, UnarySubsetMeasureDensity) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubset
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, UntilLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= 1) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}

TEST_F(SpatialEntitiesTraceTest, UntilLogicPropertyMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) < 10) U [2, 8] (count(/*{{ spatial_entities[0].name }}*/s) >= 4) U [2, 6] (count(/*{{ spatial_entities[0].name }}*/s) <= 4)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [1, 10] (d(round(subsetDensity(/*{{ spatial_entities[0].name }}*/s))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(add(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueUnarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) = 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalConstantValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(round(subsetDensity(/*{{ spatial_entities[0].name }}*/s))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(add(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(subsetDensity(/*{{ spatial_entities[0].name }}*/s)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) > 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, FutureIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) = 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueBinarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5), /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueTernarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, GlobalDecreasingValueQuaternarySubset) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Increasing and then decreasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) U [0, 10] (d(2) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) U [0, 10] (d(4) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) U [0, 10] (d(round(2)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinaryNumeric) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) >= 0) U [0, 10] (d(add({A}, {B})) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(/*{{ spatial_entities[0].name }}*/s), 2)) >= 0) U [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 80)) >= 0) U [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, IncreasingUntilDecreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) >= 0) U [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0)]"));
}


/////////////////////////////////////////////////////////
//
//
// Decreasing and then increasing value
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueReal) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) U [0, 10] (d(2) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) U [0, 10] (d(4) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) U [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= 0) U [0, 10] (d(add(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(power(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) <= 0) U [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(multiply(count(/*{{ spatial_entities[0].name }}*/s), 2)) <= 0) U [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 80)) <= 0) U [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0)]"));
}

TEST_F(SpatialEntitiesTraceTest, DecreasingUntilIncreasingValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(1231.3) <= 0) U [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(round(count(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(round(count(/*{{ spatial_entities[0].name }}*/s))) <= 0) ^ F [0, 10] (d(round(count(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinaryNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(add(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) >= 0) ^ F [0, 10] ( (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) ^ F [0, 10] (d(add(count(/*{{ spatial_entities[0].name }}*/s), count(/*{{ spatial_entities[0].name }}*/s))) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueUnarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) ^ F [0, 10] ( (d(count(/*{{ spatial_entities[0].name }}*/s)) <= 0) ^ F [0, 10] (d(count(/*{{ spatial_entities[0].name }}*/s)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueBinarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0) ^ F [0, 10] ( (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) <= 0) ^ F [0, 10] (d(avg(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000), /*{{ spatial_measures[0].name }}*/)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueTernarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0) ^ F [0, 10] ( (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) <= 0) ^ F [0, 10] (d(quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 50)) >= 0) ) )]"));
}

TEST_F(SpatialEntitiesTraceTest, OscillationsValueQuaternarySubset) {
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [F [0, 10] ( (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0) ^ F [0, 10] ( (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 0) ^ F [0, 10] (d(covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) >= 0) ) )]"));
}


/////////////////////////////////////////////////////////
//
//
// Enclosing composed statements differently with parentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently1) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) > 10) ^ (count(/*{{ spatial_entities[0].name }}*/s) < 1)) V (subsetDensity(/*{{ spatial_entities[0].name }}*/s) > 100)]"));
}

TEST_F(SpatialEntitiesTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) > 10) ^ ((count(/*{{ spatial_entities[0].name }}*/s) < 1) V (subsetDensity(/*{{ spatial_entities[0].name }}*/s) > 100))]"));
}


/////////////////////////////////////////////////////////
//
//
// Time interval exceeds trace time at start or end
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceEndTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 1000] (count(/*{{ spatial_entities[0].name }}*/s) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, TimeIntervalExceedsTraceStartTime) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [5, 10] (count(/*{{ spatial_entities[0].name }}*/s) > 10)]"));
}


/////////////////////////////////////////////////////////
//
//
// Different constraints combinations
//
//
/////////////////////////////////////////////////////////

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationUnary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 ^ /*{{ spatial_measures[0].name }}*/ > 1000)) > 10)]"));
}

TEST_F(SpatialEntitiesTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ > 5) ^ ((/*{{ spatial_measures[0].name }}*/ > 1000) V (/*{{ spatial_measures[0].name }}*/ > 100 V /*{{ spatial_measures[0].name }}*/ < 210)))) > 10)]"));
}


#endif
