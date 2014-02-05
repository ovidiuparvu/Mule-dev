#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

using namespace multiscaletest;
using namespace multiscale::verification;

// Tests
TEST(Parser, UnparseableInput) {
	ConstraintAttribute parseResult;
	Parser parser(")_VVV_");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, UnexpectedToken) {
	ConstraintAttribute parseResult;
	Parser parser("A V V");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, ExtraInput) {
	ConstraintAttribute parseResult;
	Parser parser("A V B(");

    EXPECT_THROW(parser.parse(parseResult), multiscale::InvalidInputException);
}

TEST(Parser, ParseableInput) {
	ConstraintAttribute parseResult;
	Parser parser("A V ~B");
	Parser parser2("(A V ~B)");

    EXPECT_TRUE(parser.parse(parseResult));
    EXPECT_TRUE(parser2.parse(parseResult));
}

// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
