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
// BinaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericFilter, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(3)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(3)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add()))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add1(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(1 + /*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(volume23D, /*{{ spatial_measures[0].name }}*/)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/ /*{{ spatial_measures[0].name }}*/)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, entropyy_)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/ / 2)))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/) * 1))) > 1]"), InvalidInputException);
}

TEST(BinaryNumericFilter, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= add(/*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/)))) > 1]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericMeasure
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
// BinaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericNumeric, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add({A})) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(3)) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add()) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add a(3, {A})) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add( a 3, {A})) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(a, {A})) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(3 {A})) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(3, bc)) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(3, {A} a )) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] add(3, {A}) a) <= 6]"), InvalidInputException);
}

TEST(BinaryNumericNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 5] add(3, {A})) <= 6]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericSpatial, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(density(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(area(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply()) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply((area(regions), density(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(.area(regions), density(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(2, density(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(area(regions) density(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(area(regions), {B})) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(area(regions), density(regions), perimeter(regions))) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P <= 0.9 [sum(multiply(area(regions), density(regions)) + 3) > 3]"), InvalidInputException);
}

TEST(BinaryNumericSpatial, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [sum(multiply(area(regions), density(regions))) > 3]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST(BinaryNumericTemporal, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add()]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add a(2, 3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add( a 2, 3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, InvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(a, 3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, MissingParametersComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2 3)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, InvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, a)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, 3 a)]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= add(2, 3) a]"), InvalidInputException);
}

TEST(BinaryNumericTemporal, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalMeasure, IncorrectQuaternarySubsetMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [correlation(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalMeasure, CorrectCovar) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalNumeric, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar() >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar V covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(_/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, MissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) ^ /*{{ spatial_measures[0].name }}*/) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <>= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileMeasure
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalQuantileMeasure, IncorrectBinaryStatisticalQuantileMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [midtile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileMeasure, CorrectPercentile) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"));
}

TEST(BinaryStatisticalQuantileMeasure, CorrectQuartile) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileNumeric
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(4.3) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile() <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile ^ quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile ( _ /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, MissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) 4.3) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, InvalidSpatialMeasureCollection) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(heightMeasuring_(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 2]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3, 1.2) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) V true <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalQuantileSpatial
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(4.3)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile()) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile ^ quartile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile ( _ /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, MissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) 4.3)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, InvalidSpatialMeasureCollection) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(heightMeasuring_(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= 2]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3, 1.2)) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3) V true) <= 0.5]"), InvalidInputException);
}

TEST(BinaryStatisticalQuantileSpatial, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min([0, 3] percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 4.3)) <= 0.5]"));
}


/////////////////////////////////////////////////////////
//
//
// BinaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST(BinaryStatisticalSpatial, IncorrectInputMissingParameterOne) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputMissingParameterTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputMissingParametersOneTwo) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar()) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar V covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(_/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, MissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) ^ /*{{ spatial_measures[0].name }}*/)) >= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <>= 0.001]"), InvalidInputException);
}

TEST(BinaryStatisticalSpatial, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [median([0, 3] covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 0.001]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeMeasure
//
//
/////////////////////////////////////////////////////////

TEST(ChangeMeasure, IncorrectChangeMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [z(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 2]"), InvalidInputException);
}

TEST(ChangeMeasure, CorrectDifference) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 2]"));
}

TEST(ChangeMeasure, CorrectRatio) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [r(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST(ChangeTemporalNumericCollection, IncorrectChangeMeasureDf) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(df([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectChangeMeasureDiff) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(diff([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectChangeMeasureRatio) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(ratio([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputBeforeChangeMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(-d([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d[([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d(([0, 10] {A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, MissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d()) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputMissingParameterAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectOpeningBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d[[0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectClosingBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d([0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))]) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d{[0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))}) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectBracketsInverted) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d)[0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))() >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectBracketsDoubled) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d(([0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))))) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d([0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) + 2)) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d([0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) - 1) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectTemporalNumericCollectionRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d(3.01)) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectTemporalNumericCollectionNumericStateVariable) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d({A})) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, IncorrectTemporalNumericCollectionNumericSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(d(count(clusteredness(clusters)))) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(d([0, 10] max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// ChangeTemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(ChangeTemporalNumericMeasure, IncorrectChangeMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [df(4) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputBeforeChangeMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [T ^ d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d V d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(~ max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, MissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d() <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputMissingParameterAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectOpeningBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d[4) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectClosingBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(4] >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d[4] >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectBracketsInverted) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d)4( >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectBracketsDoubled) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d((4)) >= 4]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))), 2) <= 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, MissingComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) 3]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, IncorrectEndOperand) {
    EXPECT_THROW(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= ~(add(2, 3))]"), InvalidInputException);
}

TEST(ChangeTemporalNumericMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [d(max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Comparator
//
//
/////////////////////////////////////////////////////////

TEST(Comparator, IncorrectEqual) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) == 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent1) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <> 3]"), InvalidInputException);
}

TEST(Comparator, IncorrectDifferent2) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) != 3]"), InvalidInputException);
}

TEST(Comparator, CorrectGreaterThan) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 3]"));
}

TEST(Comparator, CorrectLessThan) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 3]"));
}

