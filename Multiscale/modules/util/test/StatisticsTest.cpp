#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/statistics/BinomialDistribution.hpp"

using namespace multiscale;
using namespace multiscaletest;


// Tests
TEST(Statistics, BinomialCDF) {
    EXPECT_THROW(BinomialDistribution::cdf(3, 4, 0.5), NumericException);
    EXPECT_THROW(BinomialDistribution::cdf(4, 3, 5), NumericException);
    EXPECT_THROW(BinomialDistribution::cdf(1, 9, -0.3), NumericException);
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(10, 2, 0.2), 0.67779953));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(143, 95, 0.7), 0.19961617));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(23, 21, 0.9), 0.68487331));
}
