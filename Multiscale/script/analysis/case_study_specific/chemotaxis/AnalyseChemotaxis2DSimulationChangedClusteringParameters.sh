#!/bin/bash

####################################################################################
# 
# Initialisation step
#
####################################################################################

if [ $# -ne 6 ];
then
    echo "An error occurred: Incorrect input arguments provided.";
    echo "";
    echo "Usage: AnalyseChemotaxis2DSimulation.sh <simulation-input-file> <simulation-grid-height> <simulation-grid-width> <nr-dictyostelium-cells> <max-pileup> <stml-output-path>.";
    
    exit 1;
fi

# Initialize the variables
simulationInputFile=$1;
simulationGridHeight=$2;
simulationGridWidth=$3;
nrOfCells=$4;
maxPileup=$5;
stmlOutputPath=$6;

HOME_FOLDER=`pwd`;

INPUT_FILENAME=${simulationInputFile##*/};
INPUT_BASENAME=${INPUT_FILENAME%.*};

OUT_FOLDER="${HOME_FOLDER}/results/${INPUT_BASENAME}";

OUT_ANALYSIS_FOLDER="${OUT_FOLDER}/analysis";

OUT_VISUALISATION_FOLDER="${OUT_FOLDER}/visualisation";
OUT_INPUT_FOLDER="${OUT_VISUALISATION_FOLDER}/input";
OUT_SCRIPT_FOLDER="${OUT_VISUALISATION_FOLDER}/script";
OUT_IMG_FOLDER="${OUT_VISUALISATION_FOLDER}/img";

# Create the output folders
mkdir -p ${OUT_FOLDER};

mkdir -p ${OUT_ANALYSIS_FOLDER};
mkdir -p ${OUT_VISUALISATION_FOLDER};
mkdir -p ${OUT_INPUT_FOLDER};
mkdir -p ${OUT_SCRIPT_FOLDER};
mkdir -p ${OUT_IMG_FOLDER};


####################################################################################
# 
# Analyse images of cells
#
####################################################################################

# Define the results output files
clustersOutputFile=${OUT_ANALYSIS_FOLDER}/"results_clusters";
nrOfClustersOutputFile=${OUT_ANALYSIS_FOLDER}/"results_nr_clusters";
clustersClusterednessOutputFile=${OUT_ANALYSIS_FOLDER}/"results_clusteredness";
clustersPileupOutputFile=${OUT_ANALYSIS_FOLDER}/"results_pileup";

# Define the basename of the images without numeric index at the end
imageName=`find ${OUT_IMG_FOLDER} -name "*.png" | head -n1`;
imageBasename=`basename ${imageName}`;
imageBasenameRoot=`echo ${imageBasename} | rev | cut -d'_' -f2- | rev`;

# Run the cluster detection procedure for each image in parallel
ls ${OUT_IMG_FOLDER}/*.png | parallel ./bin/SimulationDetectClusters --input-file={} --output-file=${OUT_ANALYSIS_FOLDER}/{/.} --height=${simulationGridHeight} --width=${simulationGridWidth} --max-pileup=${maxPileup} --debug-mode="false"

# Empty files which will store final results
echo "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${clustersOutputFile};
echo "Number of regions" > ${nrOfClustersOutputFile};
echo "Clusteredness" > ${clustersClusterednessOutputFile};
echo "Pile up" > ${clustersPileupOutputFile};

# Write the clusters, number of clusters, overall clusteredness and overall pileup in separate files
for output in `ls -1v ${OUT_ANALYSIS_FOLDER}/*.out`;
do
    cat ${output} | head -n-3 | tail -n+2 >> ${clustersOutputFile};
    cat ${output} | head -n-3 | tail -n+2 | wc -l >> ${nrOfClustersOutputFile}

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${clustersClusterednessOutputFile};

    cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${clustersPileupOutputFile};
done

# Define the variables required to merge the xml files
linesBeforeTimePointContent=3;
linesAfterTimePointContent=1;
clustersXMLOutputPath=${OUT_ANALYSIS_FOLDER}/"results_regions.xml";

# Create the resulting file
fileCount=`find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | wc -l`;

if [[ ${fileCount} -gt 0 ]];
then
    sampleFilePath=`find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | head -n1`;

    # Print the header to the resulting file
    cat ${sampleFilePath} | head -n ${linesBeforeTimePointContent} > ${clustersXMLOutputPath};

    # Process each input file
    for file in `find ${OUT_ANALYSIS_FOLDER} -name "${imageBasenameRoot}*.xml" | sort -V`;
    do
        cat ${file} | head -n -${linesAfterTimePointContent} | tail -n +$((${linesBeforeTimePointContent} + 1)) >> ${clustersXMLOutputPath};
    done 

    # Print the footer to the resulting file
    cat ${sampleFilePath} | tail -n ${linesAfterTimePointContent} >> ${clustersXMLOutputPath};
fi

# Copy the resulting file where indicated
cp ${clustersXMLOutputPath} ${stmlOutputPath}/${INPUT_BASENAME}.xml;