TEST(Comparator, CorrectGreaterThanOrEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 3]"));
}

TEST(Comparator, CorrectLessThanOrEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

TEST(Comparator, CorrectEqual) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) = 3]"));
}


/////////////////////////////////////////////////////////
//
//
// CompoundConstraint
//
//
/////////////////////////////////////////////////////////

// Binary operators

const static std::vector<std::string> CONSTRAINTS_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});


// CompoundConstraint

TEST(CompoundConstraint, MissingBinaryOperator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ >= 8)))) <= 3]"), InvalidInputException);
}

TEST(CompoundConstraint, MissingConstraints) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " =>))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, MissingFirstConstraint) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 34)))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, MissingSecondConstraint) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ = 34) " + binaryOperator + "))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryBefore) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, BinaryOperatorAsUnaryAfter) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + "))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, TemporalNumericComparisonBeforeBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ({A} >= 3 " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1))))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, UnaryNumericMeasureAfterBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 3)))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, AdditionalOperatorBeforeBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) ~ " + binaryOperator + " count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 3)))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, AdditionalOperatorAfterBinaryOperator) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " " + binaryOperator + " count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 3)))) <= 3]"), InvalidInputException);
    }
}

TEST(CompoundConstraint, Correct) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1)))) <= 3]"));
    }
}

TEST(CompoundConstraint, MultipleCorrect) {
    for (auto &binaryOperator : CONSTRAINTS_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) " + binaryOperator + " (/*{{ spatial_measures[0].name }}*/ = 0.1) " + binaryOperator + " (~ /*{{ spatial_measures[0].name }}*/ >= 4000)))) <= 3]"));
    }
}


/////////////////////////////////////////////////////////
//
//
// CompoundLogicProperty
//
//
/////////////////////////////////////////////////////////

// Binary operators

const static std::vector<std::string> LOGIC_PROPERTIES_BINARY_OPERATORS = std::vector<std::string>({"^", "V", "=>", "<=>"});


// CompoundLogicProperty

TEST(CompoundLogicProperty, MissingBinaryOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"), InvalidInputException);
}

TEST(CompoundLogicProperty, MissingLogicProperties) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, MissingFirstLogicProperty) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, MissingSecondLogicProperty) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, BinaryOperatorAsUnaryBefore) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [" + binaryOperator + " ({A} >= 4) (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, BinaryOperatorAsUnaryAfter) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) " + binaryOperator + "]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, UnaryStatisticalMeasureBeforeBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [(/*{{ spatial_measures[0].name }}*/) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, UnaryNumericMeasureAfterBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, AdditionalOperatorBeforeBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, AdditionalOperatorAfterBinaryOperator) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"), InvalidInputException);
    }
}

TEST(CompoundLogicProperty, Correct) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) ]"));
    }
}

TEST(CompoundLogicProperty, MultipleCorrect) {
    for (auto &binaryOperator : LOGIC_PROPERTIES_BINARY_OPERATORS) {
        EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) " + binaryOperator + " (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 4) " + binaryOperator + " {B} = 3]"));
    }
}


/////////////////////////////////////////////////////////
//
//
// ConstraintParentheses
//
//
/////////////////////////////////////////////////////////

TEST(ConstraintEnclosedByParentheses, MissingParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, MissingParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisLeft) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesisRight) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, InvertedParentheses) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, )/*{{ spatial_measures[0].name }}*/ <= 30.2())) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ExtraParenthesesBothSides) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (((/*{{ spatial_measures[0].name }}*/ <= 30.2)))))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, ParenthesesInWrongOrder) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (((())(/*{{ spatial_measures[0].name }}*/ <= 30.2)))))) <= 3]"), InvalidInputException);
}

TEST(ConstraintEnclosedByParentheses, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectDoubled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((/*{{ spatial_measures[0].name }}*/ <= 30.2))))) <= 3]"));
}

TEST(ConstraintEnclosedByParentheses, CorrectQuadrupled) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ((((/*{{ spatial_measures[0].name }}*/ <= 30.2))))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// Constraint
//
//
/////////////////////////////////////////////////////////

TEST(Constraint, ExtraInputBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(Constraint, ExtraInputAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2, true))) <= 3]"), InvalidInputException);
}

