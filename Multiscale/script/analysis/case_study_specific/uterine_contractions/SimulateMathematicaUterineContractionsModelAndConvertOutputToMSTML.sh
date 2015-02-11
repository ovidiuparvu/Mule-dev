#!/bin/bash

###############################################################################
# 
# Script for simulating the uterine contractions of labour Mathematica model
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
CASE_STUDY_TITLE="uterine_contractions";

# Execution constants
NR_MODEL_SIMULATIONS=1;
COMMAND_EXECUTION_TIMELIMIT=360;

# I/O constants (TODO: Update)
MODEL_INPUT_FILE="model/UterineContractionsModel.m";
MODEL_SIMULATION_OUTPUT_FILE="uterine_contractions_simulation_results.csv";

OUT_SIMULATION_FOLDER="simulations";
OUT_SIMULATION_LOG_FOLDER="${OUT_SIMULATION_FOLDER}/log";
OUT_SIMULATION_PROCESSED_FOLDER="${OUT_SIMULATION_FOLDER}/processed";
OUT_SIMULATION_RAW_FOLDER="${OUT_SIMULATION_FOLDER}/raw";

OUT_EXECUTION_TIME_FOLDER="log/execution_time";

OUT_MSTML_FOLDER="mstml";
OUT_MSTML_SUBFILES_TMP_FOLDER="${OUT_MSTML_FOLDER}/tmp";

# Detection and analysis constants
GENERATE_IMAGES_FROM_SIMULATION_OUTPUT=0;

DETECTION_AND_ANALYSIS_CONFIG_FOLDER="config/analysis/spatial";

CLUSTER_DETECTION_AND_ANALYSIS_CONFIG_FILE="${DETECTION_AND_ANALYSIS_CONFIG_FOLDER}/simulation_cluster_detector.xml";
RECTANGULAR_REGION_DETECTION_AND_ANALYSIS_CONFIG_FILE="${DETECTION_AND_ANALYSIS_CONFIG_FOLDER}/rectangular_region_detector.xml";

# MSTML constants
LINES_BEFORE_TIMEPOINT_CONTENT=3;
LINES_AFTER_TIMEPOINT_CONTENT=1;


###############################################################################
#
# Simulation output analysis specification
#
# This specification is used to determine which columns from the processed 
# simulation output file should be included in the resulting MSTML file and how
# they should be analysed.
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
#       <max-neighbours-distance>   represents the maximum distance between
#                                   two neighbouring points
#       <min-neighbours-in-cluster> represents the minimum number of 
#                                   neighbouring points required to build a
#                                   cluster
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
#       <alpha>                     represents the value by which the contrast
#                                   of the image corresponding to the 
#                                   discretised space is changed 
#       <beta>                      represents the value by which the 
#                                   brightness of the image corresponding to 
#                                   the discretised space is changed
#       <blur-kernel-size>          represents the size of the kernel applied
#                                   during the blur operation
#       <morphological-close-iter>  represents the number of times the 
#                                   morphological close operation is applied
#       <epsilon>                   represents the approximation degree of the
#                                   polygon constructed from the contour of the
#                                   region
#       <region-area-thresh>        represents the threshold value above which 
#                                   the area of a region has to be in order to 
#                                   be considered
#       <threshold-value>           represents the threshold value above which
#                                   the intensity of a position in the 
#                                   discretised space has to be in order to be 
#                                   considered
#                                   
#
# TODO: Update MSTML generation specification relative to the considered case 
#       study
#
###############################################################################

