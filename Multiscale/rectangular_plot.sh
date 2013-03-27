#!/bin/bash

for file in phase_variation_in_space4*$1x$2*;
do
    ./RectangularGeometryViewer.sh $file 2 $1 $2
done
