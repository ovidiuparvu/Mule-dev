#!/bin/bash

###############################################################################
#
# Update the provided MSTML file considering the new Mule specification based 
# on the multiscale architecture graph concept. 
#
###############################################################################

# Check if the required parameters were provided as input

if [[ $# -ne 1 ]];
then
    echo "Usage: $0 <file>.";
    
    exit 1;
fi

# Check if the provided file path is valid

if [[ ! -f $1 ]];
then
    echo "The provided file path $1 is not valid. Please change.";
    
    exit 1;
fi

# Make all required changes

cat ${1} | sed "s/Tissue.\(Lung\|Gut\)Endothelium.Cellular.Ischemia/Cellular.\1EndotheliumIschemia/g" | sed "s/semanticType/scaleAndSubsystem/g" | sed "s/\([a-zA-Z0-9]\+\)\.\([a-zA-Z0-9]\+\)\.\([a-zA-Z0-9]\+\)\.\([a-zA-Z0-9]\+\)/\3.\4/g" > ${1}.bak && mv ${1}.bak ${1};
