#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

#include <string>
#include <vector>

using namespace multiscaletest;
using namespace multiscale;
using namespace multiscale::verification;

/////////////////////////////////////////////////////////////////
//
// Test function
//
/////////////////////////////////////////////////////////////////

bool parseInputString(const std::string &inputString) {
    ProbabilisticLogicPropertyAttribute parseResult;
    Parser parser(inputString);

    return parser.parse(parseResult);
}

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


// ProbabilisticLogicProperty

TEST(ProbabilisticLogicProperty, IncorrectProbabilitySymbol) {
	EXPECT_THROW(parseInputString("PT >= 0.3 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectComparator) {
	EXPECT_THROW(parseInputString("P > 0.3 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLow) {
	EXPECT_THROW(parseInputString("P >= -0.1 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLowMinor) {
	EXPECT_THROW(parseInputString("P >= -0.000000001 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHigh) {
	EXPECT_THROW(parseInputString("P >= 2.9 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHighMinor) {
	EXPECT_THROW(parseInputString("P >= 1.000000001 [count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [T]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftMissing) {
	EXPECT_THROW(parseInputString("P >= 0.3 count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightMissing) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[count(regions) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftRightExtra) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[count(regions) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesInverted) {
	EXPECT_THROW(parseInputString("P >= 0.3 ]count(regions) >= 2["), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesClosing) {
	EXPECT_THROW(parseInputString("P >= 0.3 []count(regions) >= 2[]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParantheses) {
	EXPECT_THROW(parseInputString("P >= 0.3 [[[count(regions) >= 2]][]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMin) {
	EXPECT_TRUE(parseInputString("P >= 0.0 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMax) {
	EXPECT_TRUE(parseInputString("P >= 1.0 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityLow) {
	EXPECT_TRUE(parseInputString("P >= 0.00000001 [count(regions) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityHigh) {
	EXPECT_TRUE(parseInputString("P >= 0.99999999 [count(regions) >= 2]"));
}



// LogicProperty

TEST(LogicProperty, ExtraInputBeforeLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [aaa count(regions) >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputInsideLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) aaa >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputAfterLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [count(regions) >= 2 aaa]"), InvalidInputException);
}

TEST(LogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [count(regions) >= 2]"));
}


// Difference

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


// NumericSpatialNumericComparison

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
	EXPECT_TRUE(parseInputString("P >= 0.3 [clusteredness(clusters) >= 4.2]"));
}


// NumericNumericComparison

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


// NotLogicProperty

TEST(NotLogicProperty, OperatorAfterLogicProperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorAfterLogicPropertyAndExtraLogicPorperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} 4 >=) ~ ({B} 4 >=)]"), InvalidInputException);
}

TEST(NotLogicProperty, OperatorBeforeLogicPropertyAndExtraLogicPorperty) {
	EXPECT_THROW(parseInputString("P >= 0.3 [~ ({A} 4 >=) ({B} 4 >=)]"), InvalidInputException);
}

TEST(NotLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [~({A} >= 4.2)]"));
}


// FutureLogicProperty

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
	EXPECT_THROW(parseInputString("P >= 0.3 [F [2, 3.8] ({A} >= 4)]"), InvalidInputException);
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


// GlobalLogicProperty

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
	EXPECT_THROW(parseInputString("P >= 0.3 [G [2, 3.8] ({A} >= 4)]"), InvalidInputException);
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


// NextLogicProperty

TEST(NextLogicProperty, IncorrectInputAfterNextSymbol) {
	EXPECT_THROW(parseInputString("P >= 0.3 [X {B} ({A} >= 4)]"), InvalidInputException);
}

TEST(NextLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [X ({A} >= 4)]"));
}


// NextKLogicProperty

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


// LogicProperty enclosed by parentheses

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


// AndLogicProperty

TEST(AndLogicProperty, AndOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AndOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) ^]"), InvalidInputException);
}

TEST(AndLogicProperty, IncorrectInputBeforeAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) ^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AdditionalOperatorBeforeAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ ^ (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, IncorrectInputAfterAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ^ ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, AdditionalOperatorAfterAndOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ^ => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(AndLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) ^ (count(regions) >= 4)]"));
}

TEST(AndLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) ^ (count(regions) >= 4) ^ (count(clusters) <= 4) ^ {B} = 3]"));
}


// OrLogicProperty

TEST(OrLogicProperty, OrOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, OrOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) V]"), InvalidInputException);
}

TEST(OrLogicProperty, IncorrectInputBeforeOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, AdditionalOperatorBeforeOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, IncorrectInputAfterOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) V ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, AdditionalOperatorAfterOrOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) V => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(OrLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) V (count(regions) >= 4)]"));
}

TEST(OrLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) V (count(regions) >= 4) V (count(clusters) <= 4) V {B} = 3]"));
}


// ImplicationLogicProperty

TEST(ImplicationLogicProperty, ImplicationOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, ImplicationOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) =>]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, IncorrectInputBeforeImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, AdditionalOperatorBeforeImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ => (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, IncorrectInputAfterImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) => ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, AdditionalOperatorAfterImplicationOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) => V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(ImplicationLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) => (count(regions) >= 4)]"));
}

TEST(ImplicationLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) => (count(regions) >= 4) => (count(clusters) <= 4) => {B} = 3]"));
}


// EquivalenceLogicProperty

TEST(EquivalenceLogicProperty, EquivalenceOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [<=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, EquivalenceOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) <=>]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, IncorrectInputBeforeEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) <=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, AdditionalOperatorBeforeEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ <=> (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, IncorrectInputAfterEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) <=> ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, AdditionalOperatorAfterEquivalenceOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) <=> V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(EquivalenceLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) <=> (count(regions) >= 4)]"));
}

