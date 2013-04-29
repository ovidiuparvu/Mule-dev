#!/bin/bash

for file in $1*.csv;
do
    ./RectangularGeometryViewer.sh ${file} 2 $2 $3
done
