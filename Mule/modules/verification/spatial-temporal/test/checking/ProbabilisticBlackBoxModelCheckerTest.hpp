#ifndef PROBABILISTICBLACKBOXMODELCHECKERTEST_HPP
#define PROBABILISTICBLACKBOXMODELCHECKERTEST_HPP

#include "ModelCheckerTest.hpp"

#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelChecker.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing the probabilistic black-box model checker
    class ProbabilisticBlackBoxModelCheckerTest : public ModelCheckerTest {

        private:

            //! Initialise the model checker
            void InitialiseModelChecker() override;

    };


    void ProbabilisticBlackBoxModelCheckerTest::InitialiseModelChecker() {
        modelChecker = std::make_shared<mv::ProbabilisticBlackBoxModelChecker>(
                           abstractSyntaxTree, typeSemanticsTable
                       );
    }

};


/////////////////////////////////////////////////////////////////
//
// Test functions
//
/////////////////////////////////////////////////////////////////


TEST_F(ProbabilisticBlackBoxModelCheckerTest, CaseFalse) {
    EXPECT_FALSE(RunModelCheckingTest());
}


#endif
