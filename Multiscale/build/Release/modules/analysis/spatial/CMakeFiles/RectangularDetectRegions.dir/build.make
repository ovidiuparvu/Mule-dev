# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ovidiu/Repositories/git/multiscale/Multiscale

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release

# Include any dependencies generated for this target.
include modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/depend.make

# Include the progress variables for this target.
include modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/progress.make

# Include the compile flags for this target's objects.
include modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o: ../../modules/analysis/spatial/src/CircularityMeasure.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/CircularityMeasure.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/CircularityMeasure.cpp > CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/CircularityMeasure.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o: ../../modules/analysis/spatial/src/Detector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Detector.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Detector.cpp > CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Detector.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o: ../../modules/analysis/spatial/src/MatFactory.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/MatFactory.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/MatFactory.cpp > CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/MatFactory.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o: ../../modules/analysis/spatial/src/RectangularDetectRegions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RectangularDetectRegions.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RectangularDetectRegions.cpp > CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RectangularDetectRegions.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o: ../../modules/analysis/spatial/src/Region.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Region.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Region.cpp > CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/Region.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o: ../../modules/analysis/spatial/src/RegionDetector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RegionDetector.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RegionDetector.cpp > CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/RegionDetector.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o: ../../modules/analysis/spatial/src/SpatialCollection2D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/SpatialCollection2D.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/SpatialCollection2D.cpp > CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/SpatialCollection2D.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/flags.make
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o: ../../modules/analysis/spatial/src/factory/RectangularMatFactory.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o -c /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/factory/RectangularMatFactory.cpp

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.i"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/factory/RectangularMatFactory.cpp > CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.i

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.s"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial/src/factory/RectangularMatFactory.cpp -o CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.s

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.requires:
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.provides: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.requires
	$(MAKE) -f modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.provides.build
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.provides

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.provides.build: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o

# Object files for target RectangularDetectRegions
RectangularDetectRegions_OBJECTS = \
"CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o" \
"CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o"

# External object files for target RectangularDetectRegions
RectangularDetectRegions_EXTERNAL_OBJECTS =

../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o
../../bin/RectangularDetectRegions: ../../lib/libutil.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_calib3d.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_contrib.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_core.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_features2d.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_flann.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_gpu.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_highgui.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_imgproc.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_legacy.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_ml.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_nonfree.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_objdetect.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_photo.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_stitching.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_ts.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_video.so
../../bin/RectangularDetectRegions: /usr/local/lib/libopencv_videostab.so
../../bin/RectangularDetectRegions: /usr/local/lib/libboost_program_options.a
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build.make
../../bin/RectangularDetectRegions: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../../bin/RectangularDetectRegions"
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RectangularDetectRegions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build: ../../bin/RectangularDetectRegions
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/build

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/CircularityMeasure.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Detector.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/MatFactory.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RectangularDetectRegions.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/Region.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/RegionDetector.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/SpatialCollection2D.cpp.o.requires
modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires: modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/src/factory/RectangularMatFactory.cpp.o.requires
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/requires

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/clean:
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial && $(CMAKE_COMMAND) -P CMakeFiles/RectangularDetectRegions.dir/cmake_clean.cmake
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/clean

modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/depend:
	cd /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ovidiu/Repositories/git/multiscale/Multiscale /home/ovidiu/Repositories/git/multiscale/Multiscale/modules/analysis/spatial /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial /home/ovidiu/Repositories/git/multiscale/Multiscale/build/Release/modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/analysis/spatial/CMakeFiles/RectangularDetectRegions.dir/depend