TEST(Constraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(FilterSubset, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, d(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 4.3))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, CorrectSpatialMeasureRealValue) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"));
}

TEST(FilterSubset, CorrectSpatialMeasures) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= /*{{ spatial_measures[0].name }}*/))) <= 3]"));
}

TEST(FilterSubset, CorrectMultiple) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3 ^ /*{{ spatial_measures[0].name }}*/ < 2))) <= 3]"));
}

TEST(FilterSubset, CorrectMultipleComplex) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= sqrt(add(power(subtract(10, /*{{ spatial_measures[0].name }}*/), 2), power(subtract(10, /*{{ spatial_measures[0].name }}*/), 2)))))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FilterSubset
//
//
/////////////////////////////////////////////////////////

TEST(FilterSubset, IncorrectInputMisspelledFilter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(fillter[(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter[(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputMissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3, /*{{ spatial_measures[0].name }}*/ <= 2))) <= 3]"), InvalidInputException);
}

TEST(FilterSubset, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) = 2 V <= 3]"), InvalidInputException);
}

TEST(FilterSubset, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= 4.3))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// FutureLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(FutureLogicProperty, WrongInputMissingStartTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputMissingTimePointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F ({A} >= 4) [2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, WrongInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [ ({A} >= 4) 2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, MissingTimePointComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidStartTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [-2.3, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [2, -3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(FutureLogicProperty, InvalidTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [-3.82, -2.1] ({A} >= 4)]"), InvalidInputException);
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
// GlobalLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(GlobalLogicProperty, WrongInputMissingStartTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputMissingTimePointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G ({A} >= 4) [2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, WrongInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [ ({A} >= 4) 2, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, MissingTimePointComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidStartTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [-2.3, 3] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [2, -3.8] ({A} >= 4)]"), InvalidInputException);
}

TEST(GlobalLogicProperty, InvalidTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [G [-4.0, -3.8] ({A} >= 4)]"), InvalidInputException);
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
// HeterogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST(HeterogeneousTimeSeriesComponent, WrongAlternativeSpike) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(spike, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HeterogeneousTimeSeriesComponent, WrongAlternativeSink) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(sink, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HeterogeneousTimeSeriesComponent, WrongAlternativeTrough) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(trough, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HeterogeneousTimeSeriesComponent, CorrectPeak) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(enteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HeterogeneousTimeSeriesComponent, CorrectValley) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(enteringValue(valley, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousHomogeneousTimeSeries
//
//
/////////////////////////////////////////////////////////

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputBeforeHomogeneousTimeSeriesMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(+values(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputWrongHomogeneousTimeSeriesMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(cvalues(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values of(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values((ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputInvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(valley, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputMissingFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputMissingCommaBetweenParameters) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(ascent [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputMissingSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(ascent)) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputInvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(ascent, [0, 5] /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), {A})) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))), 2) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputMissingParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputInvertedParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values)ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))() > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputDoubledParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values((ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))))) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, IncorrectInputWrongParanthesesType) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values{ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))}) > 0]"), InvalidInputException);
}

TEST(HomogeneousHomogeneousTimeSeries, CorrectNumericStateVariables) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [avg(timeSpan(plateau, [0, 11] {B})) = 12]"));
}

