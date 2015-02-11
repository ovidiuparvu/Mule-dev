#ifndef TRACEEVALUATIONTEST_HPP
#define TRACEEVALUATIONTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/model/NumericStateVariableId.hpp"
#include "multiscale/verification/spatial-temporal/model/SemanticType.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <limits>
#include <string>

namespace mv = multiscale::verification;

static const std::string ERR_MSG_TEST = "The given input string could not be successfully parsed.";


namespace multiscaletest {

    //! Class for testing evaluation of traces
    class TraceEvaluationTest : public MultiscaleTest {

        protected:

            std::size_t nrOfTimePoints;             /*!< The number of timepoints in the trace */

            NumericStateVariableId
                aNumericStateVariableId;            /*!< The id of the numeric state variable "A" (no type) */
            NumericStateVariableId
                bNumericStateVariableId;            /*!< The id of the numeric state variable "B" (no type) */
            NumericStateVariableId
                aWithTypeNumericStateVariableId;    /*!< The id of the numeric state variable "A" (with type) */
            NumericStateVariableId
                bWithTypeNumericStateVariableId;    /*!< The id of the numeric state variable "B" (with type) */
            NumericStateVariableId
                cNumericStateVariableId;            /*!< The id of the numeric state variable "C" */
            NumericStateVariableId
                dNumericStateVariableId;            /*!< The id of the numeric state variable "D" */

            double aMinValue;                       /*!< The minimum value of numeric state variable "A" */
            double aMaxValue;                       /*!< The maximum value of numeric state variable "A" */
            double bConstantValue;                  /*!< The constant value of numeric state variable "B" */
            double cMinValue;                       /*!< The minimum value of numeric state variable "C" */
            double cMaxValue;                       /*!< The maximum value of numeric state variable "C" */
            double dConstantValue;                  /*!< The constant value of numeric state variable "D" */

            mv::SpatialTemporalTrace
                trace;                              /*!< The spatial temporal trace */
            mv::TypeSemanticsTable
                typeSemanticsTable;                 /*!< The type semantics table */

            std::string query;                      /*!< The query to be checked */

            bool evaluationResult;                  /*!< The result of the evaluation */

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

           //! Initialise the trace
           virtual void InitialiseTrace() = 0;

        private:

           //! Initialise the query
           /*!
            * \param query  The given query
            */
           void InitialiseQuery(const std::string &query);

           //! Initialise the type semantics table
           void InitialiseTypeSemanticsTable();

        protected:

           // Constants
           static const std::string SEMANTIC_TYPE_ORGAN_HEART;
           static const std::string SEMANTIC_TYPE_ORGAN_KIDNEY;
           static const std::string SEMANTIC_TYPE_ORGAN_LIVER;

    };

};


#endif
