#ifndef BAYESIANMODELCHECKERTEST_HPP
#define BAYESIANMODELCHECKERTEST_HPP

#include "ModelCheckerTest.hpp"

#include "multiscale/verification/spatial-temporal/checking/BayesianModelChecker.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing the Bayesian model checker
    class BayesianModelCheckerTest : public ModelCheckerTest {

        private:

            double alphaParamForBetaPrior;  /*!< The alpha parameter for the beta prior */
            double betaParamForBetaPrior;   /*!< The beta parameter for the beta prior */

            double bayesFactorThreshold;    /*!< The considered bayes factor threshold */

        public:

            BayesianModelCheckerTest() : alphaParamForBetaPrior(1),
                                         betaParamForBetaPrior(1),
                                         bayesFactorThreshold(2) {}

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

            //! Set the value of the Bayes factor threshold
            /*!
             * \param bayesFactorThreshold      The value of the Bayes factor threshold
             */
            void SetBayesFactorThreshold(double bayesFactorThreshold);

        private:

            //! Initialise the model checker
            void InitialiseModelChecker() override;

    };


    void BayesianModelCheckerTest::SetAlphaParamForBetaPrior(double alphaParamForBetaPrior) {
        this->alphaParamForBetaPrior = alphaParamForBetaPrior;
    }

    void BayesianModelCheckerTest::SetBetaParamForBetaPrior(double betaParamForBetaPrior) {
        this->betaParamForBetaPrior = betaParamForBetaPrior;
    }

    void BayesianModelCheckerTest::SetBayesFactorThreshold(double bayesFactorThreshold) {
        this->bayesFactorThreshold = bayesFactorThreshold;
    }

    void BayesianModelCheckerTest::InitialiseModelChecker() {
        modelChecker = std::make_shared<mv::BayesianModelChecker>(
                           abstractSyntaxTree, typeSemanticsTable,
                           alphaParamForBetaPrior, betaParamForBetaPrior, bayesFactorThreshold
                       );
    }

};


/////////////////////////////////////////////////////////////////
//
// Test functions
//
/////////////////////////////////////////////////////////////////


TEST_F(BayesianModelCheckerTest, CaseTrue) {
    SetAlphaParamForBetaPrior(1);
    SetBetaParamForBetaPrior(1);
    SetBayesFactorThreshold(3.5);

    EXPECT_TRUE(RunModelCheckingTest());
}

TEST_F(BayesianModelCheckerTest, CaseFalse) {
    SetAlphaParamForBetaPrior(1);
    SetBetaParamForBetaPrior(1);
    SetBayesFactorThreshold(1.3);

    EXPECT_FALSE(RunModelCheckingTest());
}


#endif
