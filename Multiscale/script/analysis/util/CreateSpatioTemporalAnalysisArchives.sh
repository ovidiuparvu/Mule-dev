# !/bin/bash

###############################################################################
#
# Script for generating the spatio-temporal analysis modules
#
###############################################################################

# Check if the required parameters were provided as command-line arguments

if [[ $# -ne 2 ]];
then
	echo "Usage: $0 <simulation-and-analysis-case-studies-folder-path> <multiscale-folder-path>.";

    exit 1;
fi

# Check if the provided folder paths are valid

if [[ ! -d $1 ]];
then
    echo "The provided simulation and analysis case studies folder path is invalid. Please change.";

    exit 1;
elif [[ ! -d $2 ]];
then
    echo "The provided multiscale folder path is invalid. Please change.";

    exit 1;
fi

# Initialize constants

SPATIO_TEMPORAL_ANALYSIS_FOLDER_PREFIX="stm_";

SPATIO_TEMPORAL_ANALYSIS_FOLDER_CARDIOVASCULAR_VPR="${SPATIO_TEMPORAL_ANALYSIS_FOLDER_PREFIX}cardiovascular_vpr";
SPATIO_TEMPORAL_ANALYSIS_FOLDER_UTERINE_CONTRACTIONS="${SPATIO_TEMPORAL_ANALYSIS_FOLDER_PREFIX}uterine_contractions";
SPATIO_TEMPORAL_ANALYSIS_FOLDER_XENOPUS_LAEVIS_CELL_CYCLE="${SPATIO_TEMPORAL_ANALYSIS_FOLDER_PREFIX}xenopus_laevis_cell_cycle";
SPATIO_TEMPORAL_ANALYSIS_FOLDER_ACUTE_INFLAMMATION_OF_GUT_AND_LUNG="${SPATIO_TEMPORAL_ANALYSIS_FOLDER_PREFIX}acute_inflammation_of_gut_and_lung";

# Declare and initialize the associative array SIMULATION_AND_ANALYSIS_FOLDER

declare -A SIMULATION_AND_ANALYSIS_FOLDER;

SIMULATION_AND_ANALYSIS_FOLDER[${SPATIO_TEMPORAL_ANALYSIS_FOLDER_CARDIOVASCULAR_VPR}]="$1/CardioVascularVPR";
SIMULATION_AND_ANALYSIS_FOLDER[${SPATIO_TEMPORAL_ANALYSIS_FOLDER_UTERINE_CONTRACTIONS}]="$1/UterineContractions";
SIMULATION_AND_ANALYSIS_FOLDER[${SPATIO_TEMPORAL_ANALYSIS_FOLDER_XENOPUS_LAEVIS_CELL_CYCLE}]="$1/XenopusLaevisCellCycle";
SIMULATION_AND_ANALYSIS_FOLDER[${SPATIO_TEMPORAL_ANALYSIS_FOLDER_ACUTE_INFLAMMATION_OF_GUT_AND_LUNG}]="$1/AcuteInflammationOfGutAndLung";

# Create the archives in which the spatio-temporal analysis related files are stored

for spatioTemporalAnalysisFolder in "${!SIMULATION_AND_ANALYSIS_FOLDER[@]}";
do
    # Inform the user which spatio-temporal analysis archive is created
    echo "Creating the spatio-temporal analysis archive ${spatioTemporalAnalysisFolder}.zip...";

    # Initialize constants
    BIN_FOLDER="${spatioTemporalAnalysisFolder}/bin";    
    LOG_FOLDER="${spatioTemporalAnalysisFolder}/log/execution_time";
    MSTML_FOLDER="${spatioTemporalAnalysisFolder}/mstml";
    RESULTS_FOLDER="${spatioTemporalAnalysisFolder}/results";
    SIMULATIONS_FOLDER="${spatioTemporalAnalysisFolder}/simulations";
    SIMULATIONS_LOG_FOLDER="${SIMULATIONS_FOLDER}/log";
    SIMULATIONS_PROCESSED_FOLDER="${SIMULATIONS_FOLDER}/processed";
    SIMULATIONS_RAW_FOLDER="${SIMULATIONS_FOLDER}/raw";

    # Create the folders in which the spatio-temporal analysis related files are stored
    rm -rf "${spatioTemporalAnalysisFolder}" && mkdir -p "${BIN_FOLDER}";

    # Copy the relevant executables
    cp "$2/bin/CircularDetectRegions" "${BIN_FOLDER}";
    cp "$2/bin/MapCartesianToPolarScript" "${BIN_FOLDER}";
    cp "$2/bin/MapCartesianToScript" "${BIN_FOLDER}";
    cp "$2/bin/Mule" "${BIN_FOLDER}";
    cp "$2/bin/PolarMapCsvToInputFiles" "${BIN_FOLDER}";
    cp "$2/bin/RectangularDetectRegions" "${BIN_FOLDER}";
    cp "$2/bin/RectangularMapCsvToInputFiles" "${BIN_FOLDER}";
    cp "$2/bin/RectangularMapEntityCsvToInputFiles" "${BIN_FOLDER}";
    cp "$2/bin/sample/MSTMLSubfilesMergerSample" "${BIN_FOLDER}";
    cp "$2/bin/sample/XmlValidatorSample" "${BIN_FOLDER}";
    cp "$2/bin/SimulationDetectClusters" "${BIN_FOLDER}";

    # Copy the configuration files
    cp -rf "$2/config" "${spatioTemporalAnalysisFolder}";

    # Create the log folder
    mkdir -p "${LOG_FOLDER}";

    # Copy the model files
    cp -rf "${SIMULATION_AND_ANALYSIS_FOLDER[${spatioTemporalAnalysisFolder}]}/model" "${spatioTemporalAnalysisFolder}";

    # Create the mstml folder
    mkdir -p "${MSTML_FOLDER}";

    # Create the results folder
    mkdir -p "${RESULTS_FOLDER}";

    # Create the simulations folders
    mkdir -p "${SIMULATIONS_LOG_FOLDER}";
    mkdir -p "${SIMULATIONS_PROCESSED_FOLDER}";
    mkdir -p "${SIMULATIONS_RAW_FOLDER}";

    # Copy simulation and analysis related files
    find ${SIMULATION_AND_ANALYSIS_FOLDER[${spatioTemporalAnalysisFolder}]} -maxdepth 1 -type f -name "*.*" | while read file;
    do
        cp "${file}" "${spatioTemporalAnalysisFolder}";
    done

    # Create the corresponding archive and remove the folder
    zip -r -q "${spatioTemporalAnalysisFolder}.zip" "${spatioTemporalAnalysisFolder}" && rm -rf "${spatioTemporalAnalysisFolder}";
done

# Inform the user that the execution completed successfully
echo "The spatio-temporal archives were successfully created.";
