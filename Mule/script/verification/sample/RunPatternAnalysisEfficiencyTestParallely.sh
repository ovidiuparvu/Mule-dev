#!/bin/bash

# Check if the provided number of arguments equals 2
if [[ $# -ne 2 ]];
then
    echo "Usage: $0 <pattern-analysis-executable-path> <timeseries-folder-path>.";

    exit 1;
fi

# Check if the pattern analysis executable path points to a regular file
if [[ ! -f $1 ]];
then
    echo "The pattern analysis executable path does not point to a regular file. Please change.";

    exit 1;
fi

# Check if the timeseries folder path points to a directory
if [[ ! -d $2 ]];
then
    echo "The timeseries file path does not point to a directory. Please change.";

    exit 1;
fi


###############################################################################
#
# Run the pattern analysis executable in parallel considering the provided 
# timeseries folder and record the total execution time
#
###############################################################################

# Inform the user about the next action
echo "Running pattern analysis procedure for timeseries in the input folder $2...";

# Start the timer for measuring the total execution time
startTime=$(date +%s.%N);

# Run the pattern analysis executable for the provided timeseries
find $2 -name "*.csv" | parallel RunPatternAnalysisEfficiencyTestForTimeseries.sh $1 {};

# End the timer for measuring the total execution time
endTime=$(date +%s.%N);

# Print the total execution time
echo
echo "Overall execution time: $(echo "${endTime} - ${startTime}" | bc) seconds.";
echo 