TEST(HomogeneousHomogeneousTimeSeries, CorrectSpatialEntities) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST(HomogeneousTimeSeriesComponent, IncorrectAlternativeHeterogeneousTimeSeriesComponent) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(values(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousTimeSeriesComponent, CorrectAscent) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(ascent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HomogeneousTimeSeriesComponent, CorrectDescent) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(descent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HomogeneousTimeSeriesComponent, CorrectPlateau) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(plateau, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HomogeneousTimeSeriesComponent, CorrectUniformAscent) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(uniformAscent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HomogeneousTimeSeriesComponent, CorrectUniformDescent) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(uniformDescent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// HomogeneousTimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST(HomogeneousTimeSeriesMeasure, IncorrectAlternativeTimeSeriesMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(exitingValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(HomogeneousTimeSeriesMeasure, CorrectTimeSpan) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(timeSpan(uniformAscent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}

TEST(HomogeneousTimeSeriesMeasure, CorrectValue) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(values(uniformDescent, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// LogicPropertyParentheses
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
// LogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(LogicProperty, ExtraInputBeforeLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [aaa count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputInsideLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) aaa >= 2]"), InvalidInputException);
}

TEST(LogicProperty, ExtraInputAfterLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2 aaa]"), InvalidInputException);
}

TEST(LogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// MultipleLogicProperties
//
//
/////////////////////////////////////////////////////////

TEST(MultipleLogicProperties, Correct1) {
    EXPECT_TRUE(parseInputString("P >= 0.1234 [( d(4) >=  count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) ) ^ ( covar(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST(MultipleLogicProperties, Correct2) {
    EXPECT_TRUE(parseInputString("P <= 0.85934 [~( F [2, 3] ( max(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 10))) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s), 0.4) = 0.7 ))) ) <=> ( (count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 2) ^ (/*{{ spatial_measures[0].name }}*/ >= 6) V (/*{{ spatial_measures[0].name }}*/ >= 30) => (/*{{ spatial_measures[0].name }}*/ <= 2) <=> (/*{{ spatial_measures[0].name }}*/ >= 4)) )) >= 2) U [10, 400] ( kurt(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 0.00001 ) ) ]"));
}


/////////////////////////////////////////////////////////
//
//
// NextKLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NextKLogicProperty, IncorrectInputMissingTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, IncorrectInputAfterNextSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X 2 [B] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, IncorrectValueForNextTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X [B] ({A} >= 4)]"), InvalidInputException);
}

TEST(NextKLogicProperty, RealValueForNextTimePoints) {
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
// NextLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(NextLogicProperty, IncorrectNextSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [N ({A} >= 4)]"), InvalidInputException);
}

TEST(NextLogicProperty, IncorrectInputAfterNextSymbol) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X {B} ({A} >= 4)]"), InvalidInputException);
}

TEST(NextLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [X ({A} >= 4)]"));
}


/////////////////////////////////////////////////////////
//
//
// NotConstraint
//
//
/////////////////////////////////////////////////////////

TEST(NotConstraint, IncorrectOperator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, !(/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) ~))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorAfterConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ = 2.4) ~))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, OperatorBeforeConstraintAndExtraConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2) (/*{{ spatial_measures[0].name }}*/ = 2.4)))) <= 3]"), InvalidInputException);
}

TEST(NotConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ~ (/*{{ spatial_measures[0].name }}*/ <= 30.2)))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// NotLogicProperty
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
// NumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericMeasure, WrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 3] geomean)]"), InvalidInputException);
}

TEST(NumericMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 3] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST(NumericMeasureCollection, WrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max({A}) > 0]"), InvalidInputException);
}

TEST(NumericMeasureCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericSpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericSpatialMeasure, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [entropy__(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= add(2, 3)]"), InvalidInputException);
}

TEST(NumericSpatialMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= add(2, 3)]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStateVariable
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

TEST(NumericStateVariable, IncorrectSquareBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[A] <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectRoundBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(A) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingLeftParanthesisForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}scaleAndSubsystem = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingRightParanthesisForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Heart <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingBothParanthesesForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}scaleAndSubsystem = Organ.Heart <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingScaleAndSubsystemKeywordForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}( = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingEqualComparatorForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingScaleAndSubsystemValueForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = ) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingScaleAndSubsystemKeywordAndEqualComparatorForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingAllForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}() <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectLeftParanthesisForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}[scaleAndSubsystem = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectRightParanthesisForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Heart] <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectParanthesesForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}{scaleAndSubsystem = Organ.Heart} <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemSpecifierForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystemm = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemSpecifierForScaleAndSubsystemConstraint2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(tscaleAndSubsystem = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectComparatorForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem > Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemInvalidCharacterForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = *) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemMissingValueBeforeDotForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = .Organ) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemMissingValueAfterDotForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = Organ.) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, IncorrectScaleAndSubsystemMissingValueBetweenDotsForScaleAndSubsystemConstraint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = Organ..Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingNumericStateVariableName) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{}(scaleAndSubsystem = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, MissingNumericStateVariableNameAndBraces) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(scaleAndSubsystem = Organ.Heart) <= 3]"), InvalidInputException);
}

TEST(NumericStateVariable, CorrectNumericStateVariableSimple1) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= 3]"));
}

TEST(NumericStateVariable, CorrectNumericStateVariableSimple2) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{a2#0f-} <= 3]"));
}

TEST(NumericStateVariable, CorrectNumericStateVariableSimple3) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./QWERTYUIOPASDFGHJKL:\"|>ZXCVBNM<>?} <= 3]"));
}

TEST(NumericStateVariable, CorrectNumericStateVariableWithScaleAndSubsystemConstraint4) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem = Organ.Heart) <= 3]"));
}

TEST(NumericStateVariable, CorrectNumericStateVariableWithScaleAndSubsystemConstraint5) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A}  (scaleAndSubsystem = Organ.Heart) <= 3]"));
}

TEST(NumericStateVariable, CorrectNumericStateVariableWithScaleAndSubsystemConstraint6) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A}(scaleAndSubsystem   =   Organ.Heart) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// NumericStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST(NumericStatisticalMeasure, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [X cardinality__(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"), InvalidInputException);
}

