#!/bin/bash

# If any errors are encountered, then the script will exit
set -e;

# Defining the constants for the script
MOVIE_FRAME_RATE=3

OUT_FOLDER=out

INPUT_FOLDER=${OUT_FOLDER}/input
SCRIPT_FOLDER=${OUT_FOLDER}/script
MOVIE_FOLDER=${OUT_FOLDER}/movie
IMG_FOLDER=${OUT_FOLDER}/img

# If the required parameters are not provided, then exit
# REQUIRED PARAMETERS:
#   1. Path to the csv file
#   2. The number of concentric circles (D1)
#   3. The number of sectors (D2)
if [ $# -ne 3 ]; 
then
    echo "You have to provide the path to the .csv file, the number of concentric circles and the number of sectors as parameters.";

    exit 1;
fi

# Get the parameters in separate variables
csvFile=$1;
nrOfConcentricCircles=$2;
nrOfSectors=$3;

# Get the basename of the file, the filename and the extension
csvFileBasename=`basename ${csvFile}`;
csvFilename="${filename##*.}";
csvExtension=$([[ "$csvFileBaseName" = *.* ]] && echo ".${csvFileBasename##*.}" || echo '');

# TODO: Validate input

# Create a folder name for this execution according to time
folderName=`date +"%F-%T"`;

# Create all the required folders for this execution
mkdir ${INPUT_FOLDER}/${folderName}
mkdir ${SCRIPT_FOLDER}/${folderName}
mkdir ${MOVIE_FOLDER}/${folderName}
mkdir ${IMG_FOLDER}/${folderName}

# Copy the csv file to its corresponding input folder
cp ${csvFile} ${INPUT_FOLDER}/${folderName}/${csvFileBasename}

# Run the program for converting the ".csv" file to input files
# for the MapCartesianToPolar program
bin/CsvToInputConverter --input-file "../${INPUT_FOLDER}/${folderName}/${csvFileBasename}" --nr-concentric-circles $nrOfConcentricCircles --nr-sectors $nrOfSectors --output-file "../${INPUT_FOLDER}/${folderName}/${csvFilename}"

# TODO: Continue




avconv -r ${MOVIE_FRAME_RATE} -f image2 -i mapcart2pol_%d.png ../movie/output.avi
