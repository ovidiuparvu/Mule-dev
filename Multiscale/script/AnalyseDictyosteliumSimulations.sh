####################################################################################
# 
# Initialisation step
#
####################################################################################

if [ $# -ne 5 ];
then
    echo "An error occurred: Incorrect input arguments provided.";
    echo "";
    echo "Usage: AnalyseDictyosteliumSimulations.sh <simulation_input_file> <simulation-grid-height> <simulation-grid-width> <nr-dictyostelium-cells> <max-pileup>.";
    
    exit 1;
fi

# Initialise the variables
simulationInputFile=$1;
simulationGridHeight=$2;
simulationGridWidth=$3;
nrOfDictyosteliumCells=$4;
maxPileup=$5;

HOME_FOLDER=`pwd`;

R_FOLDER="${HOME_FOLDER}/R";

DATE=`date +"%F-%T"`;
OUT_FOLDER="${HOME_FOLDER}/results/${simulationGridHeight}x${simulationGridWidth}_${nrOfDictyosteliumCells}/${DATE}";

OUT_ANALYSIS_FOLDER="${OUT_FOLDER}/analysis";
OUT_VISUALISATION_FOLDER="${OUT_FOLDER}/visualisation";

OUT_INPUT_FOLDER="${OUT_VISUALISATION_FOLDER}/input";
OUT_SCRIPT_FOLDER="${OUT_VISUALISATION_FOLDER}/script";
OUT_IMG_FOLDER="${OUT_VISUALISATION_FOLDER}/img";

OUT_DICTY_INPUT_FOLDER="${OUT_INPUT_FOLDER}/dictyostelium";
OUT_DICTY_SCRIPT_FOLDER="${OUT_SCRIPT_FOLDER}/dictyostelium";
OUT_DICTY_IMG_FOLDER="${OUT_IMG_FOLDER}/dictyostelium";

OUT_CAMP_INPUT_FOLDER="${OUT_INPUT_FOLDER}/cAMP";
OUT_CAMP_SCRIPT_FOLDER="${OUT_SCRIPT_FOLDER}/cAMP";
OUT_CAMP_IMG_FOLDER="${OUT_IMG_FOLDER}/cAMP";

OUT_DICTY_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dictyostelium";
OUT_CAMP_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/cAMP";

OUT_COMPARE_COORDINATES_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dicty_compare_coordinates";
OUT_DISTANCE_CLUSTERS_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dicty_distance_cAMP_dicty_clusters";
OUT_NR_CAMP_CLUSTERS_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dicty_nr_cAMP_clusters";
OUT_NR_DICTY_CLUSTERS_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dicty_nr_dicty_clusters";
OUT_AREA_PILEUP_NR_DICTY_CLUSTERS_ANALYSIS_FOLDER="${OUT_ANALYSIS_FOLDER}/dicty_area_pileup_nr_dicty_clusters";

DICTY_FILE_BASENAME="dictyostelium_${simulationGridHeight}x${simulationGridWidth}_${nrOfDictyosteliumCells}";
CAMP_FILE_BASENAME="cAMP_${simulationGridHeight}x${simulationGridWidth}_${nrOfDictyosteliumCells}";

DICTY_SIMULATION_FILE="${OUT_FOLDER}/${DICTY_FILE_BASENAME}.csv";
CAMP_SIMULATION_FILE="${OUT_FOLDER}/${CAMP_FILE_BASENAME}.csv";

# Create the output folders
mkdir -p ${OUT_FOLDER};

mkdir -p ${OUT_DICTY_INPUT_FOLDER};
mkdir -p ${OUT_DICTY_SCRIPT_FOLDER};
mkdir -p ${OUT_DICTY_IMG_FOLDER};

mkdir -p ${OUT_CAMP_INPUT_FOLDER};
mkdir -p ${OUT_CAMP_SCRIPT_FOLDER};
mkdir -p ${OUT_CAMP_IMG_FOLDER};

mkdir -p ${OUT_DICTY_ANALYSIS_FOLDER};
mkdir -p ${OUT_CAMP_ANALYSIS_FOLDER};

mkdir -p ${OUT_COMPARE_COORDINATES_ANALYSIS_FOLDER};
mkdir -p ${OUT_DISTANCE_CLUSTERS_ANALYSIS_FOLDER};
mkdir -p ${OUT_NR_CAMP_CLUSTERS_ANALYSIS_FOLDER};
mkdir -p ${OUT_NR_DICTY_CLUSTERS_ANALYSIS_FOLDER};
mkdir -p ${OUT_AREA_PILEUP_NR_DICTY_CLUSTERS_ANALYSIS_FOLDER};


####################################################################################
# 
# Obtain separate simulation files for Dictyostelium cells and cAMP
#
####################################################################################

# Compute the indices for the columns of interest
nrOfColumns=`awk -F',' '{print NF; exit}' ${simulationInputFile}`;
startIndexCells=`expr ${nrOfColumns} - 2 \* ${nrOfDictyosteliumCells} - ${simulationGridHeight} \* ${simulationGridWidth} + 1`;
stopIndexCells=`expr ${startIndexCells} + 2 \* ${nrOfDictyosteliumCells} - 1`;
startIndexCAMP=`expr ${startIndexCells} + 2 \* ${nrOfDictyosteliumCells}`;
stopIndexCAMP=`expr ${startIndexCAMP} + ${simulationGridHeight} \* ${simulationGridWidth} - 1`;

# Obtain the separate simulation file for the Dictyostelium cells
cat ${simulationInputFile} | cut -d"," -f1,${startIndexCells}-${stopIndexCells} > ${DICTY_SIMULATION_FILE}

# Obtain the separate simulation file for cAMP
cat ${simulationInputFile} | cut -d"," -f1,${startIndexCAMP}-${stopIndexCAMP} > ${CAMP_SIMULATION_FILE}

# Check if the initial marking for the Dictyostelium cells was greater than 0
nrOfZeroInitialMarkings=`cat ${DICTY_SIMULATION_FILE} | cut -d, -f2- | egrep "[^0-9]0[^0-9.]" ${DICTY_SIMULATION_FILE} | wc -l`;

if [ ${nrOfZeroInitialMarkings} -gt 0 ];
then
    echo "Dictyostelium initial marking contained the number 0. Execution of the script halted."

    rm -rf ${OUT_FOLDER};

    exit 1;
fi


####################################################################################
# 
# Generate images for cAMP simulation file
#
####################################################################################

# Copy the part of the csv file with necessary information to its corresponding input folder
sed 's/^[;,:\t ]\+//g' <${CAMP_SIMULATION_FILE} | sed 's/[;,:\t ]\+/,/g' | tail -n +2 > ${OUT_CAMP_INPUT_FOLDER}/${CAMP_FILE_BASENAME};

# Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
bin/RectangularMapCsvToInputFiles --input-file "${OUT_CAMP_INPUT_FOLDER}/${CAMP_FILE_BASENAME}" --nr-concentrations-position 1 --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${OUT_CAMP_INPUT_FOLDER}/${CAMP_FILE_BASENAME}";

# Run the MapCartesianToScript for converting each of the generated input files into gnuplot scripts
find ${OUT_CAMP_INPUT_FOLDER} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${OUT_CAMP_SCRIPT_FOLDER}/{/.};

# Run gnuplot on each of the generated scripts from the script folder and ignore warnings
cd ${OUT_CAMP_IMG_FOLDER};

ls -1 ${OUT_CAMP_SCRIPT_FOLDER} | parallel gnuplot ${OUT_CAMP_SCRIPT_FOLDER}/{} 2>/dev/null;

cd ${HOME_FOLDER};


####################################################################################
# 
# Generate images for Dictyostelium cells simulation file
#
####################################################################################

# Copy the part of the csv file with necessary information to its corresponding input folder
sed 's/^[;,:\t ]\+//g' <${DICTY_SIMULATION_FILE} | sed 's/[;,:\t ]\+/,/g' | tail -n +2 > ${OUT_DICTY_INPUT_FOLDER}/${DICTY_FILE_BASENAME};

# Run the program for converting the ".csv" file to "Number of time points" input files for the MapCartesianToScript program
bin/RectangularMapEntityCsvToInputFiles --input-file "${OUT_DICTY_INPUT_FOLDER}/${DICTY_FILE_BASENAME}" --nr-entities ${nrOfDictyosteliumCells} --max-pileup ${maxPileup} --height ${simulationGridHeight} --width ${simulationGridWidth} --output-file "${OUT_DICTY_INPUT_FOLDER}/${DICTY_FILE_BASENAME}";

# Run the MapCartesianToScript for converting each of the generated input files into gnuplot scripts
find ${OUT_DICTY_INPUT_FOLDER} -name "*.in" | parallel bin/MapCartesianToScript --input-file {} --output-file ${OUT_DICTY_SCRIPT_FOLDER}/{/.};

# Run gnuplot on each of the generated scripts from the script folder and ignore warnings
cd ${OUT_DICTY_IMG_FOLDER};

ls -1 ${OUT_DICTY_SCRIPT_FOLDER} | parallel gnuplot ${OUT_DICTY_SCRIPT_FOLDER}/{} 2>/dev/null;

cd ${HOME_FOLDER};


####################################################################################
# 
# Analyse images of Dictyostelium cells
#
####################################################################################

# Define the results output files
clustersOutputFile=${OUT_DICTY_ANALYSIS_FOLDER}/"results_clusters";
nrOfClustersOutputFile=${OUT_DICTY_ANALYSIS_FOLDER}/"results_nr_clusters";
clusterednessOutputFile=${OUT_DICTY_ANALYSIS_FOLDER}/"results_clusteredness";
pileupOutputFile=${OUT_DICTY_ANALYSIS_FOLDER}/"results_pileup";

# Define the basename of the images without numeric index at the end
imageName=`find ${OUT_DICTY_IMG_FOLDER} -name "*.png" | head -n1`;
imageBasename=`basename ${imageName}`;
imageBasenameRoot=`echo ${imageBasename} | rev | cut -d'_' -f2- | rev`;

# Run the cluster detection procedure for each image in parallel
find ${OUT_DICTY_IMG_FOLDER} -name "*.png" | parallel ./bin/SimulationDetectClusters --input-file={} --output-file=${OUT_DICTY_ANALYSIS_FOLDER}/{/.} --height=${simulationGridHeight} --width=${simulationGridWidth} --max-pileup=${maxPileup}

# Empty files which will store final results
echo "Clusteredness degree,Pile up degree,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${clustersOutputFile};
echo "Number of clusters" > ${nrOfClustersOutputFile};
echo "Clusteredness" > ${clusterednessOutputFile};
echo "Pile up" > ${pileupOutputFile};

# Write the clusters, number of clusters, overall clusteredness and overall pileup in separate files
for output in `find ${OUT_DICTY_ANALYSIS_FOLDER} -name "*.out" | sort -V`;
do
    cat ${output} | head -n-3 | tail -n+3 >> ${clustersOutputFile};
    cat ${output} | head -n-3 | tail -n+3 | wc -l >> ${nrOfClustersOutputFile}

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${clusterednessOutputFile};

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${pileupOutputFile};
done


####################################################################################
# 
# Analyse images of cAMP
#
####################################################################################

# Define the basename of the images without numeric index at the end
imageName=`find ${OUT_CAMP_IMG_FOLDER} -name "*.png" | head -n1`;
imageBasename=`basename ${imageName}`;
imageBasenameRoot=`echo ${imageBasename} | rev | cut -d'_' -f2- | rev`;

# Define the results output files
regionsOutputFile=${OUT_CAMP_ANALYSIS_FOLDER}/"results_regions";
nrOfRegionsOutputFile=${OUT_CAMP_ANALYSIS_FOLDER}/"results_nr_regions";
clusterednessOutputFile=${OUT_CAMP_ANALYSIS_FOLDER}/"results_clusteredness";
pileupOutputFile=${OUT_CAMP_ANALYSIS_FOLDER}/"results_pileup";

# Run the region detection procedure for each image in parallel
find ${OUT_CAMP_IMG_FOLDER} -name "*.png" | parallel ./bin/RectangularDetectRegions --input-file={} --output-file=${OUT_CAMP_ANALYSIS_FOLDER}/{/.} --debug-mode="false"

# Empty files which will store final results
echo "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${regionsOutputFile};
echo "Number of regions" > ${nrOfRegionsOutputFile};
echo "Clusteredness" > ${clusterednessOutputFile};
echo "Pile up" > ${pileupOutputFile};

# Write the regions, number of regions, overall clusteredness and overall pileup in separate files
for output in `find ${OUT_CAMP_ANALYSIS_FOLDER} -name "*.out" | sort -V`;
do
    cat ${output} | head -n-3 | tail -n+2 >> ${regionsOutputFile};
    cat ${output} | head -n-3 | tail -n+2 | wc -l >> ${nrOfRegionsOutputFile}

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${clusterednessOutputFile};

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${pileupOutputFile};
done


####################################################################################
# 
# Analyse cAMP and Dictyostelium clusters using R scripts
#
####################################################################################

cp ${R_FOLDER}/*.R ${OUT_ANALYSIS_FOLDER};

cd ${OUT_ANALYSIS_FOLDER};

Rscript AnalyseResultsBatch.R "${OUT_DICTY_ANALYSIS_FOLDER}/results_clusters" "${OUT_DICTY_ANALYSIS_FOLDER}/results_nr_clusters" "${OUT_CAMP_ANALYSIS_FOLDER}/results_regions" "${OUT_CAMP_ANALYSIS_FOLDER}/results_nr_regions";

rm -f ${OUT_ANALYSIS_FOLDER}/*.R;

cd ${HOME_FOLDER};
