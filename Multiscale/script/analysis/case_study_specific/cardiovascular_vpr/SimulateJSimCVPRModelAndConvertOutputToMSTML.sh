#!/bin/bash

###############################################################################
# 
# Script for simulating the Cardiovascular Virtual Physiological Rat JSim model
# and converting the simulation output to MSTML. (TODO: Update)
#
# Author: Ovidiu Parvu
# Contact: ovidiu.parvu@gmail.com
#
# Copyright Ovidiu Parvu 2014
#
###############################################################################


###############################################################################
#
# Constants definitions 
#
###############################################################################

# Naming constants (TODO: Update)
CASE_STUDY_TITLE="cardiovascular_vpr";

# Execution constants
NR_MODEL_SIMULATIONS=1;
COMMAND_EXECUTION_TIMELIMIT=360;

# I/O constants (TODO: Update)
MODEL_INPUT_FILE="model/BaroCV_Merged_Valsalva.proj";
MODEL_SIMULATION_OUTPUT_FILE="cardiovascular_vpr_simulation_results.csv";

OUT_SIMULATION_FOLDER="simulations";
OUT_SIMULATION_LOG_FOLDER="${OUT_SIMULATION_FOLDER}/log";
OUT_SIMULATION_PROCESSED_FOLDER="${OUT_SIMULATION_FOLDER}/processed";
OUT_SIMULATION_RAW_FOLDER="${OUT_SIMULATION_FOLDER}/raw";

OUT_EXECUTION_TIME_FOLDER="log/execution_time";

OUT_MSTML_FOLDER="mstml";
OUT_MSTML_SUBFILES_TMP_FOLDER="${OUT_MSTML_FOLDER}/tmp";

# MSTML constants
LINES_BEFORE_TIMEPOINT_CONTENT=3;
LINES_AFTER_TIMEPOINT_CONTENT=1;


###############################################################################
#
# Simulation output analysis specification
#
# This specification is used to determine which columns from the processed 
# simulation output file should be (analysed and) included in the resulting 
# MSTML file.
#
# The specification format depends on the considered state variable type as 
# follows:
#
#   + Numeric:  Numeric <column> <semantic-type>, where
#       <column>                    represents the starting column from the 
#                                   processed simulation output file
#       <semantic-type>             represents the semantic type of the numeric 
#                                   state variable     
#
#   + Cluster:  Cluster <start-column> <stop-column> <simulation-grid-height> 
#               <simulation-grid-width> <nr-of-entities> <semantic-type>,
#               where:
#       <start-column>              represents the starting column from the 
#                                   processed simulation output file
#       <stop-column>               represents the stopping/ending column from 
#                                   the processed simulation output file 
#       <simulation-grid-height>    represents the number of rows in the 
#                                   discretised space
#       <simulation-grid-width>     represents the number of columns in the 
#                                   discretised space 
#       <nr-of-entities>            represents the number of entities for which
#                                   the position in the discretised space is
#                                   recorded
#       <max-pileup>                represents the maximum number of entities
#                                   which can occupy a position in the
#                                   discretised space
#       <semantic-type>             represents the semantic type of the spatial
#                                   state variable
#
#   + Region:   Region <start-column> <stop-column> <simulation-grid-height> 
#               <simulation-grid-width> <nr-of-concentrations> <semantic-type>, 
#               where:
#       <start-column>              represents the starting column from the 
#                                   processed simulation output file
#       <stop-column>               represents the stopping/ending column from 
#                                   the processed simulation output file 
#       <simulation-grid-height>    represents the number of rows in the 
#                                   discretised space
#       <simulation-grid-width>     represents the number of columns in the 
#                                   discretised space 
#       <nr-of-concentrations>      represents the number of concentrations 
#                                   recorded for each position in the 
#                                   discretised space
#       <semantic-type>             represents the semantic type of the spatial
#                                   state variable
#
# TODO: Update MSTML generation specification relative to the considered case study
#
###############################################################################

MSTML_GENERATION_SPECIFICATION="
Numeric 2 OrganSystem.Cardiovascular
Numeric 3 Cellular.Baroreflex
Numeric 4 OrganSystem.Cardiovascular
Numeric 5 OrganSystem.Cardiovascular
Numeric 6 OrganSystem.Cardiovascular
Numeric 7 OrganSystem.Cardiovascular
Numeric 8 OrganSystem.Cardiovascular
Numeric 9 OrganSystem.Cardiovascular
";


