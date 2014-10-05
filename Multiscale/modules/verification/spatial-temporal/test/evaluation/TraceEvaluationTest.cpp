#include "TraceEvaluationTest.hpp"

using namespace multiscaletest;


TraceEvaluationTest::TraceEvaluationTest() : nrOfTimePoints(12),
                                             aNumericStateVariableId("A", SemanticType::DEFAULT_VALUE),
                                             bNumericStateVariableId("B", SemanticType::DEFAULT_VALUE),
                                             aWithTypeNumericStateVariableId("A", SEMANTIC_TYPE_ORGAN_KIDNEY),
                                             bWithTypeNumericStateVariableId("B", SEMANTIC_TYPE_ORGAN_KIDNEY),
                                             cNumericStateVariableId("C", SEMANTIC_TYPE_ORGAN_HEART),
                                             aMinValue(1), aMaxValue(std::numeric_limits<double>::lowest()),
                                             bConstantValue(3), cMinValue(std::numeric_limits<double>::max()),
                                             cMaxValue(12), evaluationResult(false) {}

bool TraceEvaluationTest::RunEvaluationTest(const std::string &query) {
    InitialiseQuery(query);
    InitialiseTypeSemanticsTable();
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

    evaluationResult = parseResult.evaluate(trace, typeSemanticsTable);
}

void TraceEvaluationTest::ValidateTestResults() {}

void TraceEvaluationTest::InitialiseQuery(const std::string &query) {
    this->query = query;
}

void TraceEvaluationTest::InitialiseTypeSemanticsTable() {
    typeSemanticsTable.addTableEntry(SEMANTIC_TYPE_ORGAN_HEART, 2);
    typeSemanticsTable.addTableEntry(SEMANTIC_TYPE_ORGAN_KIDNEY, 1);
}


// Constants
const std::string multiscaletest::TraceEvaluationTest::SEMANTIC_TYPE_ORGAN_HEART    = "Organ.Heart";
const std::string multiscaletest::TraceEvaluationTest::SEMANTIC_TYPE_ORGAN_KIDNEY   = "Organ.Kidney";
