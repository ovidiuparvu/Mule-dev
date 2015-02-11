#ifndef COMPLETETRACETEST_HPP
#define COMPLETETRACETEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "TraceEvaluationTest.hpp"
 
/*{% for spatial_entity in spatial_entities %}*/
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entity.name|first_to_upper }}*/.hpp"
/*{% endfor %}*/
 
#include <algorithm>

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing evaluation of complete traces containing both numeric state variables and spatial entities
    class CompleteTraceTest : public TraceEvaluationTest {

        protected:
            
            double /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue;  /*!< The minimum /*{{ spatial_measures[0].name }}*/ value for the /*{{ spatial_entities[0].name }}*/ spatial entity type */
            double /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue;  /*!< The maximum /*{{ spatial_measures[0].name }}*/ value for the /*{{ spatial_entities[0].name }}*/ spatial entity type */
            
        private:

           //! Initialise the trace
           virtual void InitialiseTrace() override;

    };

    void CompleteTraceTest::InitialiseTrace() {
        // Initialise protected class fields
        nrOfTimePoints = 12;
        
        /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue = 1;
        
        // Initialise timepoints
        trace.clear();

        std::vector<TimePoint> timePoints;

        // Add timepoints to the trace
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints.push_back(TimePoint(i));
        }

        // Add a numeric state variable "A" (without type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(aNumericStateVariableId, aMinValue);
            } else {
                timePoints[i].addNumericStateVariable(aNumericStateVariableId, aMinValue + i);
            }
        }
        
        // Add a numeric state variable "A" (with type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(aWithTypeNumericStateVariableId, aMinValue);
            } else {
                timePoints[i].addNumericStateVariable(aWithTypeNumericStateVariableId, aMinValue + i);
            }
        }

        // Initialise the aMaxValue field considering numeric state variable "A" (without type)
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            aMaxValue = std::max(aMaxValue, timePoints[i].getNumericStateVariableValue(aNumericStateVariableId));
        }
        
        // Add a numeric state variable "B" (without type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bNumericStateVariableId, bConstantValue);
        }
        
        // Add a numeric state variable "B" (with type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bWithTypeNumericStateVariableId, bConstantValue);
        }

        // Add a numeric state variable "C" to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(cNumericStateVariableId, cMaxValue);
            } else {
                timePoints[i].addNumericStateVariable(cNumericStateVariableId, nrOfTimePoints - i);
            }
        }

        // Initialise the cMinValue field
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            cMinValue = std::min(cMinValue, timePoints[i].getNumericStateVariableValue(cNumericStateVariableId));
        }
        
        // Add a numeric state variable "D" (with type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(dNumericStateVariableId, dConstantValue);
        }

        // Add spatial entities to each timepoint
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {

            // Add /*{{ spatial_entities[0].name }}*/s to the timepoint
            for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entities[0].name }}*/ = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();

                /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue = std::max(/*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue, static_cast<double>((j * 2.4) + /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue));
                
                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((j * 2.4) + /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue));
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>(/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 2);
            /*{% endfor %}*/
                /*{{ spatial_entities[0].name }}*/->setSemanticType(SemanticType::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entities[0].name }}*/, SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
            }
            
        /*{% for spatial_entity in spatial_entities[1:] %}*/
            // Add /*{{ spatial_entity.name }}*/s with default semantic type to the timepoint
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entity.name }}*/ = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();

                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((k * 0.3) + 0.7));
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>(/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 3);
            /*{% endfor %}*/
                /*{{ spatial_entity.name }}*/->setSemanticType(SemanticType::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entity.name }}*/, SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s);
            }
            
            // Add /*{{ spatial_entity.name }}*/s with semantic type "Organ.Heart" to the timepoint
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entity.name }}*/ = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();

                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((k * 0.3) + 0.7));
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>(/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 3);
            /*{% endfor %}*/
                /*{{ spatial_entity.name }}*/->setSemanticType(SEMANTIC_TYPE_ORGAN_HEART);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entity.name }}*/, SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s);
            }
        /*{% endfor %}*/
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > subtract(/*{{ spatial_measures[0].name }}*/, 0.00001)))) > 10]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({A}, 1)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasurePower) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= power(2, 0)]"));
}

