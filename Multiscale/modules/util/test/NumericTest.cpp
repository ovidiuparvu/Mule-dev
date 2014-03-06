#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/util/Numeric.hpp"

#include <vector>

using namespace std;
using namespace multiscale;
using namespace multiscaletest;

const double DOUBLE_COMP_ERROR = 1E-6;


// Tests
TEST(Numeric, GreaterOrEqual) {
    EXPECT_TRUE(Numeric::greaterOrEqual(0, 0));
    EXPECT_TRUE(Numeric::greaterOrEqual(2, 0));
    EXPECT_TRUE(Numeric::greaterOrEqual(2, -2));
    EXPECT_TRUE(Numeric::greaterOrEqual(12312312312312312, -12312312312312312));
    EXPECT_TRUE(Numeric::greaterOrEqual(2, 2));
    EXPECT_TRUE(Numeric::greaterOrEqual(2, 2.00001));
    EXPECT_TRUE(Numeric::greaterOrEqual(2, 1.99999));
    EXPECT_FALSE(Numeric::greaterOrEqual(1, 2));
}

TEST(Numeric, LessOrEqual) {
    EXPECT_TRUE(Numeric::lessOrEqual(0, 0));
    EXPECT_TRUE(Numeric::lessOrEqual(0, 2));
    EXPECT_TRUE(Numeric::lessOrEqual(-2, 2));
    EXPECT_TRUE(Numeric::lessOrEqual(-12312312312312312, 12312312312312312));
    EXPECT_TRUE(Numeric::lessOrEqual(2, 2));
    EXPECT_TRUE(Numeric::lessOrEqual(2.00001, 2));
    EXPECT_TRUE(Numeric::lessOrEqual(1.99999, 2));
    EXPECT_FALSE(Numeric::lessOrEqual(2, 1));
}

TEST(Numeric, AlmostEqual) {
    EXPECT_TRUE(Numeric::almostEqual(0, 0));
    EXPECT_FALSE(Numeric::almostEqual(0, 2));
    EXPECT_FALSE(Numeric::almostEqual(-2, 2));
    EXPECT_FALSE(Numeric::almostEqual(-12312312312312312, 12312312312312312));
    EXPECT_TRUE(Numeric::almostEqual(2, 2));
    EXPECT_TRUE(Numeric::almostEqual(2.00001, 2));
    EXPECT_TRUE(Numeric::almostEqual(1.99999, 2));
    EXPECT_TRUE(Numeric::almostEqual(2.00000000001, 2));
    EXPECT_TRUE(Numeric::almostEqual(1.99999999991, 2));
    EXPECT_FALSE(Numeric::almostEqual(2, 1));
}

