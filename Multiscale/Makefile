all: mapcart2pol mapcart2conc polmapcsv2input rectmapcsv2input_debug
	
mapcart2pol:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a
	
mapcart2pol_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolarScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolarScript -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

mapcart2conc:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a
	
mapcart2conc_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/CartesianToConcentrationsConverter.cpp src/multiscale/video/rectangular/RectangularGnuplotScriptGenerator.cpp src/multiscale/video/rectangular/MapCartesianToScript.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToScript -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

polmapcsv2input:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

polmapcsv2input_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/PolarMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/PolarMapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

rectmapcsv2input:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

rectmapcsv2input_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/rectangular/RectangularCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/rectangular/RectangularMapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/RectangularMapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

clean:
	rm -f bin/*
