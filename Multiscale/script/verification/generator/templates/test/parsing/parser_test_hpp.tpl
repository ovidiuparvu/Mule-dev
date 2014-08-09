#ifndef PARSERTEST_HPP
#define PARSERTEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

// Include test function

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


/////////////////////////////////////////////////////////
//
//
// BinaryNumericFilterTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericFilter, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(3))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(3))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add())) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add1(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(1 + /*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(volume23D, /*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/ /*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, entropy))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/ / 2))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/) * 1)) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/))) > 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////


TEST(BinaryNumericMeasure, IncorrectBinaryNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= coord(2, 3) a]"), InvalidInputException);
}

TEST(BinaryNumericMeasure, CorrectAdd) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= add(2, 3)]"));
}

TEST(BinaryNumericMeasure, CorrectDiv) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= div(2, 3)]"));
}

TEST(BinaryNumericMeasure, CorrectLog) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= log(4.33333, 9.12312312)]"));
}

TEST(BinaryNumericMeasure, CorrectMod) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= mod(4, 8)]"));
}

TEST(BinaryNumericMeasure, CorrectMultiply) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= multiply(2, 3)]"));
}

TEST(BinaryNumericMeasure, CorrectPower) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= power(2, 3)]"));
}

TEST(BinaryNumericMeasure, CorrectSubtract) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= subtract(3, 6)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericNumericTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericNumeric, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add()]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add a(2, 3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add( a 2, 3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(a, 3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2 3)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, a)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, 3 a)]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, 3) a]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(BinarySubsetMeasure, IncorrectBinarySubsetMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [arithmeticmean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) ^ geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubsetMeasure, CorrectAvg) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [avg(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectGeomean) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectHarmean) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [harmean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectKurt) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMax) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMedian) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [median(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMin) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectMode) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [mode(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectProduct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [product(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectSkew) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [skew(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectStdev) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [stdev(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectSum) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [sum(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}

TEST(BinarySubsetMeasure, CorrectVar) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [var(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// BinarySubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(BinarySubset, IncorrectMissingFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectMissingSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectMissingParameters) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean() <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean T (/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean ( /*{{ spatial_entities[0].name }}*/s V /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, MissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, InvalidSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, height) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ true) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) ^ geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"), InvalidInputException);
}

TEST(BinarySubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// ComparatorTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(Comparator, IncorrectEqual) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) == 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent1) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) <> 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent2) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) != 3]"), InvalidInputException);
}

TEST(Comparator, CorrectGreaterThan) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) > 3]"));
}

TEST(Comparator, CorrectLessThan) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) < 3]"));
}

TEST(Comparator, CorrectGreaterThanOrEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) >= 3]"));
}

TEST(Comparator, CorrectLessThanOrEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}

TEST(Comparator, CorrectEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_entities[0].name }}*/s) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraintTest.hpp
//
//
/////////////////////////////////////////////////////////

// Binary operators

const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});


// CompoundConstraint

TEST(CompoundConstraint, MissingBinaryOperator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ >= 8))) <= 3]"), InvalidInputException);
}

TEST(CompoundConstraint, MissingConstraints) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " =>)) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, MissingFirstConstraint) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 34))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, MissingSecondConstraint) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ = 34) " + binaryOperator + ")) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryBefore) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryAfter) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + ")) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, NumericNumericComparisonBeforeBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ({A} >= 3 " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, UnaryNumericMeasureAfterBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " count(/*{{ spatial_entities[0].name }}*/s) >= 3)) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, AdditionalOperatorBeforeBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) ~ " + binaryOperator + " count(/*{{ spatial_entities[0].name }}*/s) >= 3)) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, AdditionalOperatorAfterBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " " + binaryOperator + " count(/*{{ spatial_entities[0].name }}*/s) >= 3)) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, Correct) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1))) <= 3]"));
    }
}

TEST(CompoundConstraint, MultipleCorrect) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " (~ /*{{ spatial_measures[0].name }}*/ >= 4000))) <= 3]"));
    }
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

