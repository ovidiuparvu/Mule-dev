#!/bin/bash

for file in phase_variation_in_space4_$1x$2_fixed_poolsize_$3_*.csv;
do
    ./RectangularGeometryViewer.sh $file 2 $1 $2
done
