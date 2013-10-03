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