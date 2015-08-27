#!/bin/bash

# Check if the number of input parameters is correct
if [[ $# -ne 2 ]];
then
    echo "Usage: $0 <sample-input-file-with-one-timepoint> <nr-generated-trace-folders>.";

    exit 1;
fi

# Check if a valid input trace file was provided
if [[ ! -f $1 ]];
then
    echo "Please run the script with a valid trace input file.";

    exit 1;
fi

# Check if a valid number of generated input files was provided
if [[ $2 -lt 0 ]];
then
    echo "Please run the script with a non-negative number of generated trace folders.";

    exit 1;
fi

# Get the header, contents and footer of an input file
header=`cat $1 | head -n3`;
contents=`cat $1 | head -n-1 | tail -n+4`;
footer=`cat $1 | tail -n1`;

# Generate the trace folders
nrOfTraceFolders=$2;

for i in `seq 1 1 ${nrOfTraceFolders}`;
do
    nrOfTimepoints=$(( 2 ** ${i} ));
    tracesFolder="traces_${nrOfTimepoints}";

    # Create the folder which contains the traces
    mkdir -p ${tracesFolder};

    # Create the constant area traces
    for j in `seq 1 1 25`;
    do
        echo "${header}" > ${tracesFolder}/traces_constant_${j}.xml;

        # Add time points to the trace
        for k in `seq 1 1 ${nrOfTimepoints}`;
        do
            echo "${contents}" >> ${tracesFolder}/traces_constant_${j}.xml;
        done

        echo "${footer}" >> ${tracesFolder}/traces_constant_${j}.xml;
    done

    # Create the increasing area traces
    for j in `seq 1 1 25`;
    do
        echo "${header}" > ${tracesFolder}/traces_increasing_${j}.xml;

        # Add time points to the trace
        for k in `seq 1 1 ${nrOfTimepoints}`;
        do
            echo "${contents}" | sed "s/<area>[0-9.]\+<\/area>/<area>${k}<\/area>/g" >> ${tracesFolder}/traces_increasing_${j}.xml;
        done

        echo "${footer}" >> ${tracesFolder}/traces_increasing_${j}.xml;
    done

    # Create the decreasing area traces
    for j in `seq 1 1 25`;
    do
        echo "${header}" > ${tracesFolder}/traces_decreasing_${j}.xml;

        # Add time points to the trace
        for k in `seq 1 1 ${nrOfTimepoints}`;
        do
            echo "${contents}" | sed "s/<area>[0-9.]\+<\/area>/<area>$(( ${nrOfTimepoints} - ${k} ))<\/area>/g" >> ${tracesFolder}/traces_decreasing_${j}.xml;
        done

        echo "${footer}" >> ${tracesFolder}/traces_decreasing_${j}.xml;
    done

    # Create the oscillating area traces
    for j in `seq 1 1 25`;
    do
        echo "${header}" > ${tracesFolder}/traces_oscillating_${j}.xml;

        # Add time points to the trace
        for k in `seq 1 1 ${nrOfTimepoints}`;
        do
            if [[ $(( $k % 4 )) -eq 0 ]];
            then
                echo "${contents}" | sed "s/<area>[0-9.]\+<\/area>/<area>0<\/area>/g" >> ${tracesFolder}/traces_oscillating_${j}.xml;
            else
                echo "${contents}" | sed "s/<area>[0-9.]\+<\/area>/<area>${k}<\/area>/g" >> ${tracesFolder}/traces_oscillating_${j}.xml;
            fi
        done

        echo "${footer}" >> ${tracesFolder}/traces_oscillating_${j}.xml;
   done
done
