#!/bin/bash

if [ $# -ne 3 ];
then
    echo "Usage: GetDictyosteliumPositionsFromResults.sh <input_file> <output_file> <nr_dictyostelium_cells>.";
    
    exit 1;
fi

awkCommand=$(
    # Create the awk command
    indices="print \$1,"; 

    seq `expr 2 \* $3 + 1` -1 2 | \
    { while read index; 
    do 
        indices="${indices}\$${index},"; 
    done; 

    echo ${indices}; 
    } | sed 's/,$//g';
)

# Execute the awk command
awk -F , -v OFS=, "{ $awkCommand }" $1 > $2