// Binary operators

const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});


// CompoundLogicProperty

TEST(CompoundLogicProperty, MissingBinaryOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"), InvalidInputException);
}

TEST(CompoundLogicProperty, MissingConstraints) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, MissingFirstConstraint) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, MissingSecondConstraint) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, BinaryOperatorAsUnaryBefore) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + " ({A} >= 4) (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, BinaryOperatorAsUnaryAfter) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) (count(/*{{ spatial_entities[0].name }}*/s) >= 4) " + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, UnarySubsetMeasureBeforeBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [(/*{{ spatial_measures[0].name }}*/) " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, UnaryNumericMeasureAfterBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s)) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, AdditionalOperatorBeforeBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, AdditionalOperatorAfterBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, Correct) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) ]"));
    }
}

TEST(CompoundLogicProperty, MultipleCorrect) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) >= 4) " + binaryOperator + " (count(/*{{ spatial_entities[0].name }}*/s) <= 4) " + binaryOperator + " {B} = 3]"));
    }
}


/////////////////////////////////////////////////////////
//
//
// ConstraintParenthesesTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(ConstraintEnclosedByParentheses, MissingParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, MissingParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, InvertedParentheses) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, )/*{{ spatial_measures[0].name }}*/ <= 30.2()) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesesBothSides) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (((/*{{ spatial_measures[0].name }}*/ <= 30.2))))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ParenthesesInWrongOrder) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (((())(/*{{ spatial_measures[0].name }}*/ <= 30.2))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectDoubled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectQuadrupled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ <= 30.2)))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ConstraintTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(Constraint, ExtraInputBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(Constraint, ExtraInputAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2, true)) <= 3]"), InvalidInputException);
}

TEST(Constraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// DifferenceTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(Difference, IncorrectInputMissingDifferenceNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d() >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectInputMissingDifferenceNumericMeasureAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectDifferenceSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [df(4) >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectOpeningBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d[4) >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectClosingBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(4] >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d[4] >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBracketsInverted) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d)4( >= 4]"), InvalidInputException);
}

TEST(Difference, IncorrectBracketsDoubled) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d((4)) >= 4]"), InvalidInputException);
}

TEST(Difference, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [d(4) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(FilterSubset, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, d(count(/*{{ spatial_entities[0].name }}*/s)) >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, CorrectSpatialMeasureRealValue) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"));
}

TEST(FilterSubset, CorrectSpatialMeasures) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].name }}*/)) <= 3]"));
}

TEST(FilterSubset, CorrectMultiple) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3 ^ /*{{ spatial_measures[0].name }}*/ < 2)) <= 3]"));
}

