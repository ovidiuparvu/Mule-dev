#include "TraceEvaluationTest.hpp"

using namespace multiscaletest;


TraceEvaluationTest::TraceEvaluationTest() : nrOfTimePoints(12),
                                             aNumericStateVariableId("A", ScaleAndSubsystem::DEFAULT_VALUE),
                                             bNumericStateVariableId("B", ScaleAndSubsystem::DEFAULT_VALUE),
                                             aWithTypeNumericStateVariableId("A", SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY),
                                             bWithTypeNumericStateVariableId("B", SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY),
                                             cNumericStateVariableId("C", SCALE_AND_SUBSYSTEM_ORGAN_HEART),
                                             dNumericStateVariableId("D", SCALE_AND_SUBSYSTEM_ORGAN_LIVER),
                                             aMinValue(1),
                                             aMaxValue(std::numeric_limits<double>::lowest()),
                                             bConstantValue(3),
                                             cMinValue(std::numeric_limits<double>::max()),
                                             cMaxValue(12),
                                             dConstantValue(5),
                                             evaluationResult(false) {}

bool TraceEvaluationTest::RunEvaluationTest(const std::string &query) {
    InitialiseQuery(query);
    InitialiseMultiscaleArchitectureGraph();
    InitialiseTrace();

    RunTest();
    ValidateTestResults();

    return evaluationResult;
}

void TraceEvaluationTest::RunTest() {
    AbstractSyntaxTree parseResult;
    Parser parser(query);

    if (!parser.parse(parseResult)) {
        MS_throw(multiscale::TestException, ERR_MSG_TEST);
    }

    evaluationResult = parseResult.evaluate(trace, multiscaleArchitectureGraph);
}

void TraceEvaluationTest::ValidateTestResults() {}

void TraceEvaluationTest::InitialiseQuery(const std::string &query) {
    this->query = query;
}

void TraceEvaluationTest::InitialiseMultiscaleArchitectureGraph() {
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


// Constants
const std::string multiscaletest::TraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN   = "Organism.Human";
const std::string multiscaletest::TraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART      = "Organ.Heart";
const std::string multiscaletest::TraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY     = "Organ.Kidney";
const std::string multiscaletest::TraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_LIVER      = "Organ.Liver";