TEST_F(CompleteTraceTest, BinaryNumericMeasureSubtract) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 1))) = subtract({A}, {A})]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (sum(multiply(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1375.76)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X[4] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 100) >= 10.5999]"));
}

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileMeasureQuartile) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X[4] quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 50) <= 5.7999]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileNumeric) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 79.4) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalQuantileSpatial) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max([0, 2] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 90)) >= 5.79]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, BinaryStatisticalSpatial) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max([0, 6] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeMeasureDifference) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 2.3999]"));
}

TEST_F(CompleteTraceTest, ChangeMeasureRatio) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [r(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 3.49]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeTemporalNumericCollection) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(d([0, 11] {C}(type = Organ.Heart))) = -9]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ChangeTemporalNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 2.49]"));
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
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1)))) = 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1) V (/*{{ spatial_measures[0].name }}*/ = 0.3)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1) => (/*{{ spatial_measures[0].name }}*/ = 0.1)))) > 0]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1)))) = 0]"));
}

TEST_F(CompleteTraceTest, CompoundConstraintMultiple) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1.00001) ^ (/*{{ spatial_measures[0].name }}*/ = 0.1) ^ (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) < 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1.00001) V (/*{{ spatial_measures[0].name }}*/ = 0.1) V (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) = 1]"));
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1.00001) => (/*{{ spatial_measures[0].name }}*/ = 0.1) => (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) > 0]"));
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1.00001) <=> (/*{{ spatial_measures[0].name }}*/ = 0.1) <=> (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, CompoundLogicProperty) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, 2))]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001) V (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0)]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001) => (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1)]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001) <=> (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= div({A}, div({A}, 1)))]"));
}

TEST_F(CompleteTraceTest, CompoundLogicPropertyMultiple) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 1) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) ^ {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 1) V (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) V {B} = 3]"));
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 1) => (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) => {B} = 3]"));
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 1) <=> (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintEnclosedByParentheses
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, ConstraintEnclosedByParentheses) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 1.0001)))) = 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesDoubled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ >= 1.0001))))) < 1]"));
}

TEST_F(CompleteTraceTest, ConstraintEnclosedByParenthesesQuadrupled) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ >= 1.0001))))))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, Constraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 10000 V /*{{ spatial_measures[0].name }}*/ <= 1))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterNumericMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < subtract(/*{{ spatial_measures[0].name }}*/, -0.1) ^ /*{{ spatial_measures[0].name }}*/ >= 1))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, FilterSubset) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 0))) = 1]"));
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
// HeterogeneousTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HeterogeneousTimeseriesComponentPeak) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(enteringValue(peak, [0, 11] {A})) = 4]"));
}

TEST_F(CompleteTraceTest, HeterogeneousTimeseriesComponentValley) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(enteringValue(valley, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 2]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousHomogeneousTimeseries
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousHomogeneousTimeseries) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(timeSpan(plateau, [0, 11] {B})) = 11]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousTimeseriesComponentAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(values(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeseriesComponentDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(values(descent, [0, 11] {C}(type = Organ.Heart))) = 7.5]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeseriesComponentPlateau) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(values(plateau, [0, 11] {B})) = 2.999]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeseriesComponentUniformAscent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(values(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 11]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeseriesComponentUniformDescent) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(values(uniformDescent, [0, 11] {C}(type = Organ.Heart))) = 6.6]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeseriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, HomogeneousTimeseriesMeasureTimeSpan) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(timeSpan(ascent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 2]"));
}

TEST_F(CompleteTraceTest, HomogeneousTimeseriesMeasureValue) {
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [X [3] (max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > add(add({A}, {B}), 1.3))]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NextLogicProperty) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [X (max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= multiply({B}, 1.096))]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NotConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ > 1)))) = 1]"));
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
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, NumericSpatialMeasure) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"));
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