TEST(NumericStatisticalMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [X count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 1]"));
}


/////////////////////////////////////////////////////////
//
//
// PrimarySpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST(PrimarySpatialMeasureCollection, IncorrectInputBeforeSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(volume__2D__(/*{{ spatial_entities[0].name }}*/s)) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputAfterSpatialMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/s(/*{{ spatial_entities[0].name }}*/s)) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputMissingFirstParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/ /*{{ spatial_entities[0].name }}*/s)) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputMissingSecondParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputInvalidSubset) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(cluster__)) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputMissingSubset) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/()) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputMissingSubsetAndParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/) > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, IncorrectInputMissingAll) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg() > 12.1]"), InvalidInputException);
}

TEST(PrimarySpatialMeasureCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 12.1]"));
}


/////////////////////////////////////////////////////////
//
//
// ProbabilisticLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(ProbabilisticLogicProperty, IncorrectProbabilitySymbol) {
    EXPECT_THROW(parseInputString("PT >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectProbabilitySymbol2) {
    EXPECT_THROW(parseInputString("Prob >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectComparator) {
    EXPECT_THROW(parseInputString("P != 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectEqualComparator) {
    EXPECT_THROW(parseInputString("P = 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLow) {
    EXPECT_THROW(parseInputString("P >= -0.1 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooLowMinor) {
    EXPECT_THROW(parseInputString("P >= -0.000000001 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHigh) {
    EXPECT_THROW(parseInputString("P >= 2.9 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, InvalidProbabilityValueTooHighMinor) {
    EXPECT_THROW(parseInputString("P >= 1.000000001 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectLogicProperty) {
    EXPECT_THROW(parseInputString("P >= 0.3 [T]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftMissing) {
    EXPECT_THROW(parseInputString("P >= 0.3 count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightMissing) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesRightExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesLeftRightExtra) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesInverted) {
    EXPECT_THROW(parseInputString("P >= 0.3 ]count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2["), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParanthesesClosing) {
    EXPECT_THROW(parseInputString("P >= 0.3 []count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2[]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, IncorrectlyEnclosingParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [[[count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]][]"), InvalidInputException);
}

TEST(ProbabilisticLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMin) {
    EXPECT_TRUE(parseInputString("P >= 0.0 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityMax) {
    EXPECT_TRUE(parseInputString("P >= 1.0 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityLow) {
    EXPECT_TRUE(parseInputString("P >= 0.00000001 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}

TEST(ProbabilisticLogicProperty, ProbabilityHigh) {
    EXPECT_TRUE(parseInputString("P >= 0.99999999 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// ScaleAndSubsystem
//
//
/////////////////////////////////////////////////////////

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemInvalidCharacter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = !) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemMissingValuesAfterAndBeforeDot) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = .) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemMissingValueBeforeDot) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = .Heart) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemMissingValueAfterDot) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = Heart.) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemCommaInsteadOfDot) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = Organ,Heart) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemManyDots) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = Organ..Heart) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemInvalidValuesBeforeAndAfterDots) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = $.*) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, IncorrectScaleAndSubsystemSpaceBeforeAndAfterDot) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = Organ . Kidney) >= 2]"), InvalidInputException);
}

TEST(ScaleAndSubsystem, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} (scaleAndSubsystem = Organ.Heart) >= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityMeasure
//
//
/////////////////////////////////////////////////////////

TEST(SimilarityMeasure, IncorrectSimilarityMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [approximately-similar([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityMeasure, CorrectAntiSimilar) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"));
}

TEST(SimilarityMeasure, CorrectSimilar) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [similar([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// SimilarityTemporalNumericCollectionAttribute
//
//
/////////////////////////////////////////////////////////

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite(([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite( _ [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectFirstParameterType) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite({A}, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingFirstParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectSecondParameterType) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), {A}, 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingSecondParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingSecondParameterExcludingComma) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), , 2)]"), InvalidInputException);
}
 
TEST(SimilarityTemporalNumericCollectionAttribute, MissingFirstAndSecondParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite(2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputInvalidThirdParameterType) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), {B})]"), InvalidInputException);
}
 
TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2 + 1)]"), InvalidInputException);
}
 
TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2) V True]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputExtraParameter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2, 4)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputBetweenFirstAndSecondParameters) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 4, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, IncorrectInputBetweenSecondAndThirdParameters) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingParameters) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite()]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingParametersAndParantheses) {
    EXPECT_THROW(parseInputString("P <= 0.9 [opposite]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, MissingSimilarityMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"), InvalidInputException);
}

TEST(SimilarityTemporalNumericCollectionAttribute, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [opposite([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)), 2)]"));
}


/////////////////////////////////////////////////////////
//
//
// SpatialMeasure
//
//
/////////////////////////////////////////////////////////

TEST(SpatialMeasure, IncorrectSpatialMeasureInFilter) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, height__ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(SpatialMeasure, IncorrectSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(height__(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

/*{% for spatial_measure in spatial_measures %}*/
TEST(SpatialMeasure, Correct/*{{ spatial_measure.name|first_to_upper }}*/InFilter) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measure.name }}*/ <= 30.2))) <= 3]"));
}

