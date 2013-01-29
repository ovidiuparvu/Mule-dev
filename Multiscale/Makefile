all: mapcart2pol mapcsv2input
	
mapcart2pol:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolar.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolar -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a
	
mapcart2pol_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/CartesianToPolarConverter.cpp src/multiscale/video/circular/AnnularSector.cpp src/multiscale/video/circular/PolarGnuplotScriptGenerator.cpp src/multiscale/video/circular/MapCartesianToPolar.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCartesianToPolar -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

mapcsv2input:
	g++ -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/MapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

mapcsv2input_debug:
	g++ -g -I ${BOOST_ROOT} -I include src/multiscale/video/circular/PolarCsvToInputFilesConverter.cpp src/multiscale/util/iterator/LexicographicNumberIterator.cpp src/multiscale/video/circular/MapCsvToInputFiles.cpp src/multiscale/util/NumberIterator.cpp src/multiscale/util/iterator/StandardNumberIterator.cpp src/multiscale/util/StringManipulator.cpp -o bin/MapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

clean:
	rm -f bin/MapCartesianToPolar	
