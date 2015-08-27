#!/bin/bash

# Check if the provided number of arguments equals 2
if [[ $# -ne 2 ]];
then
    echo "Usage: $0 <pattern-analysis-executable-path> <time-series-file-path>.";

    exit 1;
fi

# Check if the pattern analysis executable path points to a regular file
if [[ ! -f $1 ]];
then
    echo "The pattern analysis executable path does not point to a regular file. Please change.";

    exit 1;
fi

# Check if the time series file path points to a regular file
if [[ ! -f $2 ]];
then
    echo "The time series file path does not point to a regular file. Please change.";

    exit 1;
fi


###############################################################################
#
# Run the pattern analysis executable considering the provided time series and 
# record execution time
#
###############################################################################

# Inform the user about the next action
echo "Running pattern analysis procedure for input file $2...";

# Start the timer for measuring the total execution time
startTime=$(date +%s.%N);

# Run the pattern analysis executable for the provided time series
$1 $2;

# End the timer for measuring the total execution time
endTime=$(date +%s.%N);

# Print the total execution time
echo "Total execution time: $(echo "${endTime} - ${startTime}" | bc) seconds.";
echo 
