#!/bin/bash

####################################################################################
# 
# Initialisation step
#
####################################################################################

if [ $# -ne 0 ];
then
    echo "An error occurred: Incorrect input arguments provided.";
    echo "";
    echo "Usage: GenerateChemotaxis2DSTMLFile.sh.";
    
    exit 1;
fi

# Change the current directory to the directory where the script is located
cd "$( dirname "${BASH_SOURCE[0]}" )";

# Constants initialisation
CASE_STUDY_TITLE="chemotaxis2D";

NR_MODEL_SIMULATIONS=5;

MODEL_INPUT_FILE="model/chemotaxis2D.xml";
MODEL_OUTPUT_FILE="logger_cell.center.x_cell.center.y_all.log";
MODEL_GRID_HEIGHT=100;
MODEL_GRID_WIDTH=100;
MODEL_NR_CELLS=100;
MAX_NR_PILEUP=5;

OUT_SIMULATION="simulations";
OUT_SIMULATION_LOG="${OUT_SIMULATION}/log";
OUT_SIMULATION_PROCESSED="${OUT_SIMULATION}/processed";
OUT_SIMULATION_RAW="${OUT_SIMULATION}/raw";

OUT_STML_FOLDER="/media/seagate3tb/Analysis/CaseStudies/Chemotaxis/stml";

# Create output folders if they do not already exist
mkdir -p ${OUT_SIMULATION};
mkdir -p ${OUT_SIMULATION_LOG};
mkdir -p ${OUT_SIMULATION_PROCESSED};
mkdir -p ${OUT_SIMULATION_RAW};

mkdir -p ${OUT_STML_FOLDER};


####################################################################################
# 
# Generate STML files
#
####################################################################################

for i in `seq 1 1 ${NR_MODEL_SIMULATIONS}`;
do
    # Get the current date and time
    date=`date +"%F-%T"`;

    # Initialise the simulation dependent variables
    name="${CASE_STUDY_TITLE}_${date}";
    simulationLogOutputPath="${OUT_SIMULATION_LOG}/${name}.out";
    processedSimulationOutputPath="${OUT_SIMULATION_PROCESSED}/${name}.csv";
    rawSimulationOutputPath="${OUT_SIMULATION_RAW}/${name}.log";
    stmlOutputPath="${OUT_STML_FOLDER}/${name}.xml";

    # Inform user where the simulation output is stored
    echo "Simulating ${MODEL_INPUT_FILE} and storing simulation output in ${rawSimulationOutputPath}...";

    # Run a simulation of the model
    timelimit -T 360 morpheus ${MODEL_INPUT_FILE} 1>${simulationLogOutputPath};

    # Move the simulation result file to the simulation raw folder
    timelimit -T 360 mv ${MODEL_OUTPUT_FILE} ${rawSimulationOutputPath};

    # Inform the user where the converted simulation output is stored
    echo "Converting the simulation output to the required format...";

    # Convert the simulation result file to the required format
    timelimit -T 360 gawk -f ConvertSimulationOutputFormat.awk ${rawSimulationOutputPath} > ${processedSimulationOutputPath};

    # Generate the STML file corresponding to the simulation output represented in the new format
    echo "Generating the ${stmlOutputPath} STML file from the converted simulation output ${processedSimulationOutputPath}...";

    # Generate the STML file corresponding to the simulation output represented in the new format
    timelimit -T 360 AnalyseChemotaxis2DSimulation.sh ${processedSimulationOutputPath} ${MODEL_GRID_HEIGHT} ${MODEL_GRID_WIDTH} ${MODEL_NR_CELLS} ${MAX_NR_PILEUP} ${stmlOutputPath};

    # Separate model simulation output using a blank line
    echo;
done
