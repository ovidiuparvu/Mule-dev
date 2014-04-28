#!/bin/bash

if [ $# -eq 2 ];
then
    inputFolder=$1;
    outputFolder=$2;

    # Create the output folders
    mkdir -p ${outputFolder}

    # Run the RunRectangularDetectRegionsWithoutMovie.sh script for each image folder
    for folder in `ls -1v ${inputFolder}`;
    do
	RunRectangularRegionDetectorWithoutMovie.sh ${inputFolder}/${folder} ${outputFolder}/${folder}
    done
else
    echo "Please run the script with the parameters: <input_folder> <output_folder>.";
fi
