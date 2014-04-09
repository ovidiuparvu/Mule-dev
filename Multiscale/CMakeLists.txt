#------------------------------------------------------------
# General project configuration
#------------------------------------------------------------

# Project name
project(multiscale)

# Minimum version number
cmake_minimum_required(VERSION 2.8)

# Enable testing
enable_testing()


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
include(AddSample)
include(AddUnitTest)
include(GetCurrentDate)
include(UpdateProjectBuildNumber)
include(UpdateProjectModifiedDate)
include(MacroOutOfSourceBuild)
 
# Check if an "out of source" build folder was chosen
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")


#------------------------------------------------------------
# Compilation details
#------------------------------------------------------------

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()


#------------------------------------------------------------
# Find the required packages
#------------------------------------------------------------

# Boost
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED OFF)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

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

# Xerces
find_package(Xerces REQUIRED)

if(XERCESC_FOUND)
    include_directories(${XERCESC_INCLUDE})

    message(STATUS "Xerces C++ library was successfully found.")
endif()


#------------------------------------------------------------
# Project build number
#------------------------------------------------------------

UpdateProjectBuildNumber(
    "Release" 
    ${PROJECT_SOURCE_DIR}/doc/Multiscale.doxyfile.in 
    ${PROJECT_SOURCE_DIR}/doc/Multiscale.doxyfile
)


#------------------------------------------------------------
# Project modified date
#------------------------------------------------------------

UpdateProjectModifiedDate(
    ${PROJECT_SOURCE_DIR}/../README.md
)


#------------------------------------------------------------
# Add the include directories
#------------------------------------------------------------

# Project include
include_directories(${PROJECT_SOURCE_DIR}/include)

# Google Test framework include
include_directories(${PROJECT_SOURCE_DIR}/extern/gtest-1.7.0/include)


#------------------------------------------------------------
# Output path for binaries and libraries
#------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


#------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------
 
add_subdirectory(extern)
add_subdirectory(modules)