#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>
#include <vector>

using namespace multiscale::verification;


// Test function
bool evaluateParsingResult(const std::string &inputString, const SpatialTemporalTrace &trace) {
    AbstractSyntaxTree parseResult;
    Parser parser(inputString);

    parser.parse(parseResult);

    return parseResult.evaluate(trace);
}

// Tests
TEST(ParserEvaluationTest, Correct) {
    EXPECT_FALSE(evaluateParsingResult("P > 0.9 [count(regions) > 2]", SpatialTemporalTrace()));
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
