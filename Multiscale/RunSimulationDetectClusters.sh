#!/bin/bash

if [ $# -eq 4 ];
then
    inputFolder=$1;
    outputFolder=$2;
    height=$3;
    width=$4;

    # Create the output folder
    mkdir -p ${outputFolder}

    # Start the timer for measuring the total execution time
    startTime=$(date +%s.%N);

    # Inform user of the next action
    echo "Running the cluster detection procedure for each image...";

    # Run the cluster detection procedure for each image in parallel
    ls ${inputFolder}/*.png | parallel ./bin/SimulationDetectClusters --input-file={} --output-file=${outputFolder}/{/.} --height=${height} --width=${width}
    
    # Print end message
    echo "The cluster detection procedure(s) ended successfully.";

    # End the timer for measuring the total execution time
    endTime=$(date +%s.%N);
    
    # Print the total execution time
    echo 
    echo "Total execution time: " $(echo "${endTime} - ${startTime}" | bc) " seconds.";
    
else
    echo "Please run the script with the parameters: <input_folder> <output_folder> <height_of_grid> <width_of_grid>.";
fi
