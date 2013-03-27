#!/bin/bash

if [ $# -eq 3 ];
then
    folderNamePrefix=$1;
    finalStateIndex=$2;
    destinationFolder=$3;

    # Create the destination folder

    mkdir -p ${destinationFolder};

    # Copy all the images in the destination folder
    
    for folder in ${folderNamePrefix}*;
    do
        image=$(ls ${folder} | grep "${folderNamePrefix}_[0-9]*_${finalStateIndex}.png");

        cp ${folder}/${image} ${destinationFolder};
    done
else
    echo "Incorrect number of parameters provided";
fi
