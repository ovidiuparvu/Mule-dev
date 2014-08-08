#!/bin/bash

# Check if the required number of parameters was provided
if [[ $# -ne 1 ]];
then
    echo "Usage: MergeAttributeTestFiles.sh <attribute-test-files-folder>";

    exit 1;
fi

# Check if a folder was provided as input
if [[ ! -d $1 ]]; 
then
    echo "The provided <attribute-test-files-folder> input path is invalid. Please change.";

    exit 1;
fi

# Merge the unit test files
for file in `find $1 -type f -name "*.hpp" | sort`; 
do 
    # Obtain the file basename
    filename=${file#./*}

    # Print the header for each file
    echo "/////////////////////////////////////////////////////////"; 
    echo "//"; 
    echo "//"; 
    echo "// ${filename}"; 
    echo "//"; 
    echo "//"; 
    echo "/////////////////////////////////////////////////////////"; 

    # Print the contents for each file
    echo ;
    echo ;

    cat ${file} | tail -n+12 | head -n-2;

    echo ;
    echo ;
done
