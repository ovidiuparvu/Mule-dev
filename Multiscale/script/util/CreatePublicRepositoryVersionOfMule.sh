#!/bin/bash

###############################################################################
#
# This script should be run from the root folder of the git repository. In case 
# of the multiscale model checking project this is the folder entitled 
# "multiscale".
#
###############################################################################

# Ensure that the output folder is provided as an input parameter
if [[ $# -ne 1 ]];
then
    echo "Usage: $0 <output-folder>.";

    exit 1;
fi

# Ensure that the provided output folder exists
if [[ ! -d $1 ]];
then
    echo "The provided output folder is not valid. Please change accordingly.";

    exit 1;
fi

# Define variables
GIT_REPOSITORY_ARCHIVE_NAME="tmp.zip";
TMP_FILE="";

# Create an archive of the latest version of the git repository files and store 
# it in the provided output folder with the name tmp.zip
git archive -o $1/${GIT_REPOSITORY_ARCHIVE_NAME} HEAD;

# Extract the contents of the archive and then remove it
cd $1 && unzip ${GIT_REPOSITORY_ARCHIVE_NAME} && rm ${GIT_REPOSITORY_ARCHIVE_NAME};

# Remove unrequired files and folders
rm README.md.in;
rm -rf Multiscale/.settings;
rm Multiscale/.project Multiscale/.pydevproject Multiscale/.cproject;
rm Multiscale/CodingStyle.txt
rm -rf Multiscale/bin/*;
rm -rf Multiscale/build/Debug/;
rm -rf Multiscale/build/Release/;
rm -rf Multiscale/data/test/verification/spatial-temporal/sample/pattern_analysis/;
rm Multiscale/modules/verification/spatial-temporal/sample/PatternAnalysis*;
rm Multiscale/script/analysis/*.*;
rm -rf Multiscale/script/analysis/case_study_specific/chemotaxis/;
rm -rf Multiscale/script/analysis/case_study_specific/dictyostelium/;
rm -rf Multiscale/script/analysis/util;
rm -rf Multiscale/script/buildbot/
rm -rf Multiscale/script/docker/
rm -rf Multiscale/script/util
rm -rf Multiscale/script/verification/sample/
rm -rf Multiscale/script/verification/util/
rm Multiscale/script/verification/MergeAttributeTestFiles.sh
rm -rf Multiscale/script/video/

# Remove the update project modified date commands from the main CMakeLists.txt file
projectModifiedDateLineNumber=$(cat Multiscale/CMakeLists.txt | grep -n "# Project modified date" | head -n1 | grep -o "^[0-9]\+") && TMP_FILE=$(mktemp) && sed -e "$((${projectModifiedDateLineNumber} - 1)),$((${projectModifiedDateLineNumber} + 8))d" Multiscale/CMakeLists.txt > ${TMP_FILE} && mv ${TMP_FILE} Multiscale/CMakeLists.txt;

# Remove the pattern analysis targets from the corresponding CMakeLists.txt file
patternAnalysisLineNumber=$(cat Multiscale/modules/verification/spatial-temporal/CMakeLists.txt | grep -n "# PatternAnalysisInteractiveSample" | head -n1 | grep -o "^[0-9]\+") && TMP_FILE=$(mktemp) && sed -e "${patternAnalysisLineNumber},$((${patternAnalysisLineNumber} + 32))d" Multiscale/modules/verification/spatial-temporal/CMakeLists.txt > ${TMP_FILE} && mv ${TMP_FILE} Multiscale/modules/verification/spatial-temporal/CMakeLists.txt;

# Create the "Debug" and "Release" build folders
mkdir -p Multiscale/build/Debug;
mkdir -p Multiscale/build/Release;