/*{% endfor %}*/
/*{% for spatial_measure in spatial_measures %}*/
TEST(SpatialMeasure, Correct/*{{ spatial_measure.name|first_to_upper }}*/) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measure.name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SpatialMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST(SpatialMeasureCollection, IncorrectAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [F [0, 11] avg(avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 12.1]"), InvalidInputException);
}

TEST(SpatialMeasureCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [F [0, 11] avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > 12.1]"));
}


/////////////////////////////////////////////////////////
//
//
// Subset
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
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST(SubsetOperation, IncorrectInputWrongSubsetOperationAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(multiplication(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetOperation, CorrectDifference) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(difference(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"));
}

TEST(SubsetOperation, CorrectIntersection) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(intersection(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"));
}

TEST(SubsetOperation, CorrectUnion) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// SubsetSpecific
//
//
/////////////////////////////////////////////////////////

TEST(SubsetSpecific, IncorrectInputWrongSubsetAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(groups) <= 3]"), InvalidInputException);
}

TEST(SubsetSpecific, Correct/*{{ spatial_entities[0].name|first_to_upper }}*/s) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

/*{% for spatial_entity in spatial_entities[1:] %}*/
TEST(SubsetSpecific, Correct/*{{ spatial_entity.name|first_to_upper }}*/s) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 3]"));
}

/*{% endfor %}*/

/////////////////////////////////////////////////////////
//
//
// SubsetSubsetOperation
//
//
/////////////////////////////////////////////////////////

TEST(SubsetSubsetOperation, IncorrectInputWrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(division(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union2(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s V /*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingFirstArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(, /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSeparatorComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingCommaAndArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputMissingSecondArgument) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, ))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s => /*{{ spatial_entities[0].name }}*/s))) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s) [0, 10])) <= 3]"), InvalidInputException);
}

TEST(SubsetSubsetOperation, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(union(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericCollection
//
//
/////////////////////////////////////////////////////////

TEST(TemporalNumericCollection, IncorrectInputWrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max({A}) > 2]"), InvalidInputException);
}

TEST(TemporalNumericCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 2]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericComparison
//
//
/////////////////////////////////////////////////////////

TEST(TemporalNumericComparison, NumericMeasureFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 >= {A}"), InvalidInputException);
}

TEST(TemporalNumericComparison, NumericMeasureFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [4 {A} >=]"), InvalidInputException);
}

TEST(TemporalNumericComparison, ComparatorFirst1) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4 {A}]"), InvalidInputException);
}

TEST(TemporalNumericComparison, ComparatorFirst2) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= {A} 4]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectOrder) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} 4 >=]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputMissingFirstOperand) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>= 4]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputMissingComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} 4]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputMissingSecondOperand) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} >=]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputMissingBothOperands) {
    EXPECT_THROW(parseInputString("P >= 0.3 [>=]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputMissingBothOperandsAndComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 []"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputAfterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} - 1 >= 2.2]"), InvalidInputException);
}

TEST(TemporalNumericComparison, IncorrectInputAfterComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} >= 1 + 2.2]"), InvalidInputException);
}

TEST(TemporalNumericComparison, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} >= 4.2]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(TemporalNumericMeasure, WrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [__geographicmean(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) < 2]"), InvalidInputException);
}

TEST(TemporalNumericMeasure, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4]"));
}


/////////////////////////////////////////////////////////
//
//
// TemporalNumericMeasureCollection
//
//
/////////////////////////////////////////////////////////