###############################################################################
#
# Functions definitions
#
###############################################################################

# Execute a model simulation
#
# Function parameters:
#    $1 - Raw simulation output path
#    $2 - Simulation log output path
#    $3 - Execution time log file path
#
# TODO: Update case study-specific instructions accordingly
function SimulateModel() {
    # Inform user where the simulation output is stored
    echo "Simulating ${MODEL_INPUT_FILE} and storing simulation output in $1...";

    # Record execution start time
    local startTime=$(date +%s.%N);
    
    # Run a simulation of the model
    timelimit -T ${COMMAND_EXECUTION_TIMELIMIT} ${JSIMHOME}/linux/bin/jsbatch -f ${MODEL_INPUT_FILE} -ofmt csv -out $1 1>$2 2>&1;
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "Model simulation execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> $3;
}

# Convert the simulation output to csv
#
# Function parameters:
#    $1 - Raw simulation output path
#    $2 - Processed simulation output path
#    $3 - Execution time log file path
#
# TODO: Update case study-specific instructions accordingly
function ConvertModelSimulationOutputToCsv() {
    # Inform the user where the converted simulation output is stored
    echo "Converting the simulation output from raw ($1) to csv format ($2)...";

    # Record execution start time
    local startTime=$(date +%s.%N);
    
    # Convert the simulation output to csv format
    timelimit -T ${COMMAND_EXECUTION_TIMELIMIT} cat $1 | cut -d"," -f1,109,112,119,121,122,123,125,126 | awk --field-separator="," '/^[0-9.,]+/ { time=($1 * 1000); sub("[0-9E.]+", "", $0); print time $0; } /^time/ { print $0; }' > $2;
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "Simulation output conversion to csv format execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> $3;
}


# Generate a temporary MSTML subfile corresponding to a numeric state variable
#
# Function parameters:
#   $1 - The temporary MSTML subfiles folder
#   $2 - Processed simulation output file path
#   $3 - Index of column recording values of numeric state variable
#   $4 - The semantic type of the numeric state variable
function GenerateNumericTemporaryMSTMLSubfile() {
    # Initialisation
    numericStateVariableName=$(cat $2 | head -n1 | cut -d"," -f $3);
    numericStateVariableValues=$(cat $2 | tail -n+2 | cut -d"," -f $3);
    outputFilepath="$1/Numeric_$4_${numericStateVariableName}.xml";

    # Add header information to the MSTML subfile
    echo "<?xml version=\"1.0\" encoding=\"utf-8\"?>" > ${outputFilepath};
    echo "" >> ${outputFilepath};
    echo "<experiment>" >> ${outputFilepath};

    # Add the contents to the MSTML subfile
    echo "${numericStateVariableValues}" | while read numericStateVariableValue;
    do
        echo -e "\t<timepoint>" >> ${outputFilepath};
        echo -e "\t\t<numericStateVariable semanticType=\"$4\">" >> ${outputFilepath};
        echo -e "\t\t\t<name>${numericStateVariableName}</name>" >> ${outputFilepath};
        echo -e "\t\t\t<value>${numericStateVariableValue}</value>" >> ${outputFilepath};
        echo -e "\t\t</numericStateVariable>" >> ${outputFilepath};
        echo -e "\t</timepoint>" >> ${outputFilepath};
    done;
    
    # Add footer information to the MSTML subfile
    echo "</experiment>" >> ${outputFilepath};
}

# Export function
export -f GenerateNumericTemporaryMSTMLSubfile 


