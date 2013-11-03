#!/bin/bash

# Defining the constants for the script
MOVIE_FRAME_RATE=1;
MOVIE_FLAGS="-same_quant -r ${MOVIE_FRAME_RATE}"

if [ $# -eq 2 ];
then
    inputFolder=$1;
    outputFolder=$2;

    # Define the movie output path
    movieOutputFolder=${outputFolder}/"movie";
    
    # Define the basename of the images without numeric index at the end
    imageName=`ls ${inputFolder}/*.png | head -n1`;
    imageBasename=`basename ${imageName}`;
    imageBasenameRoot=`echo ${imageBasename} | rev | cut -d'_' -f2- | rev`;
    
    # Create the output folders
    mkdir -p ${outputFolder}
    mkdir -p ${movieOutputFolder}

    # Define the results output files
    regionsOutputFile=${outputFolder}/"results_regions";
    nrOfRegionsOutputFile=${outputFolder}/"results_nr_regions";
    clusterednessOutputFile=${outputFolder}/"results_clusteredness";
    pileupOutputFile=${outputFolder}/"results_pileup";

    # Start the timer for measuring the total execution time
    startTime=$(date +%s.%N);

    # Inform user of the next action
    echo "Running the region detection procedure for each image...";

    # Run the cluster detection procedure for each image in parallel
    ls ${inputFolder}/*.png | parallel ./bin/CircularDetectRegions --input-file={} --output-file=${outputFolder}/{/.} --debug-mode="false"
    
    # Empty files which will store final results
    echo "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${regionsOutputFile};
    echo "Number of regions" > ${nrOfRegionsOutputFile};
    echo "Clusteredness" > ${clusterednessOutputFile};
    echo "Pile up" > ${pileupOutputFile};

    # Write the clusters, number of clusters, overall clusteredness and overall pileup in separate files
    for output in `ls -1v ${outputFolder}/*.out`;
    do
        cat ${output} | head -n-3 | tail -n+2 >> ${regionsOutputFile};
        cat ${output} | head -n-3 | tail -n+2 | wc -l >> ${nrOfRegionsOutputFile}

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
    echo "Please run the script with the parameters: <input_folder> <output_folder>.";
fi
