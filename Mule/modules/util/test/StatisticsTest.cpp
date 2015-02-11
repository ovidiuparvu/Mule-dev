#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/statistics/BetaDistribution.hpp"
#include "multiscale/util/statistics/BinomialDistribution.hpp"

using namespace multiscale;
using namespace multiscaletest;


// Tests
TEST(Statistics, BinomialPDF) {
    EXPECT_THROW(BinomialDistribution::pdf(100, 101, 0.5), NumericException);
    EXPECT_THROW(BinomialDistribution::pdf(88888, 7575, 5), NumericException);
    EXPECT_THROW(BinomialDistribution::pdf(1569790, 57636, -0.3), NumericException);
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::pdf(1463416, 4272, 0.2), 0));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::pdf(146, 42, 0.2), 0.0029797602257014528873));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::pdf(14763, 9335, 0.7), 3.3124796692271547898e-70));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::pdf(567, 212, 0.9), 4.035981802091540183e-204));
}

TEST(Statistics, BinomialCDF) {
    EXPECT_THROW(BinomialDistribution::cdf(3, 4, 0.5), NumericException);
    EXPECT_THROW(BinomialDistribution::cdf(4, 3, 5), NumericException);
    EXPECT_THROW(BinomialDistribution::cdf(1, 9, -0.3), NumericException);
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(10, 2, 0.2), 0.67779952639999974107));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(143, 95, 0.7), 0.19961617866547129441));
    EXPECT_TRUE(Numeric::almostEqual(BinomialDistribution::cdf(23, 21, 0.9), 0.68487331130124440293));
}

TEST(Statistics, BetaCDF) {
    EXPECT_THROW(BetaDistribution::cdf(-2, 4, 0.5), NumericException);
    EXPECT_THROW(BetaDistribution::cdf(0, 4, 0.5), NumericException);
    EXPECT_THROW(BetaDistribution::cdf(1, -4, 0.5), NumericException);
    EXPECT_THROW(BetaDistribution::cdf(1, 0, 0.5), NumericException);
    EXPECT_THROW(BetaDistribution::cdf(4, 3, 5), NumericException);
    EXPECT_THROW(BetaDistribution::cdf(1, 9, -0.3), NumericException);
    EXPECT_TRUE(Numeric::almostEqual(BetaDistribution::cdf(2, 2, 0.6), 0.64799999999999990941));
    EXPECT_TRUE(Numeric::almostEqual(BetaDistribution::cdf(3, 5, 0.4324), 0.64849220828307418962));
    EXPECT_TRUE(Numeric::almostEqual(BetaDistribution::cdf(0.5, 4, 0.876), 0.99993187423340601505));
}
