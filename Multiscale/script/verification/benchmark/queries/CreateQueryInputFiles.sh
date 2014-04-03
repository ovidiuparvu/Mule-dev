#!/bin/bash

# Check if the number of input parameters is correct
if [[ $# -ne 2 ]];
then
    echo "Usage: CreateQueryInputFiles.sh <query-input-file-with-one-timepoint> <nr-generated-input-files>.";

    exit 1;
fi

# Check if a valid input query file was provided
if [[ ! -f $1 ]];
then
    echo "Please run the script with a valid query input file.";

    exit 1;
fi

# Check if a valid number of generated input files was provided
if [[ $2 -lt 0 ]];
then
    echo "Please run the script with a non-negative number of generated input files.";

    exit 1;
fi

# Remove the extension from the input file
filepathWithoutExtension=${1%.*}

# Generate input files
for i in `seq 0 1 $2`;
do
    nrOfTimePoints=$((2 ** i));
    
    sed "s/\[0, 1\]/[0, ${nrOfTimePoints}]/g" $1 > ${filepathWithoutExtension}_${nrOfTimePoints}.in;
done
