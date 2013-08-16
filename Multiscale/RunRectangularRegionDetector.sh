#!/bin/bash

if [ $# -eq 2 ];
then
    inputFolder=$1;
    outputFolder=$2;

    # Create the output folder
    mkdir -p ${outputFolder}

    # Define the results output files
    regionsResultFile=${outputFolder}/"results_regions";
    nrOfRegionsResultFile=${outputFolder}/"results_number_regions";
    
    # Start the timer for measuring the total execution time
    startTime=$(date +%s.%N);

    # Inform user of the next action
    echo "Running the region detection procedure for each image...";

    # Run the cluster detection procedure for each image in parallel
    ls ${inputFolder}/*.png | parallel ./bin/RectangularDetectRegions --input-file={} --output-file=${outputFolder}/{/.} --debug-mode="false"
    
    # Empty files which will store final results
    echo "Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)" > ${regionsResultFile};
    echo "Number of regions" > ${nrOfRegionsResultFile};

    # Write the number of regions for each image into a file and the other results into a separate file
    for output in ${outputFolder}/*.out;
    do
        tail -n+2 ${output} >> ${regionsResultFile};
        
        lines=`cat ${output} | wc -l`;

        echo $(( ${lines} - 1 )) >> ${nrOfRegionsResultFile};
    done

    # Print end message
    echo "The region detection procedure(s) ended successfully.";

    # End the timer for measuring the total execution time
    endTime=$(date +%s.%N);
    
    # Print the total execution time
    echo 
    echo "Total execution time: " $(echo "${endTime} - ${startTime}" | bc) " seconds.";

else
    echo "Please run the script with the parameters: <input_folder> <output_folder>.";
fi
