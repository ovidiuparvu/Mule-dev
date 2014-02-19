#ifndef MULTIPLELOGICPROPERTIESTEST_HPP
#define MULTIPLELOGICPROPERTIESTEST_HPP

#include "parsing/InputStringParser.hpp"

using namespace multiscale;
using namespace multiscaletest::verification;


// MultipleLogicProperties

TEST(MultipleLogicProperties, Correct1) {
	EXPECT_TRUE(parseInputString("P = 0.1234 [( d(4) >=  count(regions) ) ^ ( covar(regions, area, regions, perimeter) >= {A} ) V ( {B} = sqrt(add({B}, {C})) )]"));
}

TEST(MultipleLogicProperties, Correct2) {
	EXPECT_TRUE(parseInputString("P <= 0.85934 [~( F [2, 3] ( max(filter(regions, perimeter <= 10), area) >= 2 ) ) => ( G [10, 20] (X (X [10] ( percentile(regions, area, 0.4) = 0.7 ))) ) <=> ( (clusteredness(filter(clusters, (area <= 2) ^ (distanceFromOrigin >= 6) V (angle >= 30) => (centroidX <= 2) <=> (centroidY >= 4)) ) >= 2) U [10, 400] ( kurt(regions, area) <= 0.00001 ) ) ]"));
}

#endif
