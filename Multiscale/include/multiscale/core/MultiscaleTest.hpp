#ifndef MULTISCALETEST_HPP
#define MULTISCALETEST_HPP

#include "gtest/gtest.h"


namespace multiscaletest {

    class MultiscaleTest : public ::testing::Test {

        protected:

            bool validationFlag;    /*!< Flag indicating if the test results are valid */

        public:

            virtual ~MultiscaleTest() {};

        protected:

            virtual void SetUp() {}
            virtual void TearDown() {}

            //! Run the test
            virtual void RunTest() = 0;

            //! Validate the results of the test
            virtual void ValidateTestResults() = 0;

    };

};


#endif