TEST_F(CompleteTraceTest, NumericStateVariableTypeLeft) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableTypeRight) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A} <= {B}(type = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableBothTypes) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {B}(type = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableBothTypesAndDifferentTypeValues) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {C}(type = Organ.Heart)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableOneNumericStateVariable) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [{C}(type = Organ.Heart) = 12]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongRhsType) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Kidney) <= {C}(type = Organ.Kidney)]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{a2#0f-} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongLongName) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongTypeLhs) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{A}(type = Organ.Heart) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableWrongTypeLhsLargerValue) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [{B}(type = 213121) <= {B}]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableSemanticTypeNotInTypeSemanticsTable) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({D}(type = Organ.Liver) < 5.01) ^ ({D}(type = Organ.Liver) > 4.99))]"));
}

TEST_F(CompleteTraceTest, NumericStateVariableTypeInTypeSemanticsTable) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [G [0, 11] (({B}(type = Organ.Kidney) < 3.01) ^ ({B}(type = Organ.Kidney) > 2.99))]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 12]"));
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
// SemanticType
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SemanticType) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.4 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, type = Organ.Heart))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, SimilarityMeasureAntiSimilar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [opposite(d([0, 11] {A}), d([0, 11] {C} (type = Organ.Heart)), 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 1))) > {A}]"));
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST_F(CompleteTraceTest, SpatialMeasure/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= div(/*{{ spatial_measure.max_value }}*/, 1.078)))) = 1]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 27.4001]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(intersection(/*{{ spatial_entities[0].name }}*/s, filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 24.999)))) >= 2]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min([0, 11] min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TemporalNumericComparison) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"));
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
// TimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeseriesComponent) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [median(enteringValue(uniformAscent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 5]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeseriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeseriesMeasureEnteringTime) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [max(enteringTime(descent, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) < 10]"));
}

TEST_F(CompleteTraceTest, TimeseriesMeasureEnteringValue) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [min(enteringValue(uniformDescent, [0, 11] {C}(type = Organ.Heart))) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeseriesTimeseriesComponent
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, TimeseriesTimeseriesComponent) {
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= round(/*{{ spatial_measures[0].name }}*/)))) > 0]"));
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
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] (max(ceil(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 28)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < 1))) = 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureAvg) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureCount) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureGeomean) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureHarmean) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [harmean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureKurt) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [kurt(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMax) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMedian) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [median(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMin) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureMode) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 0]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureProduct) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [product(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSkew) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [skew(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1.0001]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureStdev) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [stdev(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= subtract(1, 0.9999)]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureSum) {
    EXPECT_FALSE(RunEvaluationTest("P >= 0.3 [sum(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 1.0001]"));
}

TEST_F(CompleteTraceTest, UnaryStatisticalMeasureVar) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [var(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 0.0001]"));
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
// UnaryTypeConstraint
//
//
/////////////////////////////////////////////////////////

TEST_F(CompleteTraceTest, UnaryTypeConstraint) {
    EXPECT_TRUE(RunEvaluationTest("P >= 0.3 [F [0, 11] count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, type < Organ.Kidney))) > 0]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [G [0, 10] (d(covar(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ < 1)), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d(covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0) U [0, 10] (X d(count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 V /*{{ spatial_measures[0].name }}*/ < 10000)))) < 0)]"));
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
    EXPECT_TRUE(RunEvaluationTest("P < 0.9 [(d({C}(type = Organ.Heart)) < 0) U [0, 10] (d({C}(type = Organ.Heart)) > 0)]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [((avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10)) ^ (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100)]"));
}

TEST_F(CompleteTraceTest, EnclosingWithParenthesesDifferently2) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 10) ^ ((count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 100))]"));
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
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationBinary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ > 5 ^ /*{{ spatial_measures[0].name }}*/ > 1000))) > add(add({A}, {A}), {B}))]"));
}

TEST_F(CompleteTraceTest, ConstraintsCombinationNary) {
    EXPECT_FALSE(RunEvaluationTest("P < 0.9 [G [0, 5] (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ > 5) ^ ((/*{{ spatial_measures[0].name }}*/ > 1000) V (/*{{ spatial_measures[0].name }}*/ > 100 V /*{{ spatial_measures[0].name }}*/ < 210))))) > add(add({A}, {A}), {B}))]"));
}


#endif
