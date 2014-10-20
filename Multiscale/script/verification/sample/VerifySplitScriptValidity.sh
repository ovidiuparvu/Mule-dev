#!/bin/bash

# Check if the number of provided command line arguments is two (i.e. input trace and output folder)
if [[ $# -ne 2 ]];
then
    echo "Usage: $0 <complete-timeseries-input-file> <output-folder>";

    exit 1;
fi

# Check if the complete timeseries input file is a regular file
if [[ ! -f $1 ]];
then
    echo "The provided complete timeseries input file is not a regular file. Please change.";

    exit 1;
fi


# Define constant valued variables
COMPLETE_TIMESERIES_FILEPATH=$1;
OUTPUT_FOLDER=$2;

TMP_OUTPUT_FILE_1="/tmp/temporary_comparison_file1.csv";
TMP_OUTPUT_FILE_2="/tmp/temporary_comparison_file2.csv";

# Obtain names and number of parameters
parametersSpecificationRow=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | head -n2 | tail -n+2);
parametersNames=$(echo "${parametersSpecificationRow}" | egrep -o "^([^,]+,)+" | sed "s/[^,]\+,\(.*\),/\1/" | egrep -o "[^,]+");
nrOfParameters=$(echo "${parametersNames}" | wc -l);

# Obtain the names and number of entities/species
entitiesNames=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | head -n1 | egrep -o "[^,]+" | head -n-1 | tail -n+2);
nrOfEntities=$(echo "${entitiesNames}" | wc -l);

# Create the subtraces output files
for parameterIndex in $(seq 1 1 ${nrOfParameters});
do
    # Obtain the parameter name
    parameterName=$(echo "${parametersNames}" | cut -d$'\n' -f${parameterIndex});

    for firstEntityIndex in $(seq 1 2 ${nrOfEntities});
    do
        # Obtain the name of the first entity
        firstEntityName=$(echo "$entitiesNames" | cut -d$'\n' -f ${firstEntityIndex});

        for secondEntityIndex in $(seq $((${firstEntityIndex} + 1)) 1 ${nrOfEntities});
        do
            if [[ ${firstEntityIndex} -ne ${secondEntityIndex} ]];
            then
                # Obtain the name of the second entity
                secondEntityName=$(echo "$entitiesNames" | cut -d$'\n' -f ${secondEntityIndex});

                # Obtain the subtrace contents
                contentsFirstEntityIndex=$((2 + 3 * (${firstEntityIndex} - 1) + ${parameterIndex} - 1));
                contentsSecondEntityIndex=$((2 + 3 * (${secondEntityIndex} - 1) + ${parameterIndex} - 1));

                subTraceContents=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | tail -n+3 | cut -d"," -f1,${contentsFirstEntityIndex},${contentsSecondEntityIndex});

                # Find the corresponding output file
                outputFilePath=$(find ${OUTPUT_FOLDER}/${parameterName} -name "${firstEntityName}_${secondEntityName}.csv");
                outputFileContents=$(cat ${outputFilePath} | tail -n+2);

                # Store the subtrace and output file contents in temporary files
                echo "${subTraceContents}" > ${TMP_OUTPUT_FILE_1};
                echo "${outputFileContents}" > ${TMP_OUTPUT_FILE_2};

                # Compare the contents of the temporary files
                diff -q ${TMP_OUTPUT_FILE_1} ${TMP_OUTPUT_FILE_2}
            fi
        done
    done
done