# Generate a temporary MSTML subfile corresponding to a cluster
#
# Function parameters
#   $1 - The temporary MSTML subfiles folder
#   $2 - Processed simulation output file path
#   $3 - Index of the start column recording values corresponding to potential clusters
#   $4 - Index of the stop column recording values corresponding to potential clusters
#   $5 - The height (number of rows) of the discretised spatial domain
#   $6 - The width (number of columns) of the discretised spatial domain
#   $7 - The number of entities which are tracked by their position in the discretised spatial domain
#   $8 - The maximum number of entities which can pile up on top of each other
#   $9 - The semantic type of the cluster state variable
function GenerateClusterTemporaryMSTMLSubfile() {
    # Initialisation
    local simulationGridHeight=$5;
    local simulationGridWidth=$6;
    local nrOfEntities=$7;
    local maxPileup=$8;
    local semanticType=$9;

    local stmlOutputPath="$1/Cluster_${semanticType}";

    local HOME_FOLDER=$(pwd);

    local INPUT_FILENAME=${2##*/};
    local INPUT_BASENAME=${INPUT_FILENAME%.*};

    local OUT_FOLDER="${HOME_FOLDER}/results/${INPUT_BASENAME}/cluster";

    local OUT_ANALYSIS_FOLDER="${OUT_FOLDER}/analysis";

    local OUT_VISUALISATION_FOLDER="${OUT_FOLDER}/visualisation";
    local OUT_INPUT_FOLDER="${OUT_VISUALISATION_FOLDER}/input";
    local OUT_SCRIPT_FOLDER="${OUT_VISUALISATION_FOLDER}/script";
    local OUT_IMG_FOLDER="${OUT_VISUALISATION_FOLDER}/img";

    # Create the output folders
    mkdir -p ${OUT_FOLDER};

    mkdir -p ${OUT_ANALYSIS_FOLDER};
    mkdir -p ${OUT_VISUALISATION_FOLDER};
    mkdir -p ${OUT_INPUT_FOLDER};
    mkdir -p ${OUT_SCRIPT_FOLDER};
    mkdir -p ${OUT_IMG_FOLDER};

    # Create a temporary file for storing the values corresponding to potential clusters
    local simulationInputFile=$(mktemp);

    # Add the values to the temporary file
    cat $2 | tail -n+2 | cut -d"," -f$3-$4 > ${simulationInputFile};


    ####################################################################################
    # Step 1: Generate images for simulation file
    ####################################################################################

    # Copy the part of the csv file with necessary information to its corresponding input folder
    sed 's/^[;,:\t ]\+//g' <${simulationInputFile} | sed 's/[;,:\t ]\+/,/g' | tail -n+2 > ${OUT_INPUT_FOLDER}/${INPUT_BASENAME};

    # Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
    bin/RectangularMapEntityCsvToInputFiles --input-file "${OUT_INPUT_FOLDER}/${INPUT_BASENAME}" --nr-entities ${nrOfEntities} --max-pileup ${maxPileup} --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${OUT_INPUT_FOLDER}/${INPUT_BASENAME}";

    # Run the MapCartesianToScript for converting each of the generated input files into gnuplot scripts
    find ${OUT_INPUT_FOLDER} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${OUT_SCRIPT_FOLDER}/{/.};

    # Run gnuplot on each of the generated scripts from the script folder and ignore warnings
    cd ${OUT_IMG_FOLDER};

    ls -1 ${OUT_SCRIPT_FOLDER} | parallel gnuplot ${OUT_SCRIPT_FOLDER}/{} 2>/dev/null;

    cd ${HOME_FOLDER};


    ####################################################################################
    # Step 2: Analyse images of entities
    ####################################################################################

    # Define the results output files
    local clustersOutputFile=${OUT_ANALYSIS_FOLDER}/"results_clusters";
    local nrOfClustersOutputFile=${OUT_ANALYSIS_FOLDER}/"results_nr_clusters";
    local clustersClusterednessOutputFile=${OUT_ANALYSIS_FOLDER}/"results_clusteredness";
    local clustersPileupOutputFile=${OUT_ANALYSIS_FOLDER}/"results_pileup";

    # Define the basename of the images without numeric index at the end
    local imageName=$(find ${OUT_IMG_FOLDER} -name "*.png" | head -n1);
    local imageBasename=$(basename ${imageName});
    local imageBasenameRoot=$(echo ${imageBasename} | rev | cut -d'_' -f2- | rev);

    # Run the cluster detection procedure for each image in parallel
    ls ${OUT_IMG_FOLDER}/*.png | parallel ./bin/SimulationDetectClusters --input-file={} --output-file=${OUT_ANALYSIS_FOLDER}/{/.} --height=${simulationGridHeight} --width=${simulationGridWidth} --max-pileup=${maxPileup} --debug-mode="false"

    # Empty files which will store final results
    echo "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${clustersOutputFile};
    echo "Number of regions" > ${nrOfClustersOutputFile};
    echo "Clusteredness" > ${clustersClusterednessOutputFile};
    echo "Pile up" > ${clustersPileupOutputFile};

    # Write the clusters, number of clusters, overall clusteredness and overall pileup in separate files
    for output in $(ls -1v ${OUT_ANALYSIS_FOLDER}/*.out);
    do
        cat ${output} | head -n-3 | tail -n+2 >> ${clustersOutputFile};
        cat ${output} | head -n-3 | tail -n+2 | wc -l >> ${nrOfClustersOutputFile}

        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${clustersClusterednessOutputFile};

        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${clustersPileupOutputFile};
    done

    # Define the variables required to merge the xml files
    local clustersXMLOutputPath=${OUT_ANALYSIS_FOLDER}/"results_clusters.xml";

    # Create the resulting file
    local fileCount=$(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | wc -l);

    if [[ ${fileCount} -gt 0 ]];
    then
        local sampleFilePath=$(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | head -n1);

        # Print the header to the resulting file
        cat ${sampleFilePath} | head -n ${LINES_BEFORE_TIMEPOINT_CONTENT} > ${clustersXMLOutputPath};

        # Process each input file
        for file in $(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | sort -V);
        do
            cat ${file} | head -n -${LINES_AFTER_TIMEPOINT_CONTENT} | tail -n +$((${LINES_BEFORE_TIMEPOINT_CONTENT} + 1)) | sed "s/\(spatialType=\"cluster\"\)/\0 semanticType=\"${semanticType}\"/g" >> ${clustersXMLOutputPath};
        done 

        # Print the footer to the resulting file
        cat ${sampleFilePath} | tail -n ${LINES_AFTER_TIMEPOINT_CONTENT} >> ${clustersXMLOutputPath};
    fi

    # Copy the resulting file where indicated
    cp ${clustersXMLOutputPath} ${stmlOutputPath}; 
}


# Generate a temporary MSTML subfile corresponding to a region
#
# Function parameters
#   $1 - The temporary MSTML subfiles folder
#   $2 - Processed simulation output file path
#   $3 - Index of the start column recording values corresponding to potential regions
#   $4 - Index of the stop column recording values corresponding to potential regions
#   $5 - The height (number of rows) of the discretised spatial domain
#   $6 - The width (number of columns) of the discretised spatial domain
#   $7 - The number of concentrations recorded for each position in the discretised spatial domain
#   $8 - The semantic type of the region state variable
function GenerateRegionTemporaryMSTMLSubfile() {
    # Initialisation
    local simulationGridHeight=$5;
    local simulationGridWidth=$6;
    local nrOfConcentrationsForEachPosition=$7;
    local semanticType=$8;

    local stmlOutputPath="$1/Region_${semanticType}";

    local HOME_FOLDER=$(pwd);

    local INPUT_FILENAME=${2##*/};
    local INPUT_BASENAME=${INPUT_FILENAME%.*};

    local OUT_FOLDER="${HOME_FOLDER}/results/${INPUT_BASENAME}/region";

    local OUT_ANALYSIS_FOLDER="${OUT_FOLDER}/analysis";

    local OUT_VISUALISATION_FOLDER="${OUT_FOLDER}/visualisation";
    local OUT_INPUT_FOLDER="${OUT_VISUALISATION_FOLDER}/input";
    local OUT_SCRIPT_FOLDER="${OUT_VISUALISATION_FOLDER}/script";
    local OUT_IMG_FOLDER="${OUT_VISUALISATION_FOLDER}/img";

    # Create the output folders
    mkdir -p ${OUT_FOLDER};

    mkdir -p ${OUT_ANALYSIS_FOLDER};

    mkdir -p ${OUT_VISUALISATION_FOLDER};
    mkdir -p ${OUT_INPUT_FOLDER};
    mkdir -p ${OUT_SCRIPT_FOLDER};
    mkdir -p ${OUT_IMG_FOLDER};

    # Create a temporary file for storing the values corresponding to potential regions
    local simulationInputFile=$(mktemp);

    # Add the values to the temporary file
    cat $2 | tail -n+2 | cut -d"," -f$3-$4 > ${simulationInputFile};


    ####################################################################################
    # Step 1: Generate images for simulation file
    ####################################################################################

    # Copy the part of the csv file with necessary information to its corresponding input folder
    sed 's/^[;,:\t ]\+//g' <${simulationInputFile} | sed 's/[;,:\t ]\+/,/g' | tail -n+2 > ${OUT_INPUT_FOLDER}/${INPUT_BASENAME};

    # Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
    bin/RectangularMapCsvToInputFiles --input-file "${OUT_INPUT_FOLDER}/${INPUT_BASENAME}" --nr-concentrations-position ${nrOfConcentrationsForEachPosition} --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${OUT_INPUT_FOLDER}/${INPUT_BASENAME}";

    # Run the MapCartesianToScript for converting each of the generated input files into gnuplot scripts
    find ${OUT_INPUT_FOLDER} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${OUT_SCRIPT_FOLDER}/{/.};

    # Run gnuplot on each of the generated scripts from the script folder and ignore warnings
    cd ${OUT_IMG_FOLDER};

    ls -1 ${OUT_SCRIPT_FOLDER} | parallel gnuplot ${OUT_SCRIPT_FOLDER}/{} 2>/dev/null;

    cd ${HOME_FOLDER};


    ####################################################################################
    # Step 2: Analyse images of regions
    ####################################################################################

    # Define the results output files
    local regionsOutputFile=${OUT_ANALYSIS_FOLDER}/"results_regions";
    local nrOfRegionsOutputFile=${OUT_ANALYSIS_FOLDER}/"results_nr_regions";
    local regionsClusterednessOutputFile=${OUT_ANALYSIS_FOLDER}/"results_clusteredness";
    local regionsPileupOutputFile=${OUT_ANALYSIS_FOLDER}/"results_pileup";

    # Define the basename of the images without numeric index at the end
    local imageName=$(find ${OUT_IMG_FOLDER} -name "*.png" | head -n1);
    local imageBasename=$(basename ${imageName});
    local imageBasenameRoot=$(echo ${imageBasename} | rev | cut -d'_' -f2- | rev);

    # Run the region detection procedure for each image in parallel
    ls ${OUT_IMG_FOLDER}/*.png | parallel ./bin/RectangularDetectRegions --input-file={} --output-file=${OUT_ANALYSIS_FOLDER}/{/.} --debug-mode="false"

    # Empty files which will store final results
    echo "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${regionsOutputFile};
    echo "Number of regions" > ${nrOfRegionsOutputFile};
    echo "Clusteredness" > ${regionsClusterednessOutputFile};
    echo "Pile up" > ${regionsPileupOutputFile};

    # Write the regions, number of regions, overall clusteredness and overall pileup in separate files
    for output in $(ls -1v ${OUT_ANALYSIS_FOLDER}/*.out);
    do
        cat ${output} | head -n-3 | tail -n+2 >> ${regionsOutputFile};
        cat ${output} | head -n-3 | tail -n+2 | wc -l >> ${nrOfRegionsOutputFile}

        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${regionsClusterednessOutputFile};

        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${regionsPileupOutputFile};
    done

    # Define the variables required to merge the xml files
    local regionsXMLOutputPath=${OUT_ANALYSIS_FOLDER}/"results_regions.xml";

    # Create the resulting file
    local fileCount=$(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | wc -l);

    if [[ ${fileCount} -gt 0 ]];
    then
        local sampleFilePath=$(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | head -n1);

        # Print the header to the resulting file
        cat ${sampleFilePath} | head -n ${LINES_BEFORE_TIMEPOINT_CONTENT} > ${regionsXMLOutputPath};

        # Process each input file
        for file in $(find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | sort -V);
        do
            cat ${file} | head -n -${LINES_AFTER_TIMEPOINT_CONTENT} | tail -n +$((${LINES_BEFORE_TIMEPOINT_CONTENT} + 1)) | sed "s/\(spatialType=\"region\"\)/\0 semanticType=\"${semanticType}\"/g" >> ${regionsXMLOutputPath};
        done 

        # Print the footer to the resulting file
        cat ${sampleFilePath} | tail -n ${LINES_AFTER_TIMEPOINT_CONTENT} >> ${regionsXMLOutputPath};
    fi

    # Copy the resulting file where indicated
    cp ${regionsXMLOutputPath} ${stmlOutputPath}; 
}


# Generate temporary MSTML subfiles from the csv formatted simulation output 
# according to the MSTML_GENERATION_SPECIFICATION
#
# Function parameters:
#    $1 - Processed simulation output path
#    $2 - Execution time log file path
function GenerateTemporaryMSTMLSubfiles() {
    # Inform the user where the temporary MSTML subfiles are stored
    echo "Processing (including spatio-temporal analysis) the csv file ($1) and storing the resulting temporary MSTML subfiles in ${OUT_MSTML_SUBFILES_TMP_FOLDER}...";

    # Record execution start time
    local startTime=$(date +%s.%N);

    # Generate a MSTML subfile corresponding to each line in MSTML_GENERATION_SPECIFICATION starting with "Numeric"
    echo "${MSTML_GENERATION_SPECIFICATION}" | egrep "^Numeric" | parallel --colsep ' ' --timeout ${COMMAND_EXECUTION_TIMELIMIT} "GenerateNumericTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} $1 {2} {3}";

    # Generate a MSTML subfile corresponding to each line in MSTML_GENERATION_SPECIFICATION starting with "Cluster"/"Region"
    echo "${MSTML_GENERATION_SPECIFICATION}" | egrep -v "^Numeric" | while read mstmlSubfileSpecification;
    do
        local stateVariableType=$(echo ${mstmlSubfileSpecification} | cut -d" " -f1);
        
        if [[ ${stateVariableType} == "Cluster" ]];
        then
            # Initialise relevant local variables
            local startColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f2);
            local stopColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f3);
            local simulationGridHeight=$(echo ${mstmlSubfileSpecification} | cut -d" " -f4);
            local simulationGridWidth=$(echo ${mstmlSubfileSpecification} | cut -d" " -f5);
            local nrOfEntities=$(echo ${mstmlSubfileSpecification} | cut -d" " -f6);
            local maxPileup=$(echo ${mstmlSubfileSpecification} | cut -d" " -f7);
            local semanticType=$(echo ${mstmlSubfileSpecification} | cut -d" " -f8);
           
            # Generate the cluster temporary MSTML subfile 
            timelimit -T ${COMMAND_EXECUTION_TIMELIMIT} GenerateClusterTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} $1 ${startColumn} ${stopColumn} ${simulationGridHeight} ${simulationGridWidth} ${nrOfEntities} ${maxPileup} ${semanticType};
        elif [[ ${stateVariableType} == "Region" ]];
        then
            local startColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f2);
            local stopColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f3);
            local simulationGridHeight=$(echo ${mstmlSubfileSpecification} | cut -d" " -f4);
            local simulationGridWidth=$(echo ${mstmlSubfileSpecification} | cut -d" " -f5);
            local nrOfConcentrationsForEachPosition=$(echo ${mstmlSubfileSpecification} | cut -d" " -f6);
            local semanticType=$(echo ${mstmlSubfileSpecification} | cut -d" " -f7);
           
            # Generate the cluster temporary MSTML subfile 
            timelimit -T ${COMMAND_EXECUTION_TIMELIMIT} GenerateRegionTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} $1 ${startColumn} ${stopColumn} ${simulationGridHeight} ${simulationGridWidth} ${nrOfConcentrationsForEachPosition} ${semanticType};
        fi;
    done;
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "MSTML subfiles generation execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> $2;
}


# Merge temporary MSTML subfiles into a single MSTML file
#
# Function parameters:
#   $1 - Folder containing temporary MSTML subfiles
#   $2 - Processed simulation output path
#   $3 - MSTML output path
#   $4 - Execution time log file path
function MergeSTMLSubfiles() {
    # Inform the user where the resulting MSTML file is stored
    echo "Merging MSTML subfiles from the $1 folder into the resulting MSTML file $3...";

    # Record execution start time
    local startTime=$(date +%s.%N);

    # Initialisation
    local timepointsValuesFilePath=$(mktemp);

    ####################################################################################
    # Step 1: Store the timepoints values in a separate file
    ####################################################################################
     
    cat $2 | cut -d"," -f1 >> ${timepointsValuesFilePath};

    ####################################################################################
    # Step 2: Merge MSTML subfiles
    ####################################################################################

    bin/MSTMLSubfilesMergerSample --mstml-subfiles-folder $1 --timepoints-values-file ${timepointsValuesFilePath} --mstml-output-file $3

    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "MSTML subfiles merging execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> $4;
}


###############################################################################
#
# Initialisation
#
###############################################################################

# Check if the number of command-line arguments parameters is valid
if [ $# -ne 0 ];
then
    echo "An error occurred: Incorrect input arguments provided.";
    echo "";
    echo "Usage: $0.";
    
    exit 1;
fi

# Change the current directory to the directory where the script is located
cd "$( dirname "${BASH_SOURCE[0]}" )";

# Create output folders if they do not already exist
mkdir -p ${OUT_SIMULATION_FOLDER};
mkdir -p ${OUT_SIMULATION_LOG_FOLDER};
mkdir -p ${OUT_SIMULATION_PROCESSED_FOLDER};
mkdir -p ${OUT_SIMULATION_RAW_FOLDER};

mkdir -p ${OUT_EXECUTION_TIME_FOLDER};

mkdir -p ${OUT_MSTML_FOLDER};
mkdir -p ${OUT_MSTML_SUBFILES_TMP_FOLDER};


###############################################################################
# 
# Simulate model and generate MSTML files
#
###############################################################################

# Inform the user how many MSTML files will be generated
echo "Simulating model and generating the corresponding MSTML file ${NR_MODEL_SIMULATIONS} time(s)...";
echo "------------------------------------------------------------------------------";
echo "";

# Simulate model and generate MSTML files
for i in $(seq 1 1 ${NR_MODEL_SIMULATIONS});
do
    # Get the current date and time
    date=$(date +"%F-%T");

    # Initialise the simulation dependent variables
    fullModelSimulationName="${CASE_STUDY_TITLE}_${date}";
    simulationLogOutputPath="${OUT_SIMULATION_LOG_FOLDER}/${fullModelSimulationName}.out";
    processedSimulationOutputPath="${OUT_SIMULATION_PROCESSED_FOLDER}/${fullModelSimulationName}.csv";
    rawSimulationOutputPath="${OUT_SIMULATION_RAW_FOLDER}/${fullModelSimulationName}.csv";
    
    executionTimeLogOutputPath="${OUT_EXECUTION_TIME_FOLDER}/${fullModelSimulationName}.out";
    
    mstmlOutputPath="${OUT_MSTML_FOLDER}/${fullModelSimulationName}.xml";


    ##############################################################################
    # Step 1: Simulate the model
    ##############################################################################
    
    SimulateModel ${rawSimulationOutputPath} ${simulationLogOutputPath} ${executionTimeLogOutputPath}
    
    
    ##############################################################################
    # Step 2: Convert the simulation output to csv format
    ##############################################################################
     
    ConvertModelSimulationOutputToCsv ${rawSimulationOutputPath} ${processedSimulationOutputPath} ${executionTimeLogOutputPath}

    
    ##############################################################################
    # Step 3: Generate temporary MSTML subfile(s)
    ##############################################################################
    
    GenerateTemporaryMSTMLSubfiles ${processedSimulationOutputPath} ${executionTimeLogOutputPath}
    

    ##############################################################################
    # Step 4: Merge MSTML subfile(s) into a single subfile
    ##############################################################################
    
    MergeSTMLSubfiles ${OUT_MSTML_SUBFILES_TMP_FOLDER} ${processedSimulationOutputPath} ${mstmlOutputPath} ${executionTimeLogOutputPath}

    
    ##############################################################################
    # Step 5: Post-processing
    ##############################################################################
    
    # Separate model simulation output using a blank line
    echo;
done

# Inform the user that the MSTML files were generated successfully
echo "------------------------------------------------------------------------------";
echo "${NR_MODEL_SIMULATIONS} MSTML file(s) were generated successfully.";
echo "";


###############################################################################
#
# Termination
#
###############################################################################

# Remove temporary folder(s)
rm -rf ${OUT_MSTML_SUBFILES_TMP_FOLDER}
