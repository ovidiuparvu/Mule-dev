#ifndef BINARYNUMERICNUMERICTEST_HPP
#define BINARYNUMERICNUMERICTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


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

#endif
