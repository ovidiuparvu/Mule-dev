#!/bin/bash

for file in *$1x$2*;
do
    ./RectangularGeometryViewer.sh $file 2 $1 $2
done
