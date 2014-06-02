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

    # Run a simulation of the model
    morpheus ${MODEL_INPUT_FILE} 1>${simulationLogOutputPath};

    # Move the simulation result file to the simulation raw folder
    mv ${MODEL_OUTPUT_FILE} ${rawSimulationOutputPath};

    # Convert the simulation result file to the required format
    gawk -f ConvertSimulationOutputFormat.awk ${rawSimulationOutputPath} > ${processedSimulationOutputPath};

    # Generate the STML file corresponding to the simulation output represented in the new format
    AnalyseChemotaxis2DSimulation.sh ${processedSimulationOutputPath} ${MODEL_GRID_HEIGHT} ${MODEL_GRID_WIDTH} ${MODEL_NR_CELLS} ${MAX_NR_PILEUP} ${stmlOutputPath};
done