TEST(FilterSubset, CorrectMultipleComplex) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= sqrt(add(power(subtract(10, /*{{ spatial_measures[0].name }}*/), 2), power(subtract(10, /*{{ spatial_measures[0].name }}*/), 2))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(FilterSubset, IncorrectInputMisspelledFilter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(fillter[(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter[(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputMissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3, /*{{ spatial_measures[0].name }}*/ <= 2)) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) = 2 V <= 3]"), InvalidInputException);
}

TEST(FilterSubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(FutureLogicProperty, WrongInputMissingStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingTimepointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F ({A} >= 4) [2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [ ({A} >= 4) 2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, MissingTimepointComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2.3, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2.0, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2, 3 ({A} >= 4)] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2, 3] ({A} >= 4) ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [F [2, 3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// GlobalLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(GlobalLogicProperty, WrongInputMissingStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimepointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4) [2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [ ({A} >= 4) 2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, MissingTimepointComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2.3, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2.0, 3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3 ({A} >= 4)] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3] ({A} >= 4) ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [G [2, 3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyParenthesesTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(LogicPropertyEnclosedByParentheses, MissingParenthesisRight) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, MissingParenthesisLeft) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} >= 4)]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesisLeft) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(({A} >= 4)]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesisRight) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, InvertedParentheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [){A} >= 4(]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ExtraParenthesesBothSides) {
    EXPECT_THROW(parseInputString("P >= 0.3 [((((({A} >= 4)))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, ParenthesesInWrongOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [((())(({A} >= 4)))]"), InvalidInputException);
}

TEST(LogicPropertyEnclosedByParentheses, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4)]"));
}

TEST(LogicPropertyEnclosedByParentheses, CorrectDoubled) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [(({A} >= 4))]"));
}

TEST(LogicPropertyEnclosedByParentheses, CorrectQuadrupled) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [(((({A} >= 4))))]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(LogicProperty, ExtraInputBeforeLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [aaa count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputInsideLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) aaa >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputAfterLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2 aaa]"), InvalidInputException);
}

TEST(LogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicPropertiesTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(MultipleLogicProperties, Correct1) {
    EXPECT_TRUE(parseInputString("P >= 0.1234 [( d(4) >=  count(/*{{ spatial_entities[0].name }}*/s) ) ^ ( covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST(MultipleLogicProperties, Correct2) {
    EXPECT_TRUE(parseInputString("P <= 0.85934 [~( F [2, 3] ( max(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 10), /*{{ spatial_measures[0].name }}*/) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 0.4) = 0.7 ))) ) <=> ( (subsetClusteredness(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 2) ^ (/*{{ spatial_measures[0].name }}*/ >= 6) V (/*{{ spatial_measures[0].name }}*/ >= 30) => (/*{{ spatial_measures[0].name }}*/ <= 2) <=> (/*{{ spatial_measures[0].name }}*/ >= 4)) ) >= 2) U [10, 400] ( kurt(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 0.00001 ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NextKLogicProperty, IncorrectInputMissingTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, IncorrectInputAfterNextSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X 2 [B] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, IncorrectValueForNextTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [B] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, RealValueForNextTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [3.0] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, IncorrectInputBeforeLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [3] 2 ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [X [3] ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NextLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NextLogicProperty, IncorrectInputAfterNextSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X {B} ({A} >= 4)]"), InvalidInputException);
}

TEST(NextLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [X ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraintTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NotConstraint, IncorrectOperator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, !(/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) ~)) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ = 2.4) ~)) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorBeforeConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ = 2.4))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NotLogicProperty, OperatorAfterLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorAfterLogicPropertyAndExtraLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~ ({B} 4 >=)]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorBeforeLogicPropertyAndExtraLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [~ ({A} >= 4) ({B} >= 4)]"), InvalidInputException);
}

TEST(NotLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [~({A} >= 4.2)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NumericMeasure, WrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [geomean]"), InvalidInputException);
}

TEST(NumericMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericNumericComparisonTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NumericNumericComparison, NumericMeasureFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 >= {A}"), InvalidInputException);
}

TEST(NumericNumericComparison, NumericMeasureFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 {A} >=]"), InvalidInputException);
}

TEST(NumericNumericComparison, ComparatorFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4 {A}]"), InvalidInputException);
}

TEST(NumericNumericComparison, ComparatorFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= {A} 4]"), InvalidInputException);
}

TEST(NumericNumericComparison, IncorrectOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} 4 >=]"), InvalidInputException);
}

TEST(NumericNumericComparison, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NumericSpatialMeasure, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [/*{{ spatial_entities[0].name }}*/s <= add a(2, 3)]"), InvalidInputException);
}

TEST(NumericSpatialMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialNumericComparisonTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NumericSpatialNumericComparison, NumericMeasureFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 >= d(4)]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, NumericMeasureFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 d(4) >=]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, ComparatorFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4 d(4)]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, ComparatorFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= d(4) 4]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, IncorrectOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(4) 4 >=]"), InvalidInputException);
}

