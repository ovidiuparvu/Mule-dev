#ifndef TRACEEVALUATIONTEST_HPP
#define TRACEEVALUATIONTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

namespace mv = multiscale::verification;

static const std::string ERR_MSG_TEST = "The given input string could not be successfully parsed.";


namespace multiscaletest {

    //! Class for testing evaluation of traces
    class TraceEvaluationTest : public MultiscaleTest {

        protected:

            mv::SpatialTemporalTrace trace; /*!< The spatial temporal trace */
            std::string query;              /*!< The query to be checked */

            bool evaluationResult;          /*!< The result of the evaluation */

        public:

           //! Run the test with the given string
            /*!
             * \param query The given query
             */
           bool RunEvaluationTest(const std::string &query);

        protected:

           //! Run the test
           virtual void RunTest() override;

           //! Validate the results of the test
           virtual void ValidateTestResults() override;

           //! Initialise the trace
           virtual void InitialiseTrace() = 0;

        private:

           //! Initialise the query
           /*!
            * \param query  The given query
            */
           void InitialiseQuery(const std::string &query);

    };

    bool TraceEvaluationTest::RunEvaluationTest(const std::string &query) {
        InitialiseQuery(query);
        InitialiseTrace();

        RunTest();
        ValidateTestResults();

        return evaluationResult;
    }

    void TraceEvaluationTest::RunTest() {
        AbstractSyntaxTree parseResult;
        Parser parser(query);

        if (!parser.parse(parseResult)) {
            MS_throw(multiscale::TestException, ERR_MSG_TEST);
        }

        evaluationResult = parseResult.evaluate(trace);
    }

    void TraceEvaluationTest::ValidateTestResults() {}

    void TraceEvaluationTest::InitialiseQuery(const std::string &query) {
        this->query = query;
    }

};

#endif