TEST(EquivalenceLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) <=> (count(regions) >= 4) <=> (count(clusters) <= 4) <=> {B} = 3]"));
}


// UntilLogicProperty

TEST(UntilLogicProperty, UntilOperatorAsUnaryBefore) {
	EXPECT_THROW(parseInputString("P >= 0.3 [U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryAfter) {
	EXPECT_THROW(parseInputString("P >= 0.3 [(count(regions) >= 4) U [2, 3]]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputBeforeUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorBeforeUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ U [2, 3] (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputAfterUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorAfterUntilOperator) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeStartParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U ({A} >= 4) [A, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterStartParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, MissingTimepointsComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimepointRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, A] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimepointRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3.0] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsInvalid) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, B] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimepointsRealNumber) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1.0, 3.0] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeEndParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3 ({A} >= 4) ] V (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterEndParenthesis) {
	EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3] ({A} >= 4) (count(regions) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4)]"));
}

TEST(UntilLogicProperty, MultipleCorrect) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(regions) >= 4) U [2, 3] (count(clusters) <= 4) <=> {B} = 3]"));
}


// Numeric measure

TEST(NumericMeasure, WrongAlternative) {
	EXPECT_THROW(parseInputString("P >= 0.3 [geomean]"), InvalidInputException);
}

TEST(NumericMeasure, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [(count(clusters) >= 4)]"));
}


// NumericStateVariable

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

TEST(NumericStateVariable, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= 3]"));
}


// UnaryNumericNumeric

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


// BinaryNumericNumeric

//TEST(BinaryNumericNumeric, IncorrectInputBeforeStartBracket) {
//	EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs 2(3)]"), InvalidInputException);
//}
//
//TEST(BinaryNumericNumeric, IncorrectInputAfterStartBracket) {
//	EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(2 3)]"), InvalidInputException);
//}
//
//TEST(BinaryNumericNumeric, IncorrectInputBeforeEndBracket) {
//	EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3 2)]"), InvalidInputException);
//}
//
//TEST(BinaryNumericNumeric, IncorrectInputAfterEndBracket) {
//	EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3) 2]"), InvalidInputException);
//}
//
//TEST(BinaryNumericNumeric, Correct) {
//	EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= abs(3)]"));
//}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