TEST(NumericSpatialNumericComparison, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariableTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(NumericStateVariable, MissingLeftCurlyBrace) {
    EXPECT_THROW(parseInputString("P >= 0.3 [A} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingRightCurlyBrace) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, ExtraLeftCurlyBrace) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{{A} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, ExtraRightCurlyBrace) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, InvertedCurlyBraces) {
    EXPECT_THROW(parseInputString("P >= 0.3 [}A{ <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, DoubleCurlyBraces) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{{A}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, TripleCurlyBraces) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{{{A}}} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, Correct1) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= 3]"));
}

TEST(NumericStateVariable, Correct2) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{a2#0f-} <= 3]"));
}

TEST(NumericStateVariable, Correct3) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(ProbabilisticLogicProperty, IncorrectProbabilitySymbol) {
    EXPECT_THROW(parseInputString("PT >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectComparator) {
    EXPECT_THROW(parseInputString("P != 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectEqualComparator) {
    EXPECT_THROW(parseInputString("P = 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLow) {
    EXPECT_THROW(parseInputString("P >= -0.1 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLowMinor) {
    EXPECT_THROW(parseInputString("P >= -0.000000001 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHigh) {
    EXPECT_THROW(parseInputString("P >= 2.9 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHighMinor) {
    EXPECT_THROW(parseInputString("P >= 1.000000001 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [T]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftMissing) {
    EXPECT_THROW(parseInputString("P >= 0.3 count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightMissing) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[count(/*{{ spatial_entities[0].name }}*/s) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftRightExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[count(/*{{ spatial_entities[0].name }}*/s) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesInverted) {
    EXPECT_THROW(parseInputString("P >= 0.3 ]count(/*{{ spatial_entities[0].name }}*/s) >= 2["), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesClosing) {
    EXPECT_THROW(parseInputString("P >= 0.3 []count(/*{{ spatial_entities[0].name }}*/s) >= 2[]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[[count(/*{{ spatial_entities[0].name }}*/s) >= 2]][]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMin) {
    EXPECT_TRUE(parseInputString("P >= 0.0 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMax) {
    EXPECT_TRUE(parseInputString("P >= 1.0 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityLow) {
    EXPECT_TRUE(parseInputString("P >= 0.00000001 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityHigh) {
    EXPECT_TRUE(parseInputString("P >= 0.99999999 [count(/*{{ spatial_entities[0].name }}*/s) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(QuaternarySubsetMeasure, IncorrectQuaternarySubsetMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [correlation(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, CorrectCovar) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// QuaternarySubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(QuaternarySubset, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersThreeFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoThreeFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoThreeFour) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar() >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar V covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(_/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001"), InvalidInputException);
}

TEST(QuaternarySubset, MissingFirstComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, MissingSecondComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, MissingThirdComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ ^ /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/) <>= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [covar(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////


TEST(SpatialMeasure, IncorrectSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, height <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(SpatialMeasure, Correct/*{{ spatial_measures[0].name|first_to_upper }}*/) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}

/*{% for spatial_measure in spatial_measures[1:] %}*/
TEST(SpatialMeasure, Correct/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= 30.2)) <= 3]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetOperationTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(SubsetOperation, IncorrectInputWrongSubsetOperationAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(multiplication(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetOperation, CorrectDifference) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

TEST(SubsetOperation, CorrectIntersection) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

TEST(SubsetOperation, CorrectUnion) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecificTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(SubsetSpecific, IncorrectInputWrongSubsetAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(groups) <= 3]"), InvalidInputException);
}

TEST(SubsetSpecific, Correct/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST(SubsetSpecific, Correct/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entity.name }}*/s) <= 3]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperationTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(SubsetSubsetOperation, IncorrectInputWrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(division(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union2(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s V /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingFirstArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(, /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSeparatorComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingCommaAndArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSecondArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s, )) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s => /*{{ spatial_entities[0].name }}*/s)) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s) [0, 10]) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(Subset, IncorrectInputWrongSubsetAlternativeRegion) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(region) <= 3]"), InvalidInputException);
}

TEST(Subset, IncorrectInputWrongSubsetAlternativeCluster) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(cluster) <= 3]"), InvalidInputException);
}

TEST(Subset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(TernarySubsetMeasure, IncorrectTernarySubsetMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [midtile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubsetMeasure, CorrectPercentile) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"));
}

TEST(TernarySubsetMeasure, CorrectQuartile) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// TernarySubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(TernarySubset, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParameterThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersOneThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingParametersTwoThree) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputMissingAllParameters) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile() <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile ^ quartile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile ( _ /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, MissingFirstComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, InvalidSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, height, 4.3) <= 2]"), InvalidInputException);
}

TEST(TernarySubset, MissingSecondComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ 4.3) <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5, 1.2]"), InvalidInputException);
}

TEST(TernarySubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ 4.3) V true <= 0.5]"), InvalidInputException);
}

TEST(TernarySubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilterTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericFilter, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs())) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs ^ sqrt(/*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(1, /*{{ spatial_measures[0].name }}*/))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/, 3))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/) * 2)) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/))) > 1]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericMeasure, IncorrectUnaryNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= frac(count(/*{{ spatial_entities[0].name }}*/s))]"), InvalidInputException);
}

TEST(UnaryNumericMeasure, CorrectAbs) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= abs(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectCeil) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= ceil(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectFloor) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= floor(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectRound) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= round(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectSign) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= sign(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectSqrt) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= sqrt(count(/*{{ spatial_entities[0].name }}*/s))]"));
}

TEST(UnaryNumericMeasure, CorrectTrunc) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= trunc(count(/*{{ spatial_entities[0].name }}*/s))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumericTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericNumeric, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs()]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs 2(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(2 3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3 2)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3) 2]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraintTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnarySpatialConstraint, IncorrectSpatialMeasureBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ ^ /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, <= 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ 30.2)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= )) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingComparatorNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasureNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, >=)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasureComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, 4.4)) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputEmptyConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, ())) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetMeasureTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnarySubsetMeasure, IncorrectUnarySubsetMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [number(/*{{ spatial_entities[0].name }}*/s) <= 2]"), InvalidInputException);
}

