#!/bin/bash

###########################################################
#
#
# A script for merging multiple time points into a single
# spatial temporal trace.
#
# Each time point is represented by a different xml file.
# The order of merging time points is the natural order
# of the xml files.
#
#
###########################################################

# Check if the required number of parameters was provided
if [ $# -ne 4 ];
then
    echo "Please run the script with the reguired parameters: MergeSpatialTemporalTimePoints.sh <input-folder> <xml-lines-before-time-point-content> <xml-lines-after-time-point-content> <output-path>.";
    
    exit 1;
fi

# Check if the first parameter points to a folder
if [ ! -d $1 ];
then
    echo "The input folder path is invalid. Please change.";

    exit 1;
fi

# Check if the second and third parameters are non-negative integers
numericPattern='^(0|-?[1-9]([0-9]+)?)$';

if ! [[ $2 =~ ${numericPattern} ]] || ! [[ $3 =~ ${numericPattern} ]];
then
    echo "The number of lines before/after time point content should be numeric values.";

    exit 1;
fi

# Inform user of the next action
echo "Merging the input files...";

# Start the timer for measuring the total execution time
startTime=$(date +%s.%N);

# Store input parameters in variables
inputFolder=$1;
linesBeforeTimePointContent=$2;
linesAfterTimePointContent=$3;
outputPath=$4;

# Create the resulting file
fileCount=`find ${inputFolder} -name "*.xml" | wc -l`;

if [[ ${fileCount} -gt 0 ]];
then
    sampleFilePath=`find ${inputFolder} -name "*.xml" | head -n1`;

    # Print the header to the resulting file
    cat ${sampleFilePath} | head -n ${linesBeforeTimePointContent} > ${outputPath};

    # Process each input file
    for file in `find ${inputFolder} -name "*.xml" | sort -V`;
    do
        cat ${file} | head -n -${linesAfterTimePointContent} | tail -n +$((${linesBeforeTimePointContent} + 1)) >> ${outputPath};
    done 

    # Print the footer to the resulting file
    cat ${sampleFilePath} | tail -n ${linesAfterTimePointContent} >> ${outputPath};
fi

# End the timer for measuring the total execution time
endTime=$(date +%s.%N);

# Print the total execution time
echo
echo "Total execution time: " $(echo "${endTime} - ${startTime}" | bc) " seconds.";
