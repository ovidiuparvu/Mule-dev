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
#   2. The number of concentrations for position
#   3. The number of concentric circles (D1)
#   4. The number of sectors (D2)
if [ $# -ne 4 ]; 
then
    echo "You have to provide the path to the .csv file, the number of concentrations for each position, the number of concentric circles and the number of sectors as parameters.";

    exit 1;
fi

# Get the parameters in separate variables
csvFile=$1;
nrOfConcentrationsForPosition=$2;
nrOfConcentricCircles=$3;
nrOfSectors=$4;

# Get the basename of the file, the filename and the extension
csvFileBasename=`basename ${csvFile}`;
csvFilename=${csvFileBasename%.*};
csvExtension=$([[ "$csvFileBaseName" = *.* ]] && echo ".${csvFileBasename##*.}" || echo '');

# Create a folder name for this execution according to time
folderName=`date +"%F-%T"`;

# Create all the required folders for this execution
mkdir ${INPUT_FOLDER}/${folderName}
mkdir ${SCRIPT_FOLDER}/${folderName}
mkdir ${MOVIE_FOLDER}/${folderName}
mkdir ${IMG_FOLDER}/${folderName}

# Copy the part of the csv file with necessary information to its corresponding input folder
sed 's/[;,:\t ]/,/g' <${csvFile} | cut -d "," -f 2- | tail -n +2 > ${INPUT_FOLDER}/${folderName}/${csvFileBasename}

# Run the program for converting the ".csv" file to N*M input files
# for the MapCartesianToPolar program
bin/MapCsvToInputFiles --input-file "${INPUT_FOLDER}/${folderName}/${csvFileBasename}" --nr-concentrations-position ${nrOfConcentrationsForPosition} --nr-concentric-circles $nrOfConcentricCircles --nr-sectors $nrOfSectors --output-file "${INPUT_FOLDER}/${folderName}/${csvFilename}"

# TODO: Continue




# avconv -r ${MOVIE_FRAME_RATE} -f image2 -i mapcart2pol_%d.png ../movie/output.avi
