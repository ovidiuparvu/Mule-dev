#include "TraceEvaluationTest.hpp"

using namespace multiscaletest;


TraceEvaluationTest::TraceEvaluationTest() : evaluationResult(false) {}

bool TraceEvaluationTest::RunEvaluationTest(const std::string &query) {
    InitializeQuery(query);
    InitializeMultiscaleArchitectureGraph();
    InitializeTrace();

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

void TraceEvaluationTest::InitializeQuery(const std::string &query) {
    this->query = query;
}
