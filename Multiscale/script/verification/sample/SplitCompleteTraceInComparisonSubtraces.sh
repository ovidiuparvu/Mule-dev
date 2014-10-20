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

# Create the output folder
mkdir -p ${OUTPUT_FOLDER};


###############################################################################
#
# Create the output subfolders
#
###############################################################################

# Obtain names and number of parameters
parametersSpecificationRow=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | head -n2 | tail -n+2);
parametersNames=$(echo "${parametersSpecificationRow}" | egrep -o "^([^,]+,)+" | sed "s/[^,]\+,\(.*\),/\1/" | egrep -o "[^,]+");
nrOfParameters=$(echo "${parametersNames}" | wc -l);

# Create subfolders
for parameterName in $(echo "${parametersNames}");
do
    mkdir -p "${OUTPUT_FOLDER}/${parameterName}";
done


###############################################################################
#
# Create the subtraces output files
#
###############################################################################

# Obtain the names and number of entities/species
entitiesNames=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | head -n1 | egrep -o "[^,]+" | head -n-1 | tail -n+2);
nrOfEntities=$(echo "${entitiesNames}" | wc -l);

# Create the subtraces output files
for parameterIndex in $(seq 1 1 ${nrOfParameters});
do
    # Obtain the parameter name
    parameterName=$(echo "${parametersNames}" | cut -d$'\n' -f${parameterIndex});

    for firstEntityIndex in $(seq 1 1 ${nrOfEntities});
    do
        # Obtain the name of the first entity
        firstEntityName=$(echo "$entitiesNames" | cut -d$'\n' -f ${firstEntityIndex});

        for secondEntityIndex in $(seq $((${firstEntityIndex} + 1)) 1 ${nrOfEntities});
        do
            if [[ ${firstEntityIndex} -ne ${secondEntityIndex} ]];
            then
                # Obtain the name of the second entity
                secondEntityName=$(echo "$entitiesNames" | cut -d$'\n' -f ${secondEntityIndex});

                # Obtain the header row
                headerRow="Time,$(echo ${entitiesNames} | cut -d" " -f${firstEntityIndex},${secondEntityIndex} | sed 's/ /,/g')";

                # Obtain the subtrace contents
                contentsFirstEntityIndex=$((2 + 3 * (${firstEntityIndex} - 1) + ${parameterIndex} - 1));
                contentsSecondEntityIndex=$((2 + 3 * (${secondEntityIndex} - 1) + ${parameterIndex} - 1));

                contents=$(cat ${COMPLETE_TIMESERIES_FILEPATH} | tail -n+3 | cut -d"," -f1,${contentsFirstEntityIndex},${contentsSecondEntityIndex});

                # Output the subtrace to the corresponding file
                echo "${headerRow}" > "${OUTPUT_FOLDER}/${parameterName}/${firstEntityName}_${secondEntityName}.csv"
                echo "${contents}" >> "${OUTPUT_FOLDER}/${parameterName}/${firstEntityName}_${secondEntityName}.csv"
            fi
        done
    done
done
