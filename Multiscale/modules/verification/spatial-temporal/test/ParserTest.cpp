#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

using namespace multiscaletest;
using namespace multiscale::verification;

// Tests
TEST(Parser, UnparseableInput) {
	SubsetAttribute parseResult;
	Parser parser("_XOXO_");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, UnexpectedToken) {
	SubsetAttribute parseResult;
	Parser parser("filter(regions, ~A(()");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, ExtraInput) {
	SubsetAttribute parseResult;
	Parser parser("regionsTT");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, ParseableInput) {
	SubsetAttribute parseResult;
	Parser parser("filter(regions, A V ~B)");

    EXPECT_TRUE(parser.parse(parseResult));
}

// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
