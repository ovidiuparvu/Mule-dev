all: mapcart2pol mapcart2conc polmapcsv2input rectmapcsv2input rectspatial_analysis circspatial_analysis rect_mat_factory_test circ_mat_factory_test

# Targets
	
mapcart2pol:
	g++ -std=c++11 -O2 -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript -Wall /usr/local/lib/libboost_program_options.a
	
mapcart2pol_debug:
	g++ -std=c++11 -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript_d -Wall /usr/local/lib/libboost_program_options.a

mapcart2conc:
	g++ -std=c++11 -O2 -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript -Wall /usr/local/lib/libboost_program_options.a
	
mapcart2conc_debug:
	g++ -std=c++11 -g -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript_d -Wall /usr/local/lib/libboost_program_options.a

polmapcsv2input:
	g++ -std=c++11 -O2 -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles -Wall /usr/local/lib/libboost_program_options.a

polmapcsv2input_debug:
	g++ -std=c++11 -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles_d -Wall /usr/local/lib/libboost_program_options.a

rectmapcsv2input:
	g++ -std=c++11 -O2 -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles -Wall /usr/local/lib/libboost_program_options.a

rectmapcsv2input_debug:
	g++ -std=c++11 -g -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles_d -Wall /usr/local/lib/libboost_program_options.a

rectspatial_analysis:
	g++ -std=c++11 -O2 -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/RectangularDetectRegions.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/RectangularDetectRegions -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

rectspatial_analysis_debug:
	g++ -std=c++11 -g -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/RectangularDetectRegions.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/RectangularDetectRegions_d -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

circspatial_analysis:
	g++ -std=c++11 -O2 -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/CircularDetectRegions.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/CircularDetectRegions -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

circspatial_analysis_debug:
	g++ -std=c++11 -g -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/util/Geometry2D.cpp src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/CircularDetectRegions.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp src/multiscale/analysis/spatial/Region.cpp src/multiscale/analysis/spatial/RegionDetector.cpp -o bin/CircularDetectRegions -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 


# Unit tests

line_circle_test:
	g++ -std=c++11 -O2 -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/util/Geometry2D.cpp test/LineCircleIntersectionTest.cpp -o bin/LineCircleIntersectionTest -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

rect_mat_factory_test:
	g++ -std=c++11 -O2 -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/factory/RectangularMatFactory.cpp test/RectangularMatFactoryTest.cpp -o bin/RectangularMatFactoryTest -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

circ_mat_factory_test:
	g++ -std=c++11 -O2 -I /usr/local/include/opencv -I ${BOOST_ROOT} -I include src/multiscale/analysis/spatial/MatFactory.cpp src/multiscale/analysis/spatial/factory/CircularMatFactory.cpp test/CircularMatFactoryTest.cpp -o bin/CircularMatFactoryTest -Wall /usr/local/lib/libboost_program_options.a /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 


# Remove the compiled files

clean:
	rm -f bin/*
