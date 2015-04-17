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

            //! Initialize the model checker
            void InitializeModelChecker() override;

    };


    void ProbabilisticBlackBoxModelCheckerTest::InitializeModelChecker() {
        modelChecker = std::make_shared<mv::ProbabilisticBlackBoxModelChecker>(
                           abstractSyntaxTree, multiscaleArchitectureGraph
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