TEST(UnarySubsetMeasure, CorrectCount) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}

TEST(UnarySubsetMeasure, CorrectSubsetClusteredness) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetClusteredness(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}

TEST(UnarySubsetMeasure, CorrectSubsetDensity) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [subsetDensity(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySubsetTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnarySubset, IncorrectInputNoSubset) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count() <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count [ (/*{{ spatial_entities[0].name }}*/s) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count( [ /*{{ spatial_entities[0].name }}*/s) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s } ) <= 2]"), InvalidInputException);
}

TEST(UnarySubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s ) } <= 2]"), InvalidInputException);
}

TEST(UnarySubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_entities[0].name }}*/s) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryTypeConstraintTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UnaryTypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, typee = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputWrongTypeKeywordExtraLetterBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, ttype = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputBeforeTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, 0 ^ type = 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterTypeKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, type += 0)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, type = type)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, IncorrectInputAfterFilterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, type >= 23 - 0.3)) <= 3]"), InvalidInputException);
}

TEST(UnaryTypeConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(filter(/*{{ spatial_entities[0].name }}*/s, type = 0)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicPropertyTest.hpp
//
//
/////////////////////////////////////////////////////////

TEST(UntilLogicProperty, IncorrectInputMissingStartTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingEndTimepoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingTimepoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingTimepointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(count(/*{{ spatial_entities[0].name }}*/s) >= 4) U [2, 3]]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputBeforeUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorBeforeUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputAfterUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] ({A} >= 4) (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorAfterUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] V (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeStartParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U ({A} >= 4) [A, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterStartParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, MissingTimepointsComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, A] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3.0] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, B] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3.0] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeEndParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3 ({A} >= 4) ] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterEndParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3] ({A} >= 4) (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4)]"));
}

TEST(UntilLogicProperty, MultipleCorrect) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) >= 4) U [2, 3] (count(/*{{ spatial_entities[0].name }}*/s) <= 4) <=> {B} = 3]"));
}


/////////////////////////////////////////////////////////////////
//
//
// Incorrect input
//
//
/////////////////////////////////////////////////////////////////

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


#endif
