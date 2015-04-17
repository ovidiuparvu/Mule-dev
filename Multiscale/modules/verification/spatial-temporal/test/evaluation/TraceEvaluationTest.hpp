#ifndef TRACEEVALUATIONTEST_HPP
#define TRACEEVALUATIONTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/model/NumericStateVariableId.hpp"
#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <limits>
#include <string>

namespace mv = multiscale::verification;

static const std::string ERR_MSG_TEST = "The given input string could not be successfully parsed.";


namespace multiscaletest {

    //! Class for testing evaluation of traces
    class TraceEvaluationTest : public MultiscaleTest {

        protected:

            mv::SpatialTemporalTrace
                trace;                          /*!< The spatial temporal trace */
            mv::MultiscaleArchitectureGraph
                multiscaleArchitectureGraph;    /*!< The multiscale architecture graph */

            std::string query;                  /*!< The query to be checked */

            bool evaluationResult;              /*!< The result of the evaluation */

        public:

            TraceEvaluationTest();

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

        private:

           //! Initialize the query
           /*!
            * \param query  The given query
            */
           void InitializeQuery(const std::string &query);

           //! Initialize the multiscale architecture graph
           virtual void InitializeMultiscaleArchitectureGraph() = 0;

           //! Initialize the trace
           virtual void InitializeTrace() = 0;

    };

};


#endif
