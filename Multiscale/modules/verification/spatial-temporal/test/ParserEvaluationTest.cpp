#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

#include <string>
#include <vector>

using namespace multiscale::verification;


// Test function
bool evaluateParsingResult(const std::string &inputString) {
    ProbabilisticLogicPropertyAttribute parseResult;
    Parser parser(inputString);

    parser.parse(parseResult);

//    return parseResult.evaluate();
    return true;
}

// Tests
TEST(ParserEvaluationTest, AndOperator) {
	EXPECT_TRUE(evaluateParsingResult("T ^ T"));
	EXPECT_FALSE(evaluateParsingResult("T ^ F"));
	EXPECT_FALSE(evaluateParsingResult("F ^ T"));
	EXPECT_FALSE(evaluateParsingResult("F ^ F"));
}

TEST(ParserEvaluationTest, OrOperator) {
    EXPECT_TRUE(evaluateParsingResult("T V T"));
    EXPECT_TRUE(evaluateParsingResult("T V F"));
    EXPECT_TRUE(evaluateParsingResult("F V T"));
    EXPECT_FALSE(evaluateParsingResult("F V F"));
}

TEST(ParserEvaluationTest, ImplicationOperator) {
    EXPECT_TRUE(evaluateParsingResult("T => T"));
    EXPECT_FALSE(evaluateParsingResult("T => F"));
    EXPECT_TRUE(evaluateParsingResult("F => T"));
    EXPECT_TRUE(evaluateParsingResult("F => F"));
}

TEST(ParserEvaluationTest, EquivalenceOperator) {
    EXPECT_TRUE(evaluateParsingResult("T <=> T"));
    EXPECT_FALSE(evaluateParsingResult("T <=> F"));
    EXPECT_FALSE(evaluateParsingResult("F <=> T"));
    EXPECT_TRUE(evaluateParsingResult("F <=> F"));
}

TEST(ParserEvaluationTest, NotOperator) {
    EXPECT_TRUE(evaluateParsingResult("~F"));
    EXPECT_FALSE(evaluateParsingResult("~T"));
}

TEST(ParserEvaluationTest, CombinedOperators) {
    EXPECT_TRUE(evaluateParsingResult("~F ^ T"));
    EXPECT_TRUE(evaluateParsingResult("(~T) => (T ^ (F V F))"));
    EXPECT_FALSE(evaluateParsingResult("(~T ^ ~F) <=> (T ^ (F => T) ^ (F <=> F))"));
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
