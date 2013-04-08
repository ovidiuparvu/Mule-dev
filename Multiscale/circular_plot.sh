#!/bin/bash

ls -1 $1 | tail -n430 | head -n134 | while read file;
do
    ./CircularGeometryViewer2.sh $1/${file} 2 $2 $3
done
