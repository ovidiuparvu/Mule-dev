#!/bin/bash

# Check if two command line parameters were provided as input
if [ $# -ne 2 ];
then
    echo "Usage: $0 <input-folder> <output-file>.";

    exit 1;
fi

# Check if the input folder is valid
if [ ! -d $1 ];
then
    echo "The provided input folder path is invalid. Please change.";

    exit 1;
fi

# Initialise variables
nrOfProcessedFiles=0;

averageModelSimulationExecutionTime=0;
averageSimulationOutputConversionExecutionTime=0;
averageMSTMLGenerationExecutionTime=0;
averageMSTMLSubfilesMergingExecutionTime=0;

modelSimulationExecutionTimeSum=0;
simulationOutputConversionExecutionTimeSum=0;
mstmlGenerationExecutionTimeSum=0;
mstmlSubfilesMergingExecutionTimeSum=0;

# Compute average execution times
for file in $(find $1 -name "*.out");
do
    executionTimesInFile=($(cat ${file} | egrep -o "[0-9]*\.[0-9]+"));

    modelSimulationExecutionTimeSum=$(bc -l <<< "${modelSimulationExecutionTimeSum} + ${executionTimesInFile[0]}");
    simulationOutputConversionExecutionTimeSum=$(bc -l <<< "${simulationOutputConversionExecutionTimeSum} + ${executionTimesInFile[1]}");
    mstmlGenerationExecutionTimeSum=$(bc -l <<< "${mstmlGenerationExecutionTimeSum} + ${executionTimesInFile[2]}");
    mstmlSubfilesMergingExecutionTimeSum=$(bc -l <<< "${mstmlSubfilesMergingExecutionTimeSum} + ${executionTimesInFile[3]}");

    nrOfProcessedFiles=$((nrOfProcessedFiles + 1));
done

# Compute average execution times
averageModelSimulationExecutionTime=$(bc -l <<< "${modelSimulationExecutionTimeSum} / ${nrOfProcessedFiles}");
averageSimulationOutputConversionExecutionTime=$(bc -l <<< "${simulationOutputConversionExecutionTimeSum} / ${nrOfProcessedFiles}");
averageMSTMLGenerationExecutionTime=$(bc -l <<< "${mstmlGenerationExecutionTimeSum} / ${nrOfProcessedFiles}");
averageMSTMLSubfilesMergingExecutionTime=$(bc -l <<< "${mstmlSubfilesMergingExecutionTimeSum} / ${nrOfProcessedFiles}");

# Print average execution times to the indicated output file
echo "Model simulation execution time: ${averageModelSimulationExecutionTime} seconds." > $2;
echo "Simulation output conversion to csv format execution time: ${averageSimulationOutputConversionExecutionTime} seconds." >> $2;
echo "MSTML subfiles generation execution time: ${averageMSTMLGenerationExecutionTime} seconds." >> $2;
echo "MSTML subfiles merging execution time: ${averageMSTMLSubfilesMergingExecutionTime} seconds." >> $2;
