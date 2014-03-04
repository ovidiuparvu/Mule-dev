#ifndef TRACEEVALUATIONTEST_HPP
#define TRACEEVALUATIONTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <string>

//static const std::string ERR_MSG_TEST = "The given input string could not be successfully parsed.";


namespace multiscaletest {

    //! Class for testing evaluation of traces
    class TraceEvaluationTest : public MultiscaleTest {

        protected:

            multiscale::verification::SpatialTemporalTrace trace;   /*!< The spatial temporal trace */
            std::string query;                                      /*!< The query to be checked */

            bool evaluationResult;                                  /*!< The result of the evaluation */

        public:

           //! Run the test with the given string
           bool RunEvaluationTest(const std::string &query);

        protected:

           //! Run the test
           virtual void RunTest() = 0;

           //! Validate the results of the test
           virtual void ValidateTestResults() = 0;

        private:

           //! Initialise the query
           void InitialiseQuery(const std::string &query);

           //! Initialise the trace
           virtual void InitialiseTrace() = 0;

    };

    bool TraceEvaluationTest::RunEvaluationTest(const std::string &query) {
        InitialiseQuery(query);
        InitialiseTrace();

        RunTest();
        ValidateTestResults();

        return evaluationResult;
    }

    void TraceEvaluationTest::InitialiseQuery(const std::string &query) {
        this->query = query;
    }

};

#endif
