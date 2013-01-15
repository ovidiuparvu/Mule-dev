#!/bin/bash

# If any errors are encountered, then the script will exit
set -e;

# Defining the constants for the script
MOVIE_FRAME_RATE=25;

OUT_FOLDER=out;

INPUT_FOLDER=${OUT_FOLDER}/input;
SCRIPT_FOLDER=${OUT_FOLDER}/script;
MOVIE_FOLDER=${OUT_FOLDER}/movie;
IMG_FOLDER=${OUT_FOLDER}/img;

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

# TODO: Validate the input

# Create a folder name for this execution according to time
currentDate=`date +"%F-%T"`;
folderName="${csvFilename}_${currentDate}";

# Inform user of the next action
echo "Creating the output directories...";

# Create all the required folders for this execution
mkdir ${INPUT_FOLDER}/${folderName}
mkdir ${SCRIPT_FOLDER}/${folderName}
mkdir ${MOVIE_FOLDER}/${folderName}
mkdir ${IMG_FOLDER}/${folderName}

# Copy the part of the csv file with necessary information to its corresponding input folder
sed 's/[;,:\t ]+/,/g' <${csvFile} | cut -d "," -f 2- | tail -n +2 > ${INPUT_FOLDER}/${folderName}/${csvFileBasename}

# Inform user of the next action
echo "Generating the input files from the .csv file...";

# Run the program for converting the ".csv" file to "Number of time points" input files
# for the MapCartesianToPolar program
bin/MapCsvToInputFiles --input-file "${INPUT_FOLDER}/${folderName}/${csvFileBasename}" --nr-concentrations-position ${nrOfConcentrationsForPosition} --nr-concentric-circles $nrOfConcentricCircles --nr-sectors $nrOfSectors --output-file "${INPUT_FOLDER}/${folderName}/${csvFilename}";

# Inform user of the next action
echo "Generating in parallel the gnuplot script for each of the input files...";

# Run the MapCartesianToPolar for converting each of the generated input files
# into gnuplot scripts
ls -1 ${INPUT_FOLDER}/${folderName}/*.in | parallel bin/MapCartesianToPolar --input-file {} --output-file ${SCRIPT_FOLDER}/${folderName}/{/.}

# Inform user of the next action
echo "Running in parallel gnuplot and taking as input each one of the generated scripts...";

# Run gnuplot on each of the generated scripts from the script folder
cd ${IMG_FOLDER}/${folderName};

ls -1 ../../../${SCRIPT_FOLDER}/${folderName} | parallel gnuplot ../../../${SCRIPT_FOLDER}/${folderName}/{};

cd ../../../;

# Inform user of the next action
echo "Generating the movie from the images...";

# Generate the movie
avconv -r ${MOVIE_FRAME_RATE} -f image2 -i ${IMG_FOLDER}/${folderName}/${csvFilename}_%d.png ${MOVIE_FOLDER}/${folderName}/${csvFilename}.avi

# Print end message
echo "The movie was generated successfully.";
