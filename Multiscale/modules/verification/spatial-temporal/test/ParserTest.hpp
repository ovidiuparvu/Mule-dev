#ifndef PARSERTEST_HPP
#define PARSERTEST_HPP

// Include test function

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


/////////////////////////////////////////////////////////////////
//
// Tests
//
/////////////////////////////////////////////////////////////////


// Incorrect input

TEST(Input, IncorrectTrueInput) {
    EXPECT_THROW(parseInputString("true"), InvalidInputException);
}

TEST(Input, IncorrectTInput) {
    EXPECT_THROW(parseInputString("T"), InvalidInputException);
}

TEST(Input, IncorrectFalseInput) {
    EXPECT_THROW(parseInputString("false"), InvalidInputException);
}

TEST(Input, IncorrectFInput) {
    EXPECT_THROW(parseInputString("F"), InvalidInputException);
}


// Include additional test cases

#include "attribute/BinaryNumericMeasureTest.hpp"
#include "attribute/BinaryNumericNumericTest.hpp"
#include "attribute/BinarySubsetMeasureTest.hpp"
#include "attribute/BinarySubsetTest.hpp"
#include "attribute/ComparatorTest.hpp"
#include "attribute/CompoundConstraintTest.hpp"
#include "attribute/CompoundLogicPropertyTest.hpp"
#include "attribute/ConstraintParenthesesTest.hpp"
#include "attribute/ConstraintTest.hpp"
#include "attribute/DifferenceTest.hpp"
#include "attribute/FilterSubsetTest.hpp"
#include "attribute/FutureLogicPropertyTest.hpp"
#include "attribute/GlobalLogicPropertyTest.hpp"
#include "attribute/LogicPropertyParenthesesTest.hpp"
#include "attribute/LogicPropertyTest.hpp"
#include "attribute/MultipleLogicPropertiesTest.hpp"
#include "attribute/NextKLogicPropertyTest.hpp"
#include "attribute/NextLogicPropertyTest.hpp"
#include "attribute/NotConstraintTest.hpp"
#include "attribute/NotLogicPropertyTest.hpp"
#include "attribute/NumericMeasureTest.hpp"
#include "attribute/NumericNumericComparisonTest.hpp"
#include "attribute/NumericSpatialMeasureTest.hpp"
#include "attribute/NumericSpatialNumericComparisonTest.hpp"
#include "attribute/NumericStateVariableTest.hpp"
#include "attribute/ProbabilisticLogicPropertyTest.hpp"
#include "attribute/QuaternarySubsetMeasureTest.hpp"
#include "attribute/QuaternarySubsetTest.hpp"
#include "attribute/SpatialMeasureTest.hpp"
#include "attribute/SubsetSpecificTest.hpp"
#include "attribute/SubsetTest.hpp"
#include "attribute/TernarySubsetMeasureTest.hpp"
#include "attribute/TernarySubsetTest.hpp"
#include "attribute/UnaryConstraintTest.hpp"
#include "attribute/UnaryNumericMeasureTest.hpp"
#include "attribute/UnaryNumericNumericTest.hpp"
#include "attribute/UnarySubsetMeasureTest.hpp"
#include "attribute/UnarySubsetTest.hpp"
#include "attribute/UntilLogicPropertyTest.hpp"

#endif
