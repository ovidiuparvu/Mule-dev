Project multiscale
==========

## Contents

1. **Introduction**
2. **Requirements**
    1. Building
    2. Running
3. **Running the movie generating scripts** 
    1. Rectangular geometry
        1. Rectangular geometry and representing the discretised 2D space
        2. Rectangular geometry and representing entities' positions in 2D space
    2. Circular geometry
4. **Running the region detection and analysis scripts**
    1. Rectangular geometry
    2. Circular geometry
5. **Running the cluster detection and analysis scripts**
    1. Rectangular geometry
6. **Contact**

## 1. Introduction

**Author:** Ovidiu Parvu                                                        
**Created on:** 04.02.2013
**Modified on:** 13.04.2014

## 2. Requirements
   
### 2.1. Requirements for building the program

For building the program the following software need to be installed on your
computer:
* CMake (ver. 2.8 or higher)
* Boost library (ver. 1.52.0)
* g++ (ver. 4.7 or higher)
* OpenCV (ver. 2.4.4 or higher)
* Xerces C++ (ver. 3.1.1 or higher)

__Remarks:__ 

1. CMake will attempt to automatically find the paths to your Boost, OpenCV and Xerces include and library folders.

### 2.2. Requirements for running the software

For running the program the following software need to be installed on your
computer:
* avconv
* Bash or an alternative shell which supports the same commands
* gnuplot (ver. 4.6)
* GNU parallel

__Remarks:__ 

1. If the project was build using the shared OpenCV libraries, then the path to the shared OpenCV libraries should be included in your PATH environment variable, such that they are accessible at runtime.

## 3. Running the movie generating scripts
   
### 3.1. Rectangular geometry

#### 3.1.1 Rectangular geometry and representing the discretised 2D space

For generating a movie from a _.csv_ file considering a rectangular geometry and representing the discretised 2D space use the script _RunRectangularGeometryViewer.sh_. The information regarding required parameters is displayed when running the script without any parameters.

#### 3.1.2 Rectangular geometry and representing entities' positions in 2D space

For generating a movie from a _.csv_ file considering a rectangular geometry and representing entities' positions in 2D space use the script _RunRectangularGeometryEntityViewer.sh_. The information regarding required parameters is displayed when running the script without any parameters.

### 3.2. Circular geometry

For generating a movie from a _.csv_ file considering a circular geometry use the script _RunCircularGeometryViewer.sh_. The information regarding required parameters is displayed when running the script without any parameters.

## 4. Running the region detection and analysis scripts
   
### 4.1. Rectangular geometry

For detecting and analysing regions of high intensity in an image considering a rectangular geometry use the script _RunRectangularRegionDetector.sh_. The information regarding required parameters is displayed when running the script without any parameters.

### 4.2. Circular geometry

For detecting and analysing regions of high intensity in an image considering a circular geometry use the script _RunCircularRegionDetector.sh_. The information regarding required parameters is displayed when running the script without any parameters.

## 5. Running the cluster detection and analysis scripts

### 5.1. Rectangular geometry
   
For detecting and analysing clusters of entities in images considering a rectangular geometry use the script _RunSimulationDetectClusters.sh_.

## 6. Contact

For more details please visit my [personal webpage](http://brunel.ac.uk/~cspgoop).