MSTML_GENERATION_SPECIFICATION="
Numeric 2 Organ.Uterus
Region 3 18 4 4 1 Tissue.ContractileActivity 0 100 0 0 0 0 0
Region 19 34 4 4 1 Tissue.BurstActivity 0 100 0 0 0 0 250
Region 35 50 4 4 1 Tissue.RefractoryActivity 0 100 0 0 0 0 250
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
    # Initialisation
    local rawSimulationOutputPath=$1;
    local simulationLogOutputPath=$2;
    local executionTimeLogOutputPath=$3;

    local rawSimulationOutputFolderPath=${rawSimulationOutputPath%.*};

    # Inform user where the simulation output is stored
    echo "Simulating ${MODEL_INPUT_FILE} and storing simulation output in ${rawSimulationOutputPath}...";

    # Create the raw simulation output folder if it does not exist already
    mkdir -p ${rawSimulationOutputFolderPath};

    # Create a temporary file for storing the version of the model in which the
    # generic path was replaced with the explicit path
    temporaryModelInputFile="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_model_input_file";

    # Replace the generic output path in the model with the explicit path and
    # store the resulting model in a temporary file
    cat ${MODEL_INPUT_FILE} | sed "s|SIMULATION_OUTPUT_FOLDER_PATH|${rawSimulationOutputFolderPath}|g" > ${temporaryModelInputFile};
    
    # Record execution start time
    local startTime=$(date +%s.%N);
    
    # Run a simulation of the model
    timeout ${COMMAND_EXECUTION_TIMELIMIT} math -noprompt -script ${temporaryModelInputFile} 1>${simulationLogOutputPath} 2>&1;
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "Model simulation execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> ${executionTimeLogOutputPath};
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
    # Initialisation
    local rawSimulationOutputPath=$1;
    local processedSimulationOutputPath=$2;
    local executionTimeLogOutputPath=$3;

    local rawSimulationOutputFolderPath=${rawSimulationOutputPath%.*};

    # Inform the user where the converted simulation output is stored
    echo "Converting the simulation output from raw (${rawSimulationOutputFolderPath}) to csv format (${processedSimulationOutputPath})...";

    # Create the raw simulation output folder if it does not exist already
    mkdir -p ${rawSimulationOutputFolderPath};

    # Record execution start time
    local startTime=$(date +%s.%N);
    
    # Convert the simulation output to csv format
    timeout ${COMMAND_EXECUTION_TIMELIMIT} paste "${rawSimulationOutputFolderPath}/pressure.out" "${rawSimulationOutputFolderPath}/activity.out" "${rawSimulationOutputFolderPath}/burst.out" "${rawSimulationOutputFolderPath}/refractory.out" | egrep "^[T0-9]+" | sed "s/[\t\n ]\+/,/g" | cut --complement -d"," -f3,20,37 > ${processedSimulationOutputPath};
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "Simulation output conversion to csv format execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> ${executionTimeLogOutputPath};
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
    local temporaryMSTMLSubfilesFolderPath=$1;
    local processedSimulationOutputPath=$2;
    local numericStateVariableColumnIndex=$3;
    local numericStateVariableSemanticType=$4;

    local numericStateVariableSemanticTypeOnlyLetters=${numericStateVariableSemanticType//./};

    local numericStateVariableName=$(cat ${processedSimulationOutputPath} | head -n1 | cut -d"," -f ${numericStateVariableColumnIndex});
    local numericStateVariableValues=$(cat ${processedSimulationOutputPath} | tail -n+2 | cut -d"," -f ${numericStateVariableColumnIndex});
    local outputFilepath="${temporaryMSTMLSubfilesFolderPath}/Numeric_${numericStateVariableSemanticTypeOnlyLetters}_${numericStateVariableName}.xml";

    # Add header information to the MSTML subfile
    echo "<?xml version=\"1.0\" encoding=\"utf-8\"?>" > ${outputFilepath};
    echo "" >> ${outputFilepath};
    echo "<experiment>" >> ${outputFilepath};

    # Add the contents to the MSTML subfile
    echo "${numericStateVariableValues}" | while read numericStateVariableValue;
    do
        echo -e "\t<timepoint>";
        echo -e "\t\t<numericStateVariable semanticType=\"${numericStateVariableSemanticType}\">";
        echo -e "\t\t\t<name>${numericStateVariableName}</name>";
        echo -e "\t\t\t<value>${numericStateVariableValue}</value>";
        echo -e "\t\t</numericStateVariable>";
        echo -e "\t</timepoint>";
    done >> ${outputFilepath};
    
    # Add footer information to the MSTML subfile
    echo "</experiment>" >> ${outputFilepath};
}

# Export function
export -f GenerateNumericTemporaryMSTMLSubfile 