TEST(Numeric, Average) {
    EXPECT_NEAR(Numeric::average(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::average(std::vector<double>{0}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::average(std::vector<double>{1, 2, 3, 4, 5}), 3, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Covariance) {
    EXPECT_NEAR(Numeric::covariance(std::vector<double>{}, std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::covariance(std::vector<double>{1}, std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::covariance(std::vector<double>{}, std::vector<double>{1}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::covariance(std::vector<double>{2}, std::vector<double>{1}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::covariance(std::vector<double>{1, 2, 3, 4, 5, 6, 7, 8},
                                    std::vector<double>{10, 12, 14, 16, 18, 20, 22, 24}), 12, DOUBLE_COMP_ERROR);
}

TEST(Numeric, GeometricMean) {
    EXPECT_NEAR(Numeric::geometricMean(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::geometricMean(std::vector<double>{-1}), NumericException);
    EXPECT_NEAR(Numeric::geometricMean(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::geometricMean(std::vector<double>{0, 0, 0}), NumericException);
    EXPECT_NEAR(Numeric::geometricMean(std::vector<double>{43, 12, 94, 21, 1934, 12312}), 170.1363015, DOUBLE_COMP_ERROR);
}

TEST(Numeric, HarmonicMean) {
    EXPECT_NEAR(Numeric::harmonicMean(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::harmonicMean(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::harmonicMean(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::harmonicMean(std::vector<double>{0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::harmonicMean(std::vector<double>{43, 12, 94, 21, 1934, 12312}), 36.2658773, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Kurtosis) {
    EXPECT_NEAR(Numeric::kurtosis(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::kurtosis(std::vector<double>{-1}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::kurtosis(std::vector<double>{2}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::kurtosis(std::vector<double>{0, 0, 0, 0}), -13.5, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::kurtosis(std::vector<double>{1, 2, 3, 4}), -1.2, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Maximum) {
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{1, 2, 3, 4}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{4, 3, 2, 1}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::maximum(std::vector<double>{4, 3, 6, 1}), 6, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Median) {
    EXPECT_NEAR(Numeric::median(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{1, 2, 3, 4, 5.791824}), 3, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{4, 3, 5, 2.24, 1}), 3, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{4, 3, 7, 6, -1}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::median(std::vector<double>{4, 3, 7.2, 6, 8, 1}), 6, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Minimum) {
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{1, 2, 3, 4}), 1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{4, 3, 2, 1}), 1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::minimum(std::vector<double>{4, 3, 6, -1}), -1, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Mode) {
    EXPECT_NEAR(Numeric::mode(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{1, 2, 3, 4}), 1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{4, 3, 4, 1}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{4, 3, 2, 4}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{1, 3, 4, 4}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{4, 3, 4, 5, 6, 5, -1}), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::mode(std::vector<double>{4, 3, 4, 5, 6, 5, -1, 5}), 5, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Percentile) {
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{}, 50), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::percentile(std::vector<double>{-1}, 101), NumericException);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{2}, 50), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{-1}, 0), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{2}, 100), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{0, 0, 0, 0}, 80), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{1, 2, 3, 4}, 74), 3, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{4, 3, 6, 1}, 40), 3, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{6, 3, 2, 4}, 2), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::percentile(std::vector<double>{4, 3, 4, 5, 6, 5, -1, 10, 2, 2}, 2), -1, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Product) {
    EXPECT_NEAR(Numeric::product(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{1, 2, 3, 4}), 24, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{4, 3, 4, 1}), 48, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{4, 3, 2, 4}), 96, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::product(std::vector<double>{1, 3, 4, 4}), 48, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::product(std::vector<double>{2432342432434E100, 2342344233E200, 2342342344, 3123215, 3123126, 1233215, 123312}), NumericException);
    EXPECT_NEAR(Numeric::product(std::vector<double>{1, 2, -1, 2, 1, 2, -1, 1}), 8, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Quartile) {
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{}, 50), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::quartile(std::vector<double>{-1}, 101), NumericException);
    EXPECT_THROW(Numeric::quartile(std::vector<double>{-1}, 40), NumericException);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{2}, 50), 2, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::quartile(std::vector<double>{-1}, 0), NumericException);
    EXPECT_THROW(Numeric::quartile(std::vector<double>{2}, 100), NumericException);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{0, 0, 4, 0}, 75), 4, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{1, 2, 3, 4}, 50), 3, DOUBLE_COMP_ERROR);
    EXPECT_THROW(Numeric::quartile(std::vector<double>{4, 3, 6, 1}, 100), NumericException);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 25), 3, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 50), 6, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::quartile(std::vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 75), 9, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Skew) {
    EXPECT_NEAR(Numeric::skew(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{-1}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{2}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{1, 2, 3, 4}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{4, 3, 2, 1}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{4, 3, 2, 4}), -0.85456303832, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{1, 3, 4, 1}), 0.37037037, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::skew(std::vector<double>{1, 4, 8, 4, 1, 7, 12, 1}), 0.80224115, DOUBLE_COMP_ERROR);
}

TEST(Numeric, StandardDeviation) {
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{-1}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{2}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{1, 4.55}), 2.510229073, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{1, 2, 3, 4}), 1.29099449, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{4, 3, 2, 1}), 1.29099449, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{4, 3, 2, -4.3}), 3.740209442, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::standardDeviation(std::vector<double>{-1000, 4, 8.3, 4, 1, 7.4, 12.45124, 1}), 355.501367, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Sum) {
    EXPECT_NEAR(Numeric::sum(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{-1}), -1, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{2}), 2, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{1, 2, 3, 4}), 10, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{4, 3, 2, 1}), 10, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{4, 3, 2, 4}), 13, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{1, 3, 4, 1}), 9, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::sum(std::vector<double>{1, 4, 8.3, 4, 1, 7.4, 12, 1}), 38.7, DOUBLE_COMP_ERROR);
}

TEST(Numeric, Variance) {
    EXPECT_NEAR(Numeric::variance(std::vector<double>{}), 0.0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{-1}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{2}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{1, 4.55}), 6.30124999893443, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{0, 0, 0, 0}), 0, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{1, 2, 3, 4}), 1.6666667732103601, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{4, 3, 2, 1}), 1.6666667732103601, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{4, 3, 2, -4.3}), 13.989166670025951364, DOUBLE_COMP_ERROR);
    EXPECT_NEAR(Numeric::variance(std::vector<double>{-1000, 4, 8.3, 4, 1, 7.4, 12.45124, 1}), 126381.2219626, DOUBLE_COMP_ERROR);
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
