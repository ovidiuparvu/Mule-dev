#!/bin/bash

if [ $# -eq 2 ];
then
    inputFolder=$1;
    outputFolder=$2;

    # Create the output folder

    mkdir -p ${outputFolder}

    # Start the timer for measuring the total execution time
    startTime=$(date +%s.%N);

    # Inform user of the next action
    echo "Running the region detection procedure for each image...";

    RESULT_FILE_NR_REGIONS=${outputFolder}/"results_number_regions";
    RESULT_FILE=${outputFolder}/"results";

    # Run the region detection procedure for each image

    for imageFile in ${inputFolder}/*.png;
    do
        imageFileBasename=`basename ${imageFile}`;
        imageFilename=${imageFileBasename%.*};

        ./bin/CircularDetectRegions -i ${imageFile} -o ${outputFolder}/${imageFilename}
    done

    # Empty files which will store final results
    
    echo "Number of regions" > ${RESULT_FILE_NR_REGIONS};
    echo "Area,Distance from origin,Angle(degrees)" > ${RESULT_FILE};

    # Write the number of regions for each image into a file and the other results into a separate file

    for output in ${outputFolder}/*.out;
    do
        lines=`cat ${output} | wc -l`;

        echo $(( ${lines} - 1 )) >> ${RESULT_FILE_NR_REGIONS};
        
        tail -n+2 ${output} >> ${RESULT_FILE};
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