# Update the cluster detection configuration file with the provided values 
#
# Function parameters:
#   $1 - The maximum distance between two neighbouring points
#   $2 - The minimum number of neighbouring points in a cluster
function UpdateClusterDetectionConfigurationFile() {
    # Initialisation
    local maxDistanceBtwNeighouringPoints=$1;
    local minNrOfNeighbouringPointsInCluster=$2;

    # Create a temporary configuration file
    temporaryDetectionConfigurationFile="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_detection_configuration_file";

    # Store the updated configuration in the temporary file
    cat ${CLUSTER_DETECTION_AND_ANALYSIS_CONFIG_FILE} | sed "s/\(<eps>\)[0-9]\+.\?[0-9]*\(<\/eps>\)/\1${maxDistanceBtwNeighouringPoints}\2/g" | sed "s/\(<minPoints>\)[0-9]\+.\?[0-9]*\(<\/minPoints>\)/\1${minNrOfNeighbouringPointsInCluster}\2/g" > ${temporaryDetectionConfigurationFile};

    # Replace the initial configuration file with the temporary file
    mv ${temporaryDetectionConfigurationFile} ${CLUSTER_DETECTION_AND_ANALYSIS_CONFIG_FILE};
}


# Generate a temporary MSTML subfile corresponding to a cluster
#
# Function parameters:
#   $1 - The temporary MSTML subfiles folder
#   $2 - Processed simulation output file path
#   $3 - Index of the start column recording values corresponding to potential 
#        clusters
#   $4 - Index of the stop column recording values corresponding to potential 
#        clusters
#   $5 - The height (number of rows) of the discretised spatial domain
#   $6 - The width (number of columns) of the discretised spatial domain
#   $7 - The number of entities which are tracked by their position in the 
#        discretised spatial domain
#   $8 - The maximum number of entities which can pile up on top of each other
#   $9 - The semantic type of the cluster state variable
function GenerateClusterTemporaryMSTMLSubfile() {
    # Initialisation
    local temporaryMSTMLSubfilesFolderPath=$1;
    local processedSimulationOutputPath=$2;
    local clustersStartColumnIndex=$3;
    local clustersStopColumnIndex=$4;
    local simulationGridHeight=$5;
    local simulationGridWidth=$6;
    local nrOfEntities=$7;
    local maxPileup=$8;
    local clustersSemanticType=$9;

    local clustersSemanticTypeOnlyLetters=${clustersSemanticType//./};

    local mstmlOutputPath="${temporaryMSTMLSubfilesFolderPath}/Cluster_${clustersSemanticTypeOnlyLetters}.xml";

    local homeFolder=$(pwd);

    local inputFileName=${processedSimulationOutputPath##*/};
    local inputFileBasename=${inputFileName%.*};

    local outputFolder="${homeFolder}/results/${inputFileBasename}/Cluster_${clustersSemanticTypeOnlyLetters}";

    local analysisOutputFolder="${outputFolder}/analysis";

    local visualisationOutputFolder="${outputFolder}/visualisation";
    local inputDataOutputFolder="${visualisationOutputFolder}/input";
    local scriptOutputFolder="${visualisationOutputFolder}/script";
    local imagesOutputFolder="${visualisationOutputFolder}/img";

    # Create the output folders
    mkdir -p ${outputFolder};

    mkdir -p ${analysisOutputFolder};
    mkdir -p ${visualisationOutputFolder};
    mkdir -p ${inputDataOutputFolder};
    mkdir -p ${scriptOutputFolder};
    mkdir -p ${imagesOutputFolder};

    # Create a temporary file for storing the values corresponding to potential clusters
    local simulationInputFile="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_simulation_input_file";

    # Add the values to the temporary file
    cat ${processedSimulationOutputPath} | cut -d"," -f1,${clustersStartColumnIndex}-${clustersStopColumnIndex} > ${simulationInputFile};


    ####################################################################################
    # Step 1: Preprocessing of simulation file for spatial analysis
    ####################################################################################

    # Copy the part of the csv file with necessary information to its corresponding input folder
    sed 's/^[;,:\t ]\+//g' <${simulationInputFile} | sed 's/[;,:\t ]\+/,/g' | tail -n+2 > ${inputDataOutputFolder}/${inputFileBasename};

    # Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
    bin/RectangularMapEntityCsvToInputFiles --input-file "${inputDataOutputFolder}/${inputFileBasename}" --nr-entities ${nrOfEntities} --max-pileup ${maxPileup} --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${inputDataOutputFolder}/${inputFileBasename}";

    # If the constant "GENERATE_IMAGES_FROM_SIMULATION_OUTPUT" != 0 then generate 
    # for each timepoint an image showing the value of the positions in the discretised 
    # space
    if [[ ${GENERATE_IMAGES_FROM_SIMULATION_OUTPUT} -ne 0 ]];
    then
        # Run MapCartesianToScript for converting each of the generated input files into gnuplot scripts
        find ${inputDataOutputFolder} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${scriptOutputFolder}/{/.};

        # Run gnuplot on each of the generated scripts from the script folder and ignore warnings
        cd ${imagesOutputFolder};

        ls -1 ${scriptOutputFolder} | parallel gnuplot ${scriptOutputFolder}/{} 2>/dev/null;

        cd ${homeFolder};
    fi


    ####################################################################################
    # Step 2: Spatial analysis of input files
    ####################################################################################

    # Define the basename of the input files without numeric index at the end
    local inputFileName=$(find ${inputDataOutputFolder} -name "*.in" | head -n1);
    local inputFileBasename=$(basename ${inputFileName});
    local inputFileBasenameRoot=$(echo ${inputFileBasename} | rev | cut -d'_' -f2- | rev);

    # Run the cluster detection procedure for each input file in parallel
    ls ${inputDataOutputFolder}/*.in | parallel --timeout ${COMMAND_EXECUTION_TIMELIMIT} bin/SimulationDetectClusters --input-file={} --output-file=${analysisOutputFolder}/{/.} --height=${simulationGridHeight} --width=${simulationGridWidth} --max-pileup=${maxPileup} --debug-mode="false"

    # Define the variables required to merge the xml files
    local clustersXMLOutputPath=${analysisOutputFolder}/"results_clusters.xml";

    # Create the resulting file
    local fileCount=$(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | wc -l);

    if [[ ${fileCount} -gt 0 ]];
    then
        local sampleFilePath=$(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | head -n1);

        # Print the header to the resulting file
        cat ${sampleFilePath} | head -n ${LINES_BEFORE_TIMEPOINT_CONTENT} > ${clustersXMLOutputPath};

        # Process each input file
        for file in $(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | sort -V);
        do
            cat ${file} | head -n -${LINES_AFTER_TIMEPOINT_CONTENT} | tail -n +$((${LINES_BEFORE_TIMEPOINT_CONTENT} + 1)) | sed "s/\(spatialType=\"cluster\"\)/\0 semanticType=\"${clustersSemanticType}\"/g" | sed "s/<numericStateVariable>/<numericStateVariable semanticType=\"${clustersSemanticType}\">/g"; 
        done >> ${clustersXMLOutputPath};

        # Print the footer to the resulting file
        cat ${sampleFilePath} | tail -n ${LINES_AFTER_TIMEPOINT_CONTENT} >> ${clustersXMLOutputPath};
    fi

    # Copy the resulting file where indicated
    cp ${clustersXMLOutputPath} ${mstmlOutputPath}; 
}


# Update the region detection configuration file with the provided values 
#
# Function parameters:
#   $1 - The value by which the contrast of the image corresponding to the
#        discretised space is changed
#   $2 - The value by which the brightness of the image corresponding to 
#        the discretised space is changed
#   $3 - The size of the kernel employed during the blur operation
#   $4 - The number of times the morphological close operation is applied
#   $5 - The degree of approximation employed during the construction
#        of the polygon corresponding to the regions contours
#   $6 - The threshold value above which the area of a region has to be
#        in order to be considered
#   $7 - The threshold value above which the intensity of each position in
#        the discretised space has to be in order to be considered
function UpdateRegionDetectionConfigurationFile() {
    # Initialisation
    local contrastChangingValue=$1;
    local brightnessChangingValue=$2;
    local blurKernelSize=$3;
    local morphologicalCloseIterations=$4;
    local polygonConstructionApproximationDegree=$5;
    local regionAreaThresholdValue=$6;
    local positionIntensityThresholdValue=$7;

    # Create a temporary configuration file
    temporaryDetectionConfigurationFile="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_detection_configuration_file";

    # Store the updated configuration in the temporary file
    cat ${RECTANGULAR_REGION_DETECTION_AND_ANALYSIS_CONFIG_FILE} | sed "s/\(<alpha>\)[0-9]\+.\?[0-9]*\(<\/alpha>\)/\1${contrastChangingValue}\2/g" | sed "s/\(<beta>\)[0-9]\+.\?[0-9]*\(<\/beta>\)/\1${brightnessChangingValue}\2/g" | sed "s/\(<blurKernelSize>\)[0-9]\+.\?[0-9]*\(<\/blurKernelSize>\)/\1${blurKernelSize}\2/g" | sed "s/\(<morphologicalCloseIterations>\)[0-9]\+.\?[0-9]*\(<\/morphologicalCloseIterations>\)/\1${morphologicalCloseIterations}\2/g" | sed "s/\(<epsilon>\)[0-9]\+.\?[0-9]*\(<\/epsilon>\)/\1${polygonConstructionApproximationDegree}\2/g" | sed "s/\(<regionAreaThresh>\)[0-9]\+.\?[0-9]*\(<\/regionAreaThresh>\)/\1${regionAreaThresholdValue}\2/g" | sed "s/\(<thresholdValue>\)[0-9]\+.\?[0-9]*\(<\/thresholdValue>\)/\1${positionIntensityThresholdValue}\2/g" > ${temporaryDetectionConfigurationFile};

    # Replace the initial configuration file with the temporary file
    mv ${temporaryDetectionConfigurationFile} ${RECTANGULAR_REGION_DETECTION_AND_ANALYSIS_CONFIG_FILE};
}


# Generate a temporary MSTML subfile corresponding to a region
#
# Function parameters:
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
    local temporaryMSTMLSubfilesFolderPath=$1;
    local processedSimulationOutputPath=$2;
    local regionsStartColumnIndex=$3;
    local regionsStopColumnIndex=$4;
    local simulationGridHeight=$5;
    local simulationGridWidth=$6;
    local nrOfConcentrationsForEachPosition=$7;
    local regionsSemanticType=$8;

    local regionsSemanticTypeOnlyLetters=${regionsSemanticType//./};

    local mstmlOutputPath="${temporaryMSTMLSubfilesFolderPath}/Region_${regionsSemanticTypeOnlyLetters}.xml";

    local homeFolder=$(pwd);

    local inputFileName=${processedSimulationOutputPath##*/};
    local inputFileBasename=${inputFileName%.*};

    local outputFolder="${homeFolder}/results/${inputFileBasename}/Region_${regionsSemanticTypeOnlyLetters}";

    local analysisOutputFolder="${outputFolder}/analysis";

    local visualisationOutputFolder="${outputFolder}/visualisation";
    local inputDataOutputFolder="${visualisationOutputFolder}/input";
    local scriptOutputFolder="${visualisationOutputFolder}/script";
    local imagesOutputFolder="${visualisationOutputFolder}/img";

    # Create the output folders
    mkdir -p ${outputFolder};

    mkdir -p ${analysisOutputFolder};

    mkdir -p ${visualisationOutputFolder};
    mkdir -p ${inputDataOutputFolder};
    mkdir -p ${scriptOutputFolder};
    mkdir -p ${imagesOutputFolder};

    # Create a temporary file for storing the values corresponding to potential regions
    local simulationInputFile="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_simulation_input_file";

    # Add the values to the temporary file
    cat ${processedSimulationOutputPath} | cut -d"," -f1,${regionsStartColumnIndex}-${regionsStopColumnIndex} > ${simulationInputFile};

    ####################################################################################
    # Step 1: Preprocessing of simulation file for spatial analysis
    ####################################################################################

    # Copy the part of the csv file with necessary information to its corresponding input folder
    sed 's/^[;,:\t ]\+//g' <${simulationInputFile} | sed 's/[;,:\t ]\+/,/g' | tail -n+2 > ${inputDataOutputFolder}/${inputFileBasename};

    # Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
    bin/RectangularMapCsvToInputFiles --input-file "${inputDataOutputFolder}/${inputFileBasename}" --nr-concentrations-position ${nrOfConcentrationsForEachPosition} --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${inputDataOutputFolder}/${inputFileBasename}";

    # If the constant "GENERATE_IMAGES_FROM_SIMULATION_OUTPUT" != 0 then generate 
    # for each timepoint an image showing the value of the positions in the discretised 
    # space
    if [[ ${GENERATE_IMAGES_FROM_SIMULATION_OUTPUT} -ne 0 ]];
    then
        # Run MapCartesianToScript for converting each of the generated input files into gnuplot scripts
        find ${inputDataOutputFolder} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${scriptOutputFolder}/{/.};

        # Run gnuplot on each of the generated scripts from the script folder and ignore warnings
        cd ${imagesOutputFolder};

        ls -1 ${scriptOutputFolder} | parallel gnuplot ${scriptOutputFolder}/{} 2>/dev/null;

        cd ${homeFolder};
    fi

    ####################################################################################
    # Step 2: Spatial analysis of input files
    ####################################################################################

    # Define the basename of the input files without numeric index at the end
    local inputFileName=$(find ${inputDataOutputFolder} -name "*.in" | head -n1);
    local inputFileBasename=$(basename ${inputFileName});
    local inputFileBasenameRoot=$(echo ${inputFileBasename} | rev | cut -d'_' -f2- | rev);

    # Run the region detection procedure for each input file in parallel
    ls ${inputDataOutputFolder}/*.in | parallel --timeout ${COMMAND_EXECUTION_TIMELIMIT} bin/RectangularDetectRegions --input-file={} --output-file=${analysisOutputFolder}/{/.} --debug-mode="false"

    # Define the variables required to merge the xml files
    local regionsXMLOutputPath=${analysisOutputFolder}/"results_regions.xml";

    # Create the resulting file
    local fileCount=$(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | wc -l);

    if [[ ${fileCount} -gt 0 ]];
    then
        local sampleFilePath=$(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | head -n1);

        # Print the header to the resulting file
        cat ${sampleFilePath} | head -n ${LINES_BEFORE_TIMEPOINT_CONTENT} > ${regionsXMLOutputPath};

        # Process each input file
        for file in $(find ${analysisOutputFolder} -name "${inputFileBasenameRoot}*.xml" | sort -V);
        do
            cat ${file} | head -n -${LINES_AFTER_TIMEPOINT_CONTENT} | tail -n +$((${LINES_BEFORE_TIMEPOINT_CONTENT} + 1)) | sed "s/\(spatialType=\"region\"\)/\0 semanticType=\"${regionsSemanticType}\"/g" | sed "s/<numericStateVariable>/<numericStateVariable semanticType=\"${regionsSemanticType}\">/g";
        done >> ${regionsXMLOutputPath};

        # Print the footer to the resulting file
        cat ${sampleFilePath} | tail -n ${LINES_AFTER_TIMEPOINT_CONTENT} >> ${regionsXMLOutputPath};
    fi

    # Copy the resulting file where indicated
    cp ${regionsXMLOutputPath} ${mstmlOutputPath}; 
}


# Generate temporary MSTML subfiles from the csv formatted simulation output 
# according to the MSTML_GENERATION_SPECIFICATION
#
# Function parameters:
#    $1 - Processed simulation output path
#    $2 - Execution time log file path
function GenerateTemporaryMSTMLSubfiles() {
    # Initialisation
    local processedSimulationOutputPath=$1;
    local executionTimeLogOutputPath=$2;

    # Inform the user where the temporary MSTML subfiles are stored
    echo "Processing (including spatio-temporal analysis) the csv file (${processedSimulationOutputPath}) and storing the resulting temporary MSTML subfiles in ${OUT_MSTML_SUBFILES_TMP_FOLDER}...";

    # Record execution start time
    local startTime=$(date +%s.%N);

    # Generate a MSTML subfile corresponding to each line in MSTML_GENERATION_SPECIFICATION starting with "Numeric"
    echo "${MSTML_GENERATION_SPECIFICATION}" | egrep "^Numeric" | parallel --colsep ' ' --timeout ${COMMAND_EXECUTION_TIMELIMIT} "GenerateNumericTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} ${processedSimulationOutputPath} {2} {3}";

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
            local maxDistanceBtwNeighours=$(echo ${mstmlSubfileSpecification} | cut -d" " -f9);
            local minNrOfNeighboursInCluster=$(echo ${mstmlSubfileSpecification} | cut -d" " -f10);
           
            # Update the clusters detection configuration file
            UpdateClusterDetectionConfigurationFile ${maxDistanceBtwNeighours} ${minNrOfNeighboursInCluster};

            # Generate the cluster temporary MSTML subfile 
            GenerateClusterTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} ${processedSimulationOutputPath} ${startColumn} ${stopColumn} ${simulationGridHeight} ${simulationGridWidth} ${nrOfEntities} ${maxPileup} ${semanticType};
        elif [[ ${stateVariableType} == "Region" ]];
        then
            local startColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f2);
            local stopColumn=$(echo ${mstmlSubfileSpecification} | cut -d" " -f3);
            local simulationGridHeight=$(echo ${mstmlSubfileSpecification} | cut -d" " -f4);
            local simulationGridWidth=$(echo ${mstmlSubfileSpecification} | cut -d" " -f5);
            local nrOfConcentrationsForEachPosition=$(echo ${mstmlSubfileSpecification} | cut -d" " -f6);
            local semanticType=$(echo ${mstmlSubfileSpecification} | cut -d" " -f7);
            local contrastChangingValue=$(echo ${mstmlSubfileSpecification} | cut -d" " -f8);
            local brightnessChangingValue=$(echo ${mstmlSubfileSpecification} | cut -d" " -f9);
            local blurKernelSize=$(echo ${mstmlSubfileSpecification} | cut -d" " -f10);
            local morphologicalCloseIterations=$(echo ${mstmlSubfileSpecification} | cut -d" " -f11);
            local polygonConstructionApproximationDegree=$(echo ${mstmlSubfileSpecification} | cut -d" " -f12);
            local regionAreaThresholdValue=$(echo ${mstmlSubfileSpecification} | cut -d" " -f13);
            local thresholdValue=$(echo ${mstmlSubfileSpecification} | cut -d" " -f14);

            # Update the regions detection configuration file
            UpdateRegionDetectionConfigurationFile ${contrastChangingValue} ${brightnessChangingValue} ${blurKernelSize} ${morphologicalCloseIterations} ${polygonConstructionApproximationDegree} ${regionAreaThresholdValue} ${thresholdValue};
           
            # Generate the cluster temporary MSTML subfile 
            GenerateRegionTemporaryMSTMLSubfile ${OUT_MSTML_SUBFILES_TMP_FOLDER} ${processedSimulationOutputPath} ${startColumn} ${stopColumn} ${simulationGridHeight} ${simulationGridWidth} ${nrOfConcentrationsForEachPosition} ${semanticType};
        fi;
    done;
    
    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "MSTML subfiles generation execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> ${executionTimeLogOutputPath};
}


# Merge temporary MSTML subfiles into a single MSTML file
#
# Function parameters:
#   $1 - Folder containing temporary MSTML subfiles
#   $2 - Processed simulation output path
#   $3 - MSTML output path
#   $4 - Execution time log file path
function MergeMSTMLSubfiles() {
    # Initialisation
    local temporaryMSTMLSubfilesFolderPath=$1;
    local processedSimulationOutputPath=$2;
    local mstmlOutputPath=$3;
    local executionTimeLogOutputPath=$4;

    # Inform the user where the resulting MSTML file is stored
    echo "Merging MSTML subfiles from the ${temporaryMSTMLSubfilesFolderPath} folder into the resulting MSTML file ${mstmlOutputPath}...";

    # Record execution start time
    local startTime=$(date +%s.%N);

    # Initialisation
    local timepointsValuesFilePath="${OUT_MSTML_SUBFILES_TMP_FOLDER}/tmp_timepoints_values_file_path";

    ####################################################################################
    # Step 1: Store the timepoints values in a separate file
    ####################################################################################
     
    cat ${processedSimulationOutputPath} | cut -d"," -f1 > ${timepointsValuesFilePath};

    ####################################################################################
    # Step 2: Merge MSTML subfiles
    ####################################################################################

    bin/MSTMLSubfilesMergerSample --mstml-subfiles-folder ${temporaryMSTMLSubfilesFolderPath} --timepoints-values-file ${timepointsValuesFilePath} --mstml-output-file ${mstmlOutputPath}

    # Record execution stop time
    local stopTime=$(date +%s.%N);
    
    # Print the execution time to file
    echo "MSTML subfiles merging execution time:" $(echo "${stopTime} - ${startTime}" | bc) "seconds." >> ${executionTimeLogOutputPath};
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
    # Step 0: Initialisation
    ##############################################################################
    
    # Inform the user that the user will be simulated and analysed the i-th time
    echo "Model simulation and analysis iteration: ${i} (Start time: ${date})";


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
    
    MergeMSTMLSubfiles ${OUT_MSTML_SUBFILES_TMP_FOLDER} ${processedSimulationOutputPath} ${mstmlOutputPath} ${executionTimeLogOutputPath}

    
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


##############################################################################
#
# Termination
#
##############################################################################

# Remove temporary folder(s)
rm -rf ${OUT_MSTML_SUBFILES_TMP_FOLDER}
