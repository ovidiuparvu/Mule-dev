#!/bin/bash

for file in phase_variation_in_space10_$1x$2_no_diagonal_poolsize_$3_*;
do
    ./CircularGeometryViewer.sh $file 2 $1 $2
done
