#ifndef NUMERICSTATEVARIABLESPERFORMANCETEST_HPP
#define NUMERICSTATEVARIABLESPERFORMANCETEST_HPP

#include "NumericCsvModelCheckingPerformanceTest.hpp"

using namespace multiscaletest;


///////////////////////////////////////////////////////////////////////////////
//
// Numeric state variables related performance tests
//
///////////////////////////////////////////////////////////////////////////////

TEST_F(NumericCsvModelCheckingPerformanceTest, ManyNumericStateVariablesWithMediumLengthNames) {
    EXPECT_LE(
        RunNumericCsvModelCheckingPerformanceTest(
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/performance/medium_length_numeric_state_variable_names/logic_statements.in",
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/performance/medium_length_numeric_state_variable_names/time_series.csv"
        ),
        10000000000
    );
}


#endif
