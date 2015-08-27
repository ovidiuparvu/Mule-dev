#include "NonEmptyTraceEvaluationTest.hpp"

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

using namespace multiscaletest;


NonEmptyTraceEvaluationTest::NonEmptyTraceEvaluationTest() : TraceEvaluationTest(), nrOfTimePoints(/*{{ nr_of_time_points }}*/) {}

void NonEmptyTraceEvaluationTest::InitializeMultiscaleArchitectureGraph() {
    multiscaleArchitectureGraph.reset();

    // The Organ.Liver scale and subsystem was intentionally left out in
    // order to test if a warning is issued when a "Organ.Liver" state
    // variable is evaluated
    multiscaleArchitectureGraph.addRootVertex(SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN);
    multiscaleArchitectureGraph.addVertexAndCorrespondingEdge(
        SCALE_AND_SUBSYSTEM_ORGAN_HEART,
        SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN
    );
    multiscaleArchitectureGraph.addVertexAndCorrespondingEdge(
        SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY,
        SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN
    );
}

void NonEmptyTraceEvaluationTest::InitializeTrace() {
    trace.clear();

    InitializeTimePoints();
    AddValuesToTimePoints();
    AddTimePointsToTrace();
}

void NonEmptyTraceEvaluationTest::InitializeTimePoints() {
    timePoints.clear();

    // Create collection of time points
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        timePoints.push_back(TimePoint(i));
    }
}

void NonEmptyTraceEvaluationTest::AddTimePointsToTrace() {
    // Add all time points to the trace
    for (TimePoint &timePoint : timePoints) {
        trace.addTimePoint(timePoint);
    }
}


// Constants
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN   = "Organism.Human";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART      = "Organ.Heart";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY     = "Organ.Kidney";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_LIVER      = "Organ.Liver";
