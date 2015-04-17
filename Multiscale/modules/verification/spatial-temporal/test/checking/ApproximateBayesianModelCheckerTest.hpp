#ifndef APPROXIMATEBAYESIANMODELCHECKERTEST_HPP
#define APPROXIMATEBAYESIANMODELCHECKERTEST_HPP

#include "ModelCheckerTest.hpp"

#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelChecker.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing the approximate Bayesian model checker
    class ApproximateBayesianModelCheckerTest : public ModelCheckerTest {

        private:

            double alphaParamForBetaPrior;  /*!< The alpha parameter for the beta prior */
            double betaParamForBetaPrior;   /*!< The beta parameter for the beta prior */

            double varianceThreshold;       /*!< The considered variance threshold T */

        public:

            ApproximateBayesianModelCheckerTest() : alphaParamForBetaPrior(1),
                                                    betaParamForBetaPrior(1),
                                                    varianceThreshold(0.1) {}

            //! Set the value of the alpha parameter for the beta prior
            /*!
             * \param alphaParamForBetaPrior    The alpha parameter for the beta prior
             */
            void SetAlphaParamForBetaPrior(double alphaParamForBetaPrior);

            //! Set the value of the beta parameter for the beta prior
            /*!
             * \param betaParamForBetaPrior     The beta parameter for the beta prior
             */
            void SetBetaParamForBetaPrior(double betaParamForBetaPrior);

            //! Set the value of the variance threshold
            /*!
             * \param varianceThreshold     The value of the variance threshold
             */
            void SetVarianceThreshold(double varianceThreshold);

        private:

            //! Initialize the model checker
            void InitializeModelChecker() override;

    };


    void ApproximateBayesianModelCheckerTest::SetAlphaParamForBetaPrior(double alphaParamForBetaPrior) {
        this->alphaParamForBetaPrior = alphaParamForBetaPrior;
    }

    void ApproximateBayesianModelCheckerTest::SetBetaParamForBetaPrior(double betaParamForBetaPrior) {
        this->betaParamForBetaPrior = betaParamForBetaPrior;
    }

    void ApproximateBayesianModelCheckerTest::SetVarianceThreshold(double varianceThreshold) {
        this->varianceThreshold = varianceThreshold;
    }

    void ApproximateBayesianModelCheckerTest::InitializeModelChecker() {
        modelChecker = std::make_shared<mv::ApproximateBayesianModelChecker>(
                           abstractSyntaxTree, multiscaleArchitectureGraph,
                           alphaParamForBetaPrior, betaParamForBetaPrior, varianceThreshold
                       );
    }

};


/////////////////////////////////////////////////////////////////
//
// Test functions
//
/////////////////////////////////////////////////////////////////


TEST_F(ApproximateBayesianModelCheckerTest, CaseTrue) {
    SetAlphaParamForBetaPrior(1);
    SetBetaParamForBetaPrior(1);
    SetVarianceThreshold(0.035);

    EXPECT_TRUE(RunModelCheckingTest());
}

TEST_F(ApproximateBayesianModelCheckerTest, CaseFalse) {
    SetAlphaParamForBetaPrior(1);
    SetBetaParamForBetaPrior(1);
    SetVarianceThreshold(0.002);

    EXPECT_FALSE(RunModelCheckingTest());
}


#endif
