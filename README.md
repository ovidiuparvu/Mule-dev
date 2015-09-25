<a name="top"></a> The multiscale spatio-temporal meta model checking project 
==========

## Contents

1. [**Description**](#description)
2. [**Install guide**](#install_guide)
3. [**Execution guide**](#execution_guide)
4. [**Additional information**](#additional_information)

## <a name="description"></a> 1. Description 

Mule is a multiscale spatio-temporal approximate probabilistic meta model checker employed for the validation of computational models relative to a given formal PBLMSTL specification.

**Author:**      Ovidiu Pârvu   
**Created on:**  04.02.2013                                          
**Modified on:** 25.09.2015

Click [here](#top) to go back to the top of the page.

## <a name="install_guide"></a> 2. Install guide 

### 2.1. Prerequisites

For building and installing the model checker Mule please ensure the following libraries and software are installed on your computer:
* Boost library (ver. 1.55.0);
* CMake (ver. 2.8);
* g++ (ver. 4.7);
* OpenCV (ver. 2.4.8);
* python (ver. 2.7.3) interpreter including libraries lxml, jinja2 and setuptools;
* Xerces C++ (ver. 3.1.1).

__Remark:__  The build system CMake will attempt to automatically find the paths to your Boost, OpenCV and Xerces include and library folders. Moreover CMake will check if both the python interpreter and the required libraries are available.

### 2.2. Installation steps

1) Assuming the source code of the project is available in folder %PROJECT_SOURCE_DIRECTORY% (called by default Multiscale) the first step for compiling and installing the project is to change the current directory to the %PROJECT_SOURCE_DIRECTORY%/build/Release folder (for Release version) using:

```bash
cd %PROJECT_SOURCE_DIRECTORY%/build/Release
```

__Remark:__ If the %PROJECT_SOURCE_DIRECTORY%/build/Release folder does not exist then please create it.

2) Run cmake to generate the Makefiles employed for compiling the project using:

```cmake
cmake -G %GENERATOR% -DCMAKE_BUILD_TYPE=Release -DCMAKE_CUSTOM_BUILD_TYPE=Package -DCMAKE_CUSTOM_MODEL_CHECKER=Generate ../../
```

where:

* -G specifies the custom build system generator (e.g. replace %GENERATOR% with "Unix Makefiles" for Linux, respectively "MinGW Makefiles" for Windows);
* -DCMAKE_BUILD_TYPE specifies the build type (which can be either "Release" or "Debug");
* -DCMAKE_CUSTOM_BUILD_TYPE specifies the custom build type (when CMAKE_CUSTOM_BUILD_TYPE=Package the files required for generating an installer are created);
* -DCMAKE_CUSTOM_MODEL_CHECKER specifies if a custom instance of the model checker should be generated considering the spatial entity types and properties described in the %PROJECT_SOURCE_DIRECTORY%/config/verification/spatial-temporal/generator/spatial_description.xml configuration file.

3) Build the project using:

```bash
make all
```

4) To additionally generate an installer containing the model checker and the required configuration files run the command:

```bash
cpack
```

5) Run the generated installer to set up the model checker.

Click [here](#top) to go back to the top of the page.

## <a name="execution_guide"></a> 3. Execution guide 

### 3.1. Prerequisites

For running all scripts and/or executable modules ensure the following software are installed on your computer:
* avconv (ver. 0.8.16-4:0.8.16-0ubuntu0.12.04.1) - employed only by visualisation scripts;
* Bash and standard Unix utility tools (e.g. awk, grep, sed);
* GNU parallel (ver. 20140722) - employed only by scripts to run tasks in parallel;
* gnuplot (ver. 4.6) - employed only by visualisation scripts.

__Remark:__ If the project was compiled using shared libraries then include the path to the shared libraries in your PATH environment variable to ensure that the libraries are accessible at runtime.

### 3.2. Execution steps

The executable modules can be run using:

```bash
%PROJECT_SOURCE_DIRECTORY%/bin/%EXECUTABLE_MODULE%
```

where %EXECUTABLE_MODULE% is one of the following:

* **CircularDetectRegions**: Spatio-temporal module for automatically detecting regions and computing their geometric properties (e.g. area) considering a circular geometry;
* **MapCartesianToPolarScript**: Module for converting time point input files (i.e. input files corresponding to a single simulation time point) to gnuplot scripts, considering a circular geometry;
* **MapCartesianToScript**: Module for converting time point input files to gnuplot scripts, considering a rectangular geometry;
* **Mule**: The multiscale spatio-temporal approximate probabilistic meta model checker;
* **PolarMapCsvToInputFiles**: Module for converting csv files considering a circular geometry to time point input files which are employed either for (regions) spatio-temporal analysis or for generating gnuplot scripts;
* **RectangularDetectRegions**: Spatio-temporal module for automatically detecting regions and computing their geometric properties (e.g. area) considering a rectangular geometry;
* **RectangularMapCsvToInputFiles**: Module for converting csv files considering a rectangular geometry to time point input files which are employed either for (regions) spatio-temporal analysis or for generating gnuplot scripts;
* **RectangularMapEntityCsvToInputFiles**: Module for converting csv files describing positions of spatial entities in 2D space to time point input files which are employed either for (clusters) spatio-temporal analysis or for generating gnuplot scripts;
* **SimulationDetectClusters**: Spatio-temporal module for automatically detecting clusters and computing their geometric properties (e.g. area).

__Remark:__ Assuming the executable modules were set up using the installer and their installation path was added to the PATH environment variable, they can be executed from the command line without prefixing them with the "%PROJECT_SOURCE_DIRECTORY%/bin" path.

Click [here](#top) to go back to the top of the page.

## <a name="additional_information"></a> 4. Additional information

For additional information please visit the [official Mule website](http://mule.modelchecking.org).

Click [here](#top) to go back to the top of the page.
