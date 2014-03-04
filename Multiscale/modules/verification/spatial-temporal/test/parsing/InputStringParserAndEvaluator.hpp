#ifndef INPUTSTRINGPARSERANDEVALUATOR_HPP
#define INPUTSTRINGPARSERANDEVALUATOR_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

using namespace multiscale;
using namespace multiscaletest;
using namespace multiscale::verification;

static const std::string ERR_MSG_TEST = "The given input string could not be successfully parsed.";


/////////////////////////////////////////////////////////////////
//
// Test function
//
/////////////////////////////////////////////////////////////////

namespace multiscaletest {

    namespace verification {

        //! Parse the input string and evaluate the abstract syntax tree considering the given trace
        /*!
         * \param inputString The input string
         * \param trace       The spatial-temporal trace
         */
        bool parseAndEvaluateInputString(const std::string &inputString, const SpatialTemporalTrace &trace) {
            AbstractSyntaxTree parseResult;
            Parser parser(inputString);

            if (!parser.parse(parseResult)) {
                MS_throw(TestException, ERR_MSG_TEST);
            }

            return parseResult.evaluate(trace);
        }

    };

};

#endif
