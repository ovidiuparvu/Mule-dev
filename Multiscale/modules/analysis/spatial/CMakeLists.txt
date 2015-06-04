#------------------------------------------------------------
# Include directories
#------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#------------------------------------------------------------
# Specify link directories
#------------------------------------------------------------

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/util)


#------------------------------------------------------------
# Add executables
#------------------------------------------------------------


# Set the detectors core source files
set (CORE_DETECTORS_SOURCE_FILES
    src/detector/ClusterDetector.cpp
    src/detector/Detector.cpp
    src/detector/RegionDetector.cpp
    src/detector/SimulationClusterDetector.cpp
    
    src/factory/CircularMatFactory.cpp
    src/factory/MatFactory.cpp
    src/factory/RectangularMatFactory.cpp
    
    src/model/Cluster.cpp
    src/model/Entity.cpp
    src/model/Region.cpp
    src/model/SpatialEntityPseudo3D.cpp
    
    src/util/Silhouette.cpp
    src/util/SpatialMeasureCalculator.cpp
)

add_library(detectors_core STATIC ${CORE_DETECTORS_SOURCE_FILES})


# CircularDetectRegions

# Set the path to the configuration file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CircularDetectRegions.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CircularDetectRegions.cpp
)

set(CIRCULAR_DETECT_REGIONS_SRC
    src/CircularDetectRegions.cpp 
)

AddExecutableInstallTarget(CircularDetectRegions "${CIRCULAR_DETECT_REGIONS_SRC}")
AddDebugPostfix(CircularDetectRegions)

target_link_libraries(CircularDetectRegions detectors_core)
target_link_libraries(CircularDetectRegions util)
target_link_libraries(CircularDetectRegions ${OpenCV_LIBRARIES})
target_link_libraries(CircularDetectRegions ${Boost_PROGRAM_OPTIONS_LIBRARY})


# CircularMatFactorySample

set(CIRCULAR_MAT_FACTORY_SAMPLE_SRC
    sample/CircularMatFactorySample.cpp
)

add_executable(CircularMatFactorySample ${CIRCULAR_MAT_FACTORY_SAMPLE_SRC})
AddSample(CircularMatFactorySample)

target_link_libraries(CircularMatFactorySample detectors_core)
target_link_libraries(CircularMatFactorySample util)
target_link_libraries(CircularMatFactorySample ${OpenCV_LIBRARIES})
target_link_libraries(CircularMatFactorySample gtest gtest_main)


# ClusterDetectorTest

set(CLUSTER_DETECTOR_TEST_SRC
    test/ClusterDetectorTest.cpp
)

set(CLUSTER_DETECTOR_TEST_LINK_LIBS
    detectors_core
    util
    ${OpenCV_LIBRARIES}
    gtest 
    gtest_main
)

AddUnitTest(ClusterDetectorTest "${CLUSTER_DETECTOR_TEST_SRC}" "${CLUSTER_DETECTOR_TEST_LINK_LIBS}")


# DBSCANTest

set(DBSCAN_TEST_SRC
    test/DBSCANTest.cpp
)

set(DBSCAN_TEST_LINK_LIBS
    util
    ${OpenCV_LIBRARIES}
    gtest 
    gtest_main
)

AddUnitTest(DBSCANTest "${DBSCAN_TEST_SRC}" "${DBSCAN_TEST_LINK_LIBS}")


# RegionDetectorTest

set(REGION_DETECTOR_TEST_SRC
    test/RegionDetectorTest.cpp
)

set(REGION_DETECTOR_TEST_LINK_LIBS
    detectors_core
    util
    ${OpenCV_LIBRARIES}
    gtest 
    gtest_main
)

AddUnitTest(RegionDetectorTest "${REGION_DETECTOR_TEST_SRC}" "${REGION_DETECTOR_TEST_LINK_LIBS}")


# LexicographicIteratorSample

set(LEXICOGRAPHIC_ITERATOR_SAMPLE_SRC
    sample/LexicographicIteratorSample.cpp
)

add_executable(LexicographicIteratorSample ${LEXICOGRAPHIC_ITERATOR_SAMPLE_SRC})
AddSample(LexicographicIteratorSample)

target_link_libraries(LexicographicIteratorSample util)
target_link_libraries(LexicographicIteratorSample ${OpenCV_LIBRARIES})
target_link_libraries(LexicographicIteratorSample gtest gtest_main)


# RectangularDetectRegions

# Set the path to the configuration file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RectangularDetectRegions.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RectangularDetectRegions.cpp
)

set(RECTANGULAR_DETECT_REGIONS_SRC
    src/RectangularDetectRegions.cpp
)

AddExecutableInstallTarget(RectangularDetectRegions "${RECTANGULAR_DETECT_REGIONS_SRC}")
AddDebugPostfix(RectangularDetectRegions)

target_link_libraries(RectangularDetectRegions detectors_core)
target_link_libraries(RectangularDetectRegions util)
target_link_libraries(RectangularDetectRegions ${OpenCV_LIBRARIES})
target_link_libraries(RectangularDetectRegions ${Boost_PROGRAM_OPTIONS_LIBRARY})


# RectangularMatFactorySample

set(RECTANGULAR_MAT_FACTORY_SAMPLE_SRC
    sample/RectangularMatFactorySample.cpp
)

add_executable(RectangularMatFactorySample ${RECTANGULAR_MAT_FACTORY_SAMPLE_SRC})
AddSample(RectangularMatFactorySample)

target_link_libraries(RectangularMatFactorySample detectors_core)
target_link_libraries(RectangularMatFactorySample util)
target_link_libraries(RectangularMatFactorySample ${OpenCV_LIBRARIES})
target_link_libraries(RectangularMatFactorySample gtest gtest_main)


# SimulationDetectClusters

# Set the path to the configuration file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SimulationDetectClusters.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SimulationDetectClusters.cpp
)

set(SIMULATION_DETECT_CLUSTERS_SRC
    src/SimulationDetectClusters.cpp
)

AddExecutableInstallTarget(SimulationDetectClusters "${SIMULATION_DETECT_CLUSTERS_SRC}")
AddDebugPostfix(SimulationDetectClusters)

target_link_libraries(SimulationDetectClusters detectors_core)
target_link_libraries(SimulationDetectClusters util)
target_link_libraries(SimulationDetectClusters ${OpenCV_LIBRARIES})
target_link_libraries(SimulationDetectClusters ${Boost_PROGRAM_OPTIONS_LIBRARY})