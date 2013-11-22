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


# CircularDetectRegions

set(CIRCULAR_DETECT_REGIONS_SRC
    src/CircularityMeasure.cpp
    src/Detector.cpp
    src/MatFactory.cpp 
    src/CircularDetectRegions.cpp 
    src/Region.cpp
    src/RegionDetector.cpp
    src/SpatialCollection2D.cpp
    
    src/factory/CircularMatFactory.cpp 
)

add_executable(CircularDetectRegions ${CIRCULAR_DETECT_REGIONS_SRC})

AddDebugPostfix(CircularDetectRegions)

target_link_libraries(CircularDetectRegions util)
target_link_libraries(CircularDetectRegions ${OpenCV_LIBRARIES})
target_link_libraries(CircularDetectRegions ${Boost_PROGRAM_OPTIONS_LIBRARY})


# CircularMatFactorySample

set(CIRCULAR_MAT_FACTORY_SAMPLE_SRC
    sample/CircularMatFactorySample.cpp
    
    src/factory/CircularMatFactory.cpp
    src/DBSCAN.cpp
    src/MatFactory.cpp
)

add_executable(CircularMatFactorySample ${CIRCULAR_MAT_FACTORY_SAMPLE_SRC})
AddSample(CircularMatFactorySample)

target_link_libraries(CircularMatFactorySample util)
target_link_libraries(CircularMatFactorySample ${OpenCV_LIBRARIES})
target_link_libraries(CircularMatFactorySample gtest gtest_main)


# DBSCANTest

set(DBSCAN_TEST_SRC
    test/DBSCANTest.cpp
    
    src/DBSCAN.cpp
)

add_executable(DBSCANTest ${DBSCAN_TEST_SRC})
AddUnitTest(DBSCANTest)

target_link_libraries(DBSCANTest util)
target_link_libraries(DBSCANTest ${OpenCV_LIBRARIES})
target_link_libraries(DBSCANTest gtest gtest_main)


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

set(RECTANGULAR_DETECT_REGIONS_SRC
    src/CircularityMeasure.cpp
    src/Detector.cpp
    src/MatFactory.cpp 
    src/RectangularDetectRegions.cpp 
    src/Region.cpp
    src/RegionDetector.cpp
    src/SpatialCollection2D.cpp
    
    src/factory/RectangularMatFactory.cpp 
)

add_executable(RectangularDetectRegions ${RECTANGULAR_DETECT_REGIONS_SRC})

AddDebugPostfix(RectangularDetectRegions)

target_link_libraries(RectangularDetectRegions util)
target_link_libraries(RectangularDetectRegions ${OpenCV_LIBRARIES})
target_link_libraries(RectangularDetectRegions ${Boost_PROGRAM_OPTIONS_LIBRARY})


# RectangularMatFactorySample

set(RECTANGULAR_MAT_FACTORY_SAMPLE_SRC
    sample/RectangularMatFactorySample.cpp
    
    src/DBSCAN.cpp
    src/MatFactory.cpp
    src/factory/RectangularMatFactory.cpp
)

add_executable(RectangularMatFactorySample ${RECTANGULAR_MAT_FACTORY_SAMPLE_SRC})
AddSample(RectangularMatFactorySample)

target_link_libraries(RectangularMatFactorySample util)
target_link_libraries(RectangularMatFactorySample ${OpenCV_LIBRARIES})
target_link_libraries(RectangularMatFactorySample gtest gtest_main)


# SimulationDetectClusters

set(SIMULATION_DETECT_CLUSTERS_SRC
    src/CircularityMeasure.cpp
    src/Cluster.cpp
    src/ClusterDetector.cpp
    src/DBSCAN.cpp
    src/Detector.cpp
    src/Entity.cpp
    src/MatFactory.cpp
    src/Silhouette.cpp
    src/cluster/SimulationClusterDetector.cpp
    src/SimulationDetectClusters.cpp
    src/SpatialCollection2D.cpp
    
    src/factory/RectangularMatFactory.cpp 
)

add_executable(SimulationDetectClusters ${SIMULATION_DETECT_CLUSTERS_SRC})

AddDebugPostfix(SimulationDetectClusters)

target_link_libraries(SimulationDetectClusters util)
target_link_libraries(SimulationDetectClusters ${OpenCV_LIBRARIES})
target_link_libraries(SimulationDetectClusters ${Boost_PROGRAM_OPTIONS_LIBRARY})