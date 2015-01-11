#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/InvalidOutputException.hpp"
#include "multiscale/verification/spatial-temporal/data/MSTMLSubfilesMerger.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"

using namespace multiscale;
using namespace multiscaletest;
using namespace multiscale::verification;

// The following line contains a #define statement in case the
// project build type is "Debug". Otherwise the line will be blank.
// The #define statement is used to include/exclude test cases from 
// the unit test MSTMLSubfilesMerger



///////////////////////////////////////////////////////////////////////////////
//
// Tests
//
///////////////////////////////////////////////////////////////////////////////

TEST(MSTMLSubfilesMerger, InvalidNoTracesNoTimepointsInvalidOutputFile) {
    EXPECT_THROW(
        MSTMLSubfilesMerger(
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_traces_no_timepoints_invalid_output_file/traces/",
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_traces_no_timepoints_invalid_output_file/timepoints_values.csv"
        ),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidNoTraces) {
    EXPECT_THROW(
        MSTMLSubfilesMerger(
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_traces/traces/",
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_traces/timepoints_values.csv"
        ),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidNoTimepoints) {
    EXPECT_THROW(
        MSTMLSubfilesMerger(
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_timepoints/traces/",
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_timepoints/timepoints_values.csv"
        ),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidWrongOutputFile) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_wrong_output_file/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_wrong_output_file/timepoints_values.csv"
    );

    // Merge the MSTML subfiles
    mstmlSubfilesMerger.mergeMSTMLSubfiles();

    EXPECT_THROW(
        mstmlSubfilesMerger.outputResultingMSTMLFile(
            "///home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_wrong_output_file/"
        ),
        std::exception
    );
}

TEST(MSTMLSubfilesMerger, InvalidNoData) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_data/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_data/timepoints_values.csv"
    );

    // Merge the MSTML subfiles
    mstmlSubfilesMerger.mergeMSTMLSubfiles();

    EXPECT_THROW(
        mstmlSubfilesMerger.outputResultingMSTMLFile(
            "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_no_data/traces_2_timepoints.xml"
        ),
        InvalidOutputException
    );
}


#ifndef PROJECT_BUILD_TYPE_DEBUG

// Tests which are compiled only in non-Debug mode.
// Including the tests in Debug mode leads to SIGSEGV errors due to the 
// internal implementation of the XercesC3.1 library

TEST(MSTMLSubfilesMerger, InvalidTracesStructure1) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_traces_structure1/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_traces_structure1/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidTracesStructure2) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_traces_structure2/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_traces_structure2/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

#endif


TEST(MSTMLSubfilesMerger, InvalidDifferentNumberOfTimepoints) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_different_number_of_timepoints/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_different_number_of_timepoints/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidDifferentTimepointsValues) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_different_timepoint_values/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_different_timepoint_values/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidIdenticNumericStateVariables) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_identic_numeric_state_variables/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_identic_numeric_state_variables/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, InvalidIdenticSpatialEntities) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_identic_spatial_entities/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/invalid_identic_spatial_entities/timepoints_values.csv"
    );

    EXPECT_THROW(
        mstmlSubfilesMerger.mergeMSTMLSubfiles(),
        InvalidInputException
    );
}

TEST(MSTMLSubfilesMerger, Valid) {
    // Create the MSTML subfiles merger
    MSTMLSubfilesMerger mstmlSubfilesMerger(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/valid/traces/",
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/valid/timepoints_values.csv"
    );

    // Merge MSTML subfiles
    mstmlSubfilesMerger.mergeMSTMLSubfiles();

    // Get a reference to the merged spatial temporal trace
    SpatialTemporalTrace obtainedTrace = mstmlSubfilesMerger.getResultingMergedTrace();

    // Read expected merged MSTML file
    SpatialTemporalDataReader mstmlReader(
        "/home/ovidiu/Repositories/git/multiscale/Multiscale/data/test/verification/spatial-temporal/sample/mstml_merger/valid/expected_trace/"
    );

    // Obtain the expected spatial temporal trace
    SpatialTemporalTrace expectedTrace = mstmlReader.getNextSpatialTemporalTrace();

    // Check if the obtained and expected trace match
    EXPECT_TRUE(obtainedTrace == expectedTrace);
}


///////////////////////////////////////////////////////////////////////////////
//
// Main method
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