TEST(TemporalNumericMeasureCollection, IncorrectInputBeforeBeginParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min(~ [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingBeginParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min(0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingBeginTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputInvalidBeginTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([-11, 100] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, ] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputInvalidEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([11, 100a] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingEndTimePointAndComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputExtraTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 11, 100] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputMissingEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 11 count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputExtraSurroundingParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 11] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputBeforeNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 11] -count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, IncorrectInputAfterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"), InvalidInputException);
}

TEST(TemporalNumericMeasureCollection, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min([0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST(TimeSeriesComponent, IncorrectInputBeforeTimeSeriesComponent) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue((plateau)valley, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesComponent, IncorrectParanthesisBeforeTimeSeriesComponent) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue((valley, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesComponent, IncorrectInputAfterTimeSeriesComponent) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(valley(valley), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesComponent, IncorrectParanthesisAfterTimeSeriesComponent) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(valley), [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesComponent, IncorrectInputInvalidAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(valleys, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesComponent, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(enteringValue(plateau, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesMeasure
//
//
/////////////////////////////////////////////////////////

TEST(TimeSeriesMeasure, IncorrectInputWrongAlternative) {
    EXPECT_THROW(parseInputString("P >= 0.3 [min(values(peak, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"), InvalidInputException);
}

TEST(TimeSeriesMeasure, CorrectEnteringTime) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min(enteringTime(peak, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"));
}

TEST(TimeSeriesMeasure, CorrectEnteringValue) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min(enteringValue(peak, [0, 11] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) = 1]"));
}


/////////////////////////////////////////////////////////
//
//
// TimeSeriesTimeSeriesComponent
//
//
/////////////////////////////////////////////////////////

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputBeforeTimeSeriesMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(+enteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputWrongTimeSeriesMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(wenteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputBeforeStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue () (peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputAfterStartParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(()peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputInvalidFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(climb, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputMissingFirstParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputMissingCommaBetweenParameters) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(peak [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputMissingSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(peak)) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputInvalidSecondParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(peak, [0, 5] /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputBeforeEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) < 2)) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputAfterEndParanthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) [0, 3]) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputMissingParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputInvertedParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue)peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))() > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputDoubledParantheses) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue((peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))))) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, IncorrectInputWrongParanthesesType) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(enteringValue{peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))}) > 0]"), InvalidInputException);
}

TEST(TimeSeriesTimeSeriesComponent, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(enteringValue(peak, [0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))) > 0]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericFilter
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericFilter, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs()))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs ^ sqrt(/*{{ spatial_measures[0].name }}*/)))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(1, /*{{ spatial_measures[0].name }}*/))))]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/, 3)))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/) * 2))) > 1]"), InvalidInputException);
}

TEST(UnaryNumericFilter, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= abs(/*{{ spatial_measures[0].name }}*/)))) > 1]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericMeasure
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericMeasure, IncorrectUnaryNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= frac(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"), InvalidInputException);
}

TEST(UnaryNumericMeasure, CorrectAbs) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= abs(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectCeil) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= ceil(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectFloor) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= floor(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectRound) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= round(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectSign) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= sign(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectSqrt) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= sqrt(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}

TEST(UnaryNumericMeasure, CorrectTrunc) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= trunc(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)))]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericNumeric
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericNumeric, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max() <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max min([0, 11] {A}) <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(+[0, 11] {A}) <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 11] {A}-) <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 11] {A})^2 <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputDoubleBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(([0, 11] {A})) <= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputMissingComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(([0, 11] {A})) abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputMissingFirstOperand) {
    EXPECT_THROW(parseInputString("P >= 0.3 [<= abs(3)]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputMissingSecondOperand) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max(([0, 11] {A})) <=]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, IncorrectInputMissingBothOperands) {
    EXPECT_THROW(parseInputString("P >= 0.3 [<=]"), InvalidInputException);
}

TEST(UnaryNumericNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 11] {A}) <= abs(3)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericSpatial
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericSpatial, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(round()) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(roundabs(perimeter(regions))) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(round(0.2 + perimeter(regions))) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(round(perimeter(regions) % 3)) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(round(perimeter(regions)) + 0.9) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, IncorrectInputDoubleBrackets) {
    EXPECT_THROW(parseInputString("P > 0.23 [product(round((perimeter(regions)))) = 4]"), InvalidInputException);
}

TEST(UnaryNumericSpatial, Correct) {
    EXPECT_TRUE(parseInputString("P > 0.23 [product(round(perimeter(regions))) = 4]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryNumericTemporal
//
//
/////////////////////////////////////////////////////////

TEST(UnaryNumericTemporal, IncorrectInputMissingParameter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs()]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs 2(3)]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(2 3)]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3 2)]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs(3) 2]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, IncorrectInputDoubleBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [{A} <= abs((3))]"), InvalidInputException);
}

TEST(UnaryNumericTemporal, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [{A} <= abs(3.0)]"));
}


/////////////////////////////////////////////////////////
//
//
// UnarySpatialConstraint
//
//
/////////////////////////////////////////////////////////

