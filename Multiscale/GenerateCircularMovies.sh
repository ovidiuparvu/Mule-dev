#!/bin/bash

for file in *.csv;
do
    CircularGeometryViewer.sh ${file} 2 61 61
done
