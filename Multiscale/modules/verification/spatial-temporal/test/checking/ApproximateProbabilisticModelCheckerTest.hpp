#ifndef APPROXIMATEPROBABILISTICMODELCHECKERTEST_HPP
#define APPROXIMATEPROBABILISTICMODELCHECKERTEST_HPP

#include "ModelCheckerTest.hpp"

#include "multiscale/verification/spatial-temporal/checking/ApproximateProbabilisticModelChecker.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing the approximate probabilistic model checker
    class ApproximateProbabilisticModelCheckerTest : public ModelCheckerTest {

        private:

            double delta;   /*!< The value of delta in the Chernoff-Hoeffding inequality */
            double epsilon; /*!< The value of epsilon in the Chernoff-Hoeffding inequality */

        public:

            ApproximateProbabilisticModelCheckerTest() : delta(0.5),
                                                         epsilon(1) {}

            //! Set the value of delta
            /*!
             * \param delta     The value of delta
             */
            void SetDelta(double delta);

            //! Set the value of epsilon
            /*!
             * \param epsilon   The value of epsilon
             */
            void SetEpsilon(double epsilon);

        private:

            //! Initialize the model checker
            void InitializeModelChecker() override;

    };


    void ApproximateProbabilisticModelCheckerTest::SetDelta(double delta) {
        this->delta = delta;
    }

    void ApproximateProbabilisticModelCheckerTest::SetEpsilon(double epsilon) {
        this->epsilon = epsilon;
    }

    void ApproximateProbabilisticModelCheckerTest::InitializeModelChecker() {
        modelChecker = std::make_shared<mv::ApproximateProbabilisticModelChecker>(
                           abstractSyntaxTree, multiscaleArchitectureGraph, delta, epsilon
                       );
    }

};


/////////////////////////////////////////////////////////////////
//
// Test functions
//
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//
// No "CaseTrue" test case was considered because more traces than are available would have been required
//
/////////////////////////////////////////////////////////////////


TEST_F(ApproximateProbabilisticModelCheckerTest, CaseFalse) {
    SetDelta(0.005);
    SetEpsilon(0.005);

    EXPECT_FALSE(RunModelCheckingTest());
}


#endif
