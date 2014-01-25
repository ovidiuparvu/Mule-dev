#!/bin/bash

# Defining the constants for the script
MOVIE_FRAME_RATE=1;
MOVIE_FLAGS="-same_quant -r ${MOVIE_FRAME_RATE}"

if [ $# -eq 5 ];
then
    inputFolder=$1;
    outputFolder=$2;
    height=$3;
    width=$4;
    maxPileup=$5;

    # Define the results output files
    clustersOutputFile=${outputFolder}/"results_clusters";
    nrOfClustersOutputFile=${outputFolder}/"results_nr_clusters";
    clusterednessOutputFile=${outputFolder}/"results_clusteredness";
    pileupOutputFile=${outputFolder}/"results_pileup";
    
    # Define the movie output path
    movieOutputFolder=${outputFolder}/"movie";
    
    # Define the basename of the images without numeric index at the end
    imageName=`ls ${inputFolder}/*.png | head -n1`;
    imageBasename=`basename ${imageName}`;
    imageBasenameRoot=`echo ${imageBasename} | rev | cut -d'_' -f2- | rev`;
    
    # Create the output folders
    mkdir -p ${outputFolder}
    mkdir -p ${movieOutputFolder}

    # Start the timer for measuring the total execution time
    startTime=$(date +%s.%N);

    # Inform user of the next action
    echo "Running the cluster detection procedure for each image...";

    # Run the cluster detection procedure for each image in parallel
    ls ${inputFolder}/*.png | parallel ./bin/SimulationDetectClusters --input-file={} --output-file=${outputFolder}/{/.} --height=${height} --width=${width} --max-pileup=${maxPileup}

    # Empty files which will store final results
    echo "Clusteredness degree,Pile up degree,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${clustersOutputFile};
    echo "Number of clusters" > ${nrOfClustersOutputFile};
    echo "Clusteredness" > ${clusterednessOutputFile};
    echo "Pile up" > ${pileupOutputFile};

    # Write the clusters, number of clusters, overall clusteredness and overall pileup in separate files
    for output in `ls -1v ${outputFolder}/*.out`;
    do
        cat ${output} | head -n-3 | tail -n+3 >> ${clustersOutputFile};
        cat ${output} | head -n-3 | tail -n+3 | wc -l >> ${nrOfClustersOutputFile}

        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | head -n 1 >> ${clusterednessOutputFile};
   
        cat ${output} | tail -n 2 | grep -o "[0-9.]\+" | tail -n 1 >> ${pileupOutputFile};
    done
    
    # Inform user of the next action
    echo "Generating the movie from the images...";
    
    # Generate the movie
    avconv ${MOVIE_FLAGS} -f image2 -i ${outputFolder}/${imageBasenameRoot}_%d.png ${movieOutputFolder}/${imageBasenameRoot}.mp4
    
    # Print end message
    echo "The movie was generated successfully.";

    # End the timer for measuring the total execution time
    endTime=$(date +%s.%N);
    
    # Print the total execution time
    echo 
    echo "Total execution time: " $(echo "${endTime} - ${startTime}" | bc) " seconds.";
    
else
    echo "Please run the script with the parameters: <input_folder> <output_folder> <height_of_grid> <width_of_grid> <max_pileup>.";
fi
