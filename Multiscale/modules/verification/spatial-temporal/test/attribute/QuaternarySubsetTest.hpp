#ifndef QUATERNARYSUBSETTEST_HPP
#define QUATERNARYSUBSETTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// QuaternarySubset

TEST(QuaternarySubset, IncorrectInputMissingParameterOne) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(area, regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterTwo) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParameterFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area, regions) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwo) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(area, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(area, regions) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, regions) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersThreeFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoThree) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(regions) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersTwoThreeFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputMissingParametersOneTwoThreeFour) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar() >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputBeforeStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar V covar(clusters, area, regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputAfterStartBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(_clusters, area, regions, perimeter) >= 0.001"), InvalidInputException);
}

TEST(QuaternarySubset, MissingFirstComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters area, regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, MissingSecondComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area regions, perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, MissingThirdComma) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area, regions perimeter) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputBeforeEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area, regions, perimeter ^ area) >= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, IncorrectInputAfterEndBracket) {
	EXPECT_THROW(parseInputString("P >= 0.3 [covar(clusters, area, regions perimeter) <>= 0.001]"), InvalidInputException);
}

TEST(QuaternarySubset, Correct) {
	EXPECT_TRUE(parseInputString("P >= 0.3 [covar(clusters, area, regions, perimeter) >= 0.001]"));
}

#endif
