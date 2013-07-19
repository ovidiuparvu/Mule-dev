#########################################################################################
# Flags
#
# Please EDIT the following include and libraries paths in order for the compilation to
# work properly.
#########################################################################################

CC=g++

CFLAGS_RELEASE=-std=c++11 -O2 -Wall
CFLAGS_DEBUG=-std=c++11 -g -Wall

INCLUDES_PROJECT=-I include
INCLUDES_BOOST=-I ${BOOST_ROOT}
INCLUDES_OPENCV=-I /usr/local/include/opencv

LIBS_BOOST=/usr/local/lib/libboost_program_options.a /usr/local/lib/libboost_serialization.a
LIBS_OPENCV=/usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so


#########################################################################################
# Default target
#
# List of all targets: mapcart2pol mapcart2pol_debug mapcart2conc mapcart2conc_debug polmapcsv2input polmapcsv2input_debug rectmapcsv2input rectmapcsv2input_debug rect_region_detection rect_region_detection_debug circ_region_detection circ_region_detection_debug simulation_cluster_detection simulation_cluster_detection_debug
#########################################################################################

all: rect_region_detection rect_region_detection_debug circ_region_detection circ_region_detection_debug simulation_cluster_detection simulation_cluster_detection_debug


#########################################################################################
# Targets
#
# DO NOT EDIT this section for changing the include and libraries path. Refer to the 
# "Flags" section for these changes.
#########################################################################################
	
mapcart2pol:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript $(LIBS_BOOST)
	
mapcart2pol_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript_d $(LIBS_BOOST)

mapcart2conc:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript $(LIBS_BOOST)
	
mapcart2conc_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript_d $(LIBS_BOOST)

polmapcsv2input:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles $(LIBS_BOOST)

polmapcsv2input_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles_d $(LIBS_BOOST)

rectmapcsv2input:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles $(LIBS_BOOST)

rectmapcsv2input_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles_d $(LIBS_BOOST)

rect_region_detection:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Detector.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/RectangularDetectRegions.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/RectangularDetectRegions $(LIBS_BOOST) $(LIBS_OPENCV) 

rect_region_detection_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Detector.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/RectangularDetectRegions.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/RectangularDetectRegions_d $(LIBS_BOOST) $(LIBS_OPENCV) 

circ_region_detection:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Detector.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/CircularDetectRegions.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/CircularDetectRegions $(LIBS_BOOST) $(LIBS_OPENCV) 

circ_region_detection_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Detector.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/CircularDetectRegions.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/CircularDetectRegions_d $(LIBS_BOOST) $(LIBS_OPENCV) 

simulation_cluster_detection:
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Cluster.cpp src/multiscale/analysis/spatial/ClusterDetector.cpp src/multiscale/analysis/spatial/DBSCAN.cpp src/multiscale/analysis/spatial/Detector.cpp src/multiscale/analysis/spatial/Entity.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/util/RGBColourGenerator.cpp src/multiscale/analysis/spatial/cluster/SimulationClusterDetector.cpp src/multiscale/analysis/spatial/SimulationDetectClusters.cpp -o bin/SimulationDetectClusters $(LIBS_BOOST) $(LIBS_OPENCV) 

simulation_cluster_detection_debug:
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/Cluster.cpp src/multiscale/analysis/spatial/ClusterDetector.cpp src/multiscale/analysis/spatial/DBSCAN.cpp src/multiscale/analysis/spatial/Detector.cpp src/multiscale/analysis/spatial/Entity.cpp src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/util/Numeric.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/util/RGBColourGenerator.cpp src/multiscale/analysis/spatial/cluster/SimulationClusterDetector.cpp src/multiscale/analysis/spatial/SimulationDetectClusters.cpp -o bin/SimulationDetectClusters_d $(LIBS_BOOST) $(LIBS_OPENCV) 


#########################################################################################
# Unit tests
#########################################################################################

geometry2d_test:
	g++ $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/util/Geometry2D.cpp src/multiscale/util/MinimumAreaEnclosingTriangle.cpp src/multiscale/util/Numeric.cpp test/Geometry2DTest.cpp -o bin/Geometry2DTest $(LIBS_BOOST) $(LIBS_OPENCV) 

geometry2d_test_debug:
	g++ $(CFLAGS_DEBUG) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/util/Geometry2D.cpp src/multiscale/util/MinimumAreaEnclosingTriangle.cpp src/multiscale/util/Numeric.cpp test/Geometry2DTest.cpp -o bin/Geometry2DTest_d $(LIBS_BOOST) $(LIBS_OPENCV) 

line_circle_test:
	g++ $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/util/Geometry2D.cpp test/LineCircleIntersectionTest.cpp -o bin/LineCircleIntersectionTest $(LIBS_BOOST) $(LIBS_OPENCV) 

rect_mat_factory_test:
	g++ $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp test/RectangularMatFactoryTest.cpp -o bin/RectangularMatFactoryTest $(LIBS_BOOST) $(LIBS_OPENCV) 

circ_mat_factory_test:
	g++ $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp test/CircularMatFactoryTest.cpp -o bin/CircularMatFactoryTest $(LIBS_BOOST) $(LIBS_OPENCV) 

dbscan_test:
	g++ $(CFLAGS_RELEASE) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/DBSCAN.cpp test/dbscan/EuclideanDataPoint.hpp test/dbscan/DBSCANTest.cpp -o bin/DBSCANTest $(LIBS_BOOST) $(LIBS_OPENCV) 

dbscan_test_debug:
	g++ $(CFLAGS_DEBUG) $(INCLUDES_OPENCV) $(INCLUDES_BOOST) $(INCLUDES_PROJECT) src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/DBSCAN.cpp test/dbscan/EuclideanDataPoint.hpp test/dbscan/DBSCANTest.cpp -o bin/DBSCANTest_d $(LIBS_BOOST) $(LIBS_OPENCV) 


#########################################################################################
# Remove the compiled files
#########################################################################################

clean:
	rm -f bin/*
