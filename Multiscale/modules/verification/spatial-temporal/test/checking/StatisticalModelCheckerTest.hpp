#ifndef STATISTICALMODELCHECKERTEST_HPP
#define STATISTICALMODELCHECKERTEST_HPP

#include "ModelCheckerTest.hpp"

#include "multiscale/verification/spatial-temporal/checking/StatisticalModelChecker.hpp"

using namespace multiscale;
using namespace multiscaletest;


namespace multiscaletest {

    //! Class for testing the statistical model checker
    class StatisticalModelCheckerTest : public ModelCheckerTest {

        private:

            double typeIError;      /*!< The probability of type I errors */
            double typeIIError;     /*!< The probability of type II errors */

        public:

            StatisticalModelCheckerTest() : typeIError(0.05),
                                            typeIIError(0.05) {}

            //! Set the value of the type I error
            /*!
             * \param typeIError    The probability of type I errors occurring
             */
            void SetTypeIError(double typeIError);

            //! Set the value of the type II error
            /*!
             * \param typeIIError   The probability of type II errors occurring
             */
            void SetTypeIIError(double typeIIError);

        private:

            //! Initialize the model checker
            void InitializeModelChecker() override;

    };


    void StatisticalModelCheckerTest::SetTypeIError(double typeIError) {
        this->typeIError = typeIError;
    }

    void StatisticalModelCheckerTest::SetTypeIIError(double typeIIError) {
        this->typeIIError = typeIIError;
    }

    void StatisticalModelCheckerTest::InitializeModelChecker() {
        modelChecker = std::make_shared<mv::StatisticalModelChecker>(
                           abstractSyntaxTree, multiscaleArchitectureGraph,
                           typeIError, typeIIError
                       );
    }

};


/////////////////////////////////////////////////////////////////
//
// Test functions
//
/////////////////////////////////////////////////////////////////


TEST_F(StatisticalModelCheckerTest, CaseTrue) {
    SetTypeIError(0.4);
    SetTypeIIError(0.3);

    EXPECT_TRUE(RunModelCheckingTest());
}

TEST_F(StatisticalModelCheckerTest, CaseFalse) {
    SetTypeIError(0.005);
    SetTypeIIError(0.005);

    EXPECT_FALSE(RunModelCheckingTest());
}


#endif
