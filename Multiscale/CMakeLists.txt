#------------------------------------------------------------
# General project configuration
#------------------------------------------------------------

# Project name
project(multiscale)

# Minimum version number
cmake_minimum_required(VERSION 2.6)


#------------------------------------------------------------
# Compilation details
#------------------------------------------------------------

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
    add_definitions(-Wall)
endif()


#------------------------------------------------------------
# Output path for binaries and libraries
#------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


#------------------------------------------------------------
# Configuration dependent details
#------------------------------------------------------------

# Change the names of the output libraries depending on the chosen configuration
set(CMAKE_DEBUG_POSTFIX _d)


#------------------------------------------------------------
# Enforce "out of source" build
#------------------------------------------------------------
 
# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
 
# Incluse user defined CMake modules
include(AddDebugPostfix)
include(MacroOutOfSourceBuild)
 
# Check if an "out of source" build folder was chosen
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")


#------------------------------------------------------------
# Add the include directories
#------------------------------------------------------------

# Project include
include_directories(${PROJECT_SOURCE_DIR}/include)


#------------------------------------------------------------
# Find the required packages
#------------------------------------------------------------

# Boost
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED OFF)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    message(STATUS "Boost library was successfully found.")
endif()

# OpenCV
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})

    message(STATUS "OpenCV library was successfully found.")
endif()


#------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------
 
add_subdirectory(modules)