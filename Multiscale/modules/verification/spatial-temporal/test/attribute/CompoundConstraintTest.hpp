#ifndef COMPOUNDCONSTRAINTTEST_HPP
#define COMPOUNDCONSTRAINTTEST_HPP

#include "parsing/InputStringParser.hpp"

#include <string>
#include <vector>

using namespace multiscale;
using namespace multiscaletest::verification;

// Binary operators

const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});


// CompoundConstraint

TEST(CompoundConstraint, MissingBinaryOperator) {
	EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) (area >= 8))) <= 3]"), InvalidInputException);
}

TEST(CompoundConstraint, MissingConstraints) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, " + binaryOperator + " =>)) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, MissingFirstConstraint) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, " + binaryOperator + " (area = 34))) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, MissingSecondConstraint) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (area = 34) " + binaryOperator + ")) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryBefore) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, " + binaryOperator + " (perimeter <= 30.2))) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryAfter) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + ")) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, NumericNumericComparisonBeforeBinaryOperator) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ({A} >= 3 " + binaryOperator + " (circleMeasure = 0.1))) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, UnaryNumericMeasureAfterBinaryOperator) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ((circleMeasure = 0.1) " + binaryOperator + " count(regions) >= 3)) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, AdditionalOperatorBeforeBinaryOperator) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ((circleMeasure = 0.1) ~ " + binaryOperator + " count(regions) >= 3)) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, AdditionalOperatorAfterBinaryOperator) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(clusters, ((circleMeasure = 0.1) " + binaryOperator + " " + binaryOperator + " count(regions) >= 3)) <= 3]"), InvalidInputException);
	}
}

TEST(CompoundConstraint, Correct) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1))) <= 3]"));
	}
}

TEST(CompoundConstraint, MultipleCorrect) {
	for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
		EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(clusters, (perimeter <= 30.2) " + binaryOperator + " (circleMeasure = 0.1) " + binaryOperator + " (~ distanceFromOrigin >= 4000))) <= 3]"));
	}
}

#endif
