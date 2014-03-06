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
    EXPECT_NEAR(Numeric::average(std::vector<double>{1, 2, 3, 4, 5}), 15, DOUBLE_COMP_ERROR);
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
