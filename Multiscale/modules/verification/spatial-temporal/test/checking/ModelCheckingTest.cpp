#include "ApproximateBayesianModelCheckerTest.hpp"
#include "ApproximateProbabilisticModelCheckerTest.hpp"
#include "BayesianModelCheckerTest.hpp"
#include "ProbabilisticBlackBoxModelCheckerTest.hpp"
#include "StatisticalModelCheckerTest.hpp"


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}