TEST(UnarySpatialConstraint, IncorrectSpatialMeasureBeforeConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ ^ /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputSpatialEntityInsteadOfSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_entities[0].name }}*/s <= 2))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, <= 30.2))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ 30.2))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ >= ))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingComparatorNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasureNumericMeasure) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, >=))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputMissingSpatialMeasureComparator) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, 4.4))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, IncorrectInputEmptyConstraint) {
    EXPECT_THROW(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, ()))) <= 3]"), InvalidInputException);
}

TEST(UnarySpatialConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P <= 0.9 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/ <= 30.2))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalMeasure
//
//
/////////////////////////////////////////////////////////

TEST(UnaryStatisticalMeasure, IncorrectUnaryStatisticalMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [arithmeticmean__(/*{{ spatial_entities[0].name }}*/s, /*{{ spatial_measures[0].name }}*/) ^ geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalMeasure, CorrectAvg) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectCount) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectGeomean) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [geomean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectHarmean) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [harmean(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectKurt) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [kurt(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectMax) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectMedian) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [median(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectMin) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [min(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectMode) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [mode(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectProduct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [product(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectSkew) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [skew(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectStdev) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [stdev(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectSum) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [sum(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}

TEST(UnaryStatisticalMeasure, CorrectVar) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [var(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalNumeric
//
//
/////////////////////////////////////////////////////////

TEST(UnaryStatisticalNumeric, IncorrectInputNoSubset) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count() <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count [ (/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count( [ /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) } ) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) ) } <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, IncorrectInputDoubleBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count((/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalNumeric, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryStatisticalSpatial
//
//
/////////////////////////////////////////////////////////

TEST(UnaryStatisticalSpatial, IncorrectInputNoSubset) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count()) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, IncorrectInputBeforeStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count [ (/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, IncorrectInputAfterStartBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count( [ /*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, IncorrectInputBeforeEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) } )) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, IncorrectInputAfterEndBracket) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) ) }) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, IncorrectInputDoubleBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [max([0, 5] count((/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s) ))) <= 2]"), InvalidInputException);
}

TEST(UnaryStatisticalSpatial, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [max([0, 5] count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s))) <= 2]"));
}


/////////////////////////////////////////////////////////
//
//
// UnaryScaleAndSubsystemConstraint
//
//
/////////////////////////////////////////////////////////

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputWrongScaleAndSubsystemKeywordExtraLetterAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystemm = Organ.Heart))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputWrongScaleAndSubsystemKeywordExtraLetterBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, tscaleAndSubsystem = Organ.Heart))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputBeforeScaleAndSubsystemKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, 0 ^ scaleAndSubsystem = Organ.Heart))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputAfterScaleAndSubsystemKeyword) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem += Organ.Heart))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputAfterComparator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem = *))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, IncorrectInputAfterFilterNumericMeasure) {
    EXPECT_THROW(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem >= Organ.Heart - 0.3))) <= 3]"), InvalidInputException);
}

TEST(UnaryScaleAndSubsystemConstraint, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [count(/*{{ spatial_measures[0].name }}*/(filter(/*{{ spatial_entities[0].name }}*/s, scaleAndSubsystem = Organ.Heart))) <= 3]"));
}


/////////////////////////////////////////////////////////
//
//
// UntilLogicProperty
//
//
/////////////////////////////////////////////////////////

TEST(UntilLogicProperty, IncorrectInputMissingStartTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingEndTimePoint) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingTimePoints) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputMissingTimePointsAndBrackets) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryBefore) {
    EXPECT_THROW(parseInputString("P >= 0.3 [U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, UntilOperatorAsUnaryAfter) {
    EXPECT_THROW(parseInputString("P >= 0.3 [(count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4) U [2, 3]]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputBeforeUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ({A} >= 4) U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorBeforeUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) ~ U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, IncorrectInputAfterUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] ({A} >= 4) (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, AdditionalOperatorAfterUntilOperator) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] V (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeStartParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U ({A} >= 4) [A, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterStartParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [ ({A} >= 4) 2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, MissingTimePointsComma) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [2 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimePointInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, StartTimePointNegativeRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [-1.0, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimePointInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, A] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, EndTimePointNegativeRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, -3.0] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimePointsInvalid) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [A, B] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, TimePointsNegativeRealNumber) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [-3.0, -1.0] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputBeforeEndParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3 ({A} >= 4) ] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, WrongInputAfterEndParenthesis) {
    EXPECT_THROW(parseInputString("P >= 0.3 [({A} >= 4) U [1, 3] ({A} >= 4) (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"), InvalidInputException);
}

TEST(UntilLogicProperty, Correct) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) >= 4)]"));
}

TEST(UntilLogicProperty, MultipleCorrect) {
    EXPECT_TRUE(parseInputString("P >= 0.3 [({A} >= 4) U [2, 3] (count(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) <= 4) <=> {B} = 3]"));
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
