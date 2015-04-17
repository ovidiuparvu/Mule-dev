#include "NonEmptyTraceEvaluationTest.hpp"

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

using namespace multiscaletest;


NonEmptyTraceEvaluationTest::NonEmptyTraceEvaluationTest() : TraceEvaluationTest(), nrOfTimePoints(/*{{ nr_of_timepoints }}*/) {}

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

    InitializeTimepoints();
    AddValuesToTimepoints();
    AddTimepointsToTrace();
}

void NonEmptyTraceEvaluationTest::InitializeTimepoints() {
    timePoints.clear();

    // Create collection of timepoints
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        timePoints.push_back(TimePoint(i));
    }
}

void NonEmptyTraceEvaluationTest::AddTimepointsToTrace() {
    // Add all timepoints to the trace
    for (TimePoint &timePoint : timePoints) {
        trace.addTimePoint(timePoint);
    }
}


// Constants
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN   = "Organism.Human";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART      = "Organ.Heart";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY     = "Organ.Kidney";
const std::string multiscaletest::NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_LIVER      = "Organ.Liver";